#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "bow.h"
#include "test_data.hpp"

namespace {

const int dict_size = 5;  // using Get5Kmeans() dummy data;
auto& dictionary = ipb::BowDictionary::GetInstance();

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

TEST(QueryImage, Construct) {
  dictionary.set_vocabulary(Get5Kmeans());
  cv::Mat descriptors = Get2Kmeans();
  ipb::QueryImage query(descriptors, dictionary);
  ASSERT_EQ(query.size(), dict_size);
}

TEST(QueryImage, TFidf) {
  const int number = 4;
  const std::vector<int> occurences = {4, 3, 4, 1, 1};
  std::vector<std::vector<int>> histogram = GetHistograms();
  std::vector<std::vector<float>> tf_histogram = GetTFHistograms();

  std::vector<std::vector<float>> calc_tf_histogram;

  for (int i = 0; i < 4; i++) {
    std::vector<float> tf_out_hist =
        ipb::QueryImage::get_tf(histogram[i], number, occurences);
    calc_tf_histogram.push_back(tf_out_hist);
    EXPECT_TRUE(norm_compare<float>(tf_out_hist, tf_histogram[i]))
        << i << "\n"
        << "calculated tf histogram:\n"
        << tf_out_hist[0] << tf_out_hist[1] << tf_out_hist[2] << tf_out_hist[3]
        << "\ntrue tf histogram:\n"
        << tf_histogram[i][0] << tf_histogram[i][1] << tf_histogram[i][2]
        << tf_histogram[i][3];
  }
  // cosine similarity test
  float sim1 = ipb::QueryImage::cosine_similarity(calc_tf_histogram[0],
                                                  calc_tf_histogram[1]);

  float sim3 = ipb::QueryImage::cosine_similarity(calc_tf_histogram[0],
                                                  calc_tf_histogram[2]);
  float sim2 = ipb::QueryImage::cosine_similarity(calc_tf_histogram[0],
                                                  calc_tf_histogram[3]);

  float eps = 0.01f;
  ASSERT_NEAR(0.0f, sim1, eps);
  ASSERT_NEAR(1.0f, sim2, eps);
  ASSERT_NEAR(0.1f, sim3, eps);
}

TEST(QueryImage, NORM) {
  const std::vector<float> norm_vec = {0.3, 0.4};
  float eps = 0.001f;
  float norm_val = ipb::QueryImage::norm(norm_vec);
  ASSERT_NEAR(0.5f, norm_val, eps);
}