#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "bow.h"
#include "test_data.hpp"
#include "utils/current_path.hpp"

namespace fs = std::filesystem;

namespace {
const std::string img_path = ipb::ProjectPath + "tests/data/freiburg/images/";
const std::filesystem::path image_file_path(img_path);
const auto& hist_path =
    image_file_path.parent_path().parent_path().string() + "/histogram/";
const auto& bin_path =
    image_file_path.parent_path().parent_path().string() + "/bin/";

// define and get the dictionary using k-means
auto& dictionary = ipb::BowDictionary::GetInstance();
const int max_iter = 10;
const int dict_size = 50;

template <typename Tp>
bool inline norm_compare(const std::vector<Tp>& v1, const std::vector<Tp>& v2) {
  std::vector<Tp> diff;
  for (int k = 0; k < 4; k++) {
    diff.push_back(v1[k] - v2[k]);
  }
  double norm = 0.0;
  for (auto const& i : diff) {
    norm += i * i;
  }
  bool flag = false;
  if (sqrt(norm) < 0.1) {
    flag = true;
  }
  return flag;
}
}  // namespace

TEST(Datasets, Histrograms) {
  ipb::serialization::sifts::ConvertDataset(img_path);
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);
  dictionary.build(max_iter, dict_size, descriptors);
  ipb::GetHistograms(bin_path, dictionary);
  ASSERT_TRUE(fs::exists(bin_path));
  ASSERT_TRUE(fs::exists(hist_path));
  // getting occurences and number of images in the dataset
  int num_images;
  for (const auto& bin : std::filesystem::directory_iterator(hist_path)) {
    if (bin.path().extension() == ".txt") {
      std::ifstream in(bin.path(), std::ios_base::in);
      in >> num_images;
      ASSERT_EQ(num_images, 10);
    }
  }
}

TEST(QueryDatasets, tfIDFhist) {
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);
  dictionary.build(max_iter, dict_size, descriptors);
  // query example
  const std::string query_path =
      ipb::ProjectPath +
      "tests/data/freiburg/images/imageCompressedCam0_0000000.png";
  cv::Mat query_descriptors =
      ipb::serialization::sifts::GetDescriptors(query_path);
  ipb::QueryImage query_img(query_descriptors, dictionary);
  std::vector<ipb::IndexedHist> dataset_tfidf_hist =
      query_img.tf_idf_histograms(hist_path);

  // size of the tf_idf_hist
  ASSERT_EQ(dataset_tfidf_hist.size(), 10);

  // score in tuple is zero - initilized value
  for (auto& i : dataset_tfidf_hist) {
    ASSERT_EQ(std::get<0>(i), 0.0);
  }
}

TEST(QueryDatasets, GetSimilarImages) {
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);
  dictionary.build(max_iter, dict_size, descriptors);
  // query example
  const std::string query_path =
      ipb::ProjectPath +
      "tests/data/freiburg/images/imageCompressedCam0_0000000.png";
  cv::Mat query_descriptors =
      ipb::serialization::sifts::GetDescriptors(query_path);
  ipb::QueryImage query_img(query_descriptors, dictionary);
  int num_similar_imgs = 5;
  std::vector<image_browser::ScoredImage> results =
      query_img.get_similar_images(hist_path, num_similar_imgs);

  // size of the image rows
  ASSERT_EQ(results.size(), num_similar_imgs);

  // check if the score of the images are sorted
  for (int i = 0; i < num_similar_imgs - 1; i++) {
    ASSERT_TRUE(std::get<1>(results[i]) > std::get<1>(results[i + 1]));
  }
  fs::remove_all(bin_path);
  fs::remove_all(hist_path);
}
