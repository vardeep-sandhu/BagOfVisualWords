#include "histogram_dataset.hpp"

#include <fstream>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/features2d.hpp>

#include "histogram.hpp"
#include "serialize.hpp"

namespace ipb {

void GetHistograms(const std::filesystem::path& bin_path,
                   const ipb::BowDictionary& dictionary) {
  // create flann based matcher
  auto diction = dictionary.vocabulary();
  cv::Ptr<cv::FlannBasedMatcher> matcher = cv::FlannBasedMatcher::create();
  matcher->add(diction);
  matcher->train();
  // create empty hist with k-means set which can take multiple images
  int number_of_images = 0;
  std::vector<int> occurence_of_words(dictionary.size(), 0);
  for (const auto& bin : std::filesystem::directory_iterator(bin_path)) {
    if (bin.path().extension() == ".bin") {
      const auto& bin_file = bin.path();
      const auto& stem = bin_file.stem().string();
      const auto& hist_path =
          bin_path.parent_path().parent_path().string() + "/histogram/";
      std::filesystem::create_directory(hist_path);
      cv::Mat sift_feat = ipb::serialization::Deserialize(bin.path());
      auto histogram = Histogram(sift_feat, matcher, dictionary.size());
      number_of_images += 1;
      auto this_occurence = histogram.get_occurences();
      std::transform(occurence_of_words.begin(), occurence_of_words.end(),
                     this_occurence.begin(), occurence_of_words.begin(),
                     std::plus<>());
      const auto& hist_csv = hist_path + stem + ".csv";
      histogram.WriteToCSV(hist_csv);
    }
  }
  const auto& hist_p =
      bin_path.parent_path().parent_path().string() + "/histogram/";
  const auto& tdf_hist_name = hist_p + "tdf_hist.txt";
  std::ofstream out(tdf_hist_name);
  out << number_of_images << std::endl;
  for (auto i : occurence_of_words) {
    out << i << std::endl;
  }
}
}  // namespace ipb