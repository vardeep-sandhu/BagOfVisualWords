#include "query_image.hpp"

#include <fstream>
#include <numeric>

#include "convert_dataset.hpp"
#include "histogram.hpp"

namespace ipb {

QueryImage::QueryImage(const cv::Mat& query_descriptors,
                       const ipb::BowDictionary& dictionary) {
  // initialise histogram
  Histogram histogram(query_descriptors, dictionary);
  std::vector<int> hist_occurence = histogram.get_occurences();
  query_histogram_ = histogram.data();
  query_occurence_ = hist_occurence;
}

unsigned long QueryImage::size() const { return query_histogram_.size(); }

std::vector<IndexedHist> QueryImage::tf_idf_histograms(
    const std::filesystem::path& hist_path) {
  int number_of_images = 0;
  std::vector<int> occurence_of_words;

  // getting occurences and number of images in the dataset
  for (const auto& bin : std::filesystem::directory_iterator(hist_path)) {
    if (bin.path().extension() == ".txt") {
      std::ifstream in(bin.path(), std::ios_base::in);
      in >> number_of_images;
      for (unsigned long i = 0; i < query_histogram_.size(); i++) {
        int num = 0;
        in >> num;
        occurence_of_words.push_back(num);
      }
    }
  }

  // update with query image parameters
  number_of_images += 1;
  std::transform(occurence_of_words.begin(), occurence_of_words.end(),
                 query_occurence_.begin(), occurence_of_words.begin(),
                 std::plus<>());

  // tf-idf of the database
  std::vector<IndexedHist> indexed_hist;
  for (const auto& bin : std::filesystem::directory_iterator(hist_path)) {
    if (bin.path().extension() == ".csv") {
      auto histogram = ipb::Histogram::ReadFromCSV(bin.path());
      std::vector<float> hist_tf_idf =
          get_tf(histogram.data(), number_of_images, occurence_of_words);
      const auto& hist_file = bin.path();
      const auto& stem = hist_file.stem().string();
      const auto& image_path =
          hist_path.parent_path().parent_path().string() + "/images/";
      const auto& image_file = image_path + stem + ".png";
      indexed_hist.emplace_back(std::make_tuple(0.0, hist_tf_idf, image_file));
    }
  }

  // tf-idf of the query image
  query_histogram_tf_idf_ =
      get_tf(query_histogram_, number_of_images, occurence_of_words);
  return indexed_hist;
}

std::vector<float> QueryImage::get_tf(const std::vector<int>& histogram,
                                      const int& num_images,
                                      const std::vector<int>& occurence) {
  std::vector<float> tf_histogram;
  for (unsigned long i = 0; i < histogram.size(); i++) {
    tf_histogram.push_back(
        (static_cast<float>(histogram[i]) /
         accumulate(histogram.begin(), histogram.end(), 0)) *
        std::log(static_cast<float>(num_images) / occurence[i]));
  }
  return tf_histogram;
}

float QueryImage::norm(const std::vector<float>& vec) {
  float norm = 0.0;
  for (auto const& i : vec) {
    norm += i * i;
  }
  return std::sqrt(norm);
}

float QueryImage::cosine_similarity(const std::vector<float>& a,
                                    const std::vector<float>& b) {
  float score = std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
  score = score / (norm(a) * norm(b));
  return score;
}

std::vector<ScoredImage> QueryImage::get_similar_images(
    const std::filesystem::path& hist_path, const int& num_similar) {
  // get the tfidf hist vector - indexed
  std::vector<IndexedHist> dataset_tfidf_hist = tf_idf_histograms(hist_path);

  // loop over each histogram and get cosine similarity for each
  for (auto& i : dataset_tfidf_hist) {
    std::get<0>(i) = cosine_similarity(std::get<1>(i), query_histogram_tf_idf_);
  }

  // sort for the highest similarity
  sort(dataset_tfidf_hist.begin(), dataset_tfidf_hist.end(),
       [](const IndexedHist& h1, const IndexedHist& h2) {
         return std::get<0>(h1) > std::get<0>(h2);
       });
  std::vector<ScoredImage> results;
  for (int i = 0; i < num_similar; i++) {
    auto tf_hist = dataset_tfidf_hist[i];
    results.emplace_back(
        std::make_tuple(std::get<2>(tf_hist), std::get<0>(tf_hist)));
  }

  return results;
}
}  // namespace ipb
