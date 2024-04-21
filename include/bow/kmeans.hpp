#ifndef KMEANS_HPP_
#define KMEANS_HPP_

#include <vector>

#include <opencv2/core/mat.hpp>

namespace ipb {

bool check_centers_similarity(const cv::Mat& desc1, const cv::Mat& desc2);
cv::Mat kMeans(const std::vector<cv::Mat>& descriptors, int k, int max_iter);
}  // namespace ipb

#endif  // KMEANS_HPP_