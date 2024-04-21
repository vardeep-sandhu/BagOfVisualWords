#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <opencv2/core/mat.hpp>

#include "bow.h"
#include "test_data.hpp"

using namespace std;
using namespace cv;

namespace {
template <typename Tp>
bool inline mat_are_equal(const cv::Mat& m1, const cv::Mat& m2) {
  return std::equal(m1.begin<Tp>(), m1.end<Tp>(), m2.begin<Tp>());
}
}  // namespace

static void TestKMeans(const cv::Mat& gt_cluster) {
  auto& data = GetDummyData();

  const int dict_size = gt_cluster.rows;
  const int iterations = 10;
  auto centroids = ipb::kMeans(data, dict_size, iterations);

  EXPECT_EQ(centroids.rows, dict_size);
  EXPECT_EQ(centroids.size, gt_cluster.size);

  // Need to sort the output, otherwise the comparison will fail
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  EXPECT_TRUE(mat_are_equal<float>(centroids, gt_cluster))
      << "gt_centroids:\n"
      << gt_cluster << "\ncomputed centroids:\n"
      << centroids;
}

TEST(KMeansCluster, Use2Words) { TestKMeans(Get2Kmeans()); }
TEST(KMeansCluster, Use3Words) { TestKMeans(Get3Kmeans()); }
TEST(KMeansCluster, MinimumSignificantCluster) { TestKMeans(Get5Kmeans()); }