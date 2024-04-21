#include "kmeans.hpp"

#include <iostream>

#include <opencv2/features2d.hpp>

namespace ipb {

bool check_centers_similarity(const cv::Mat& desc1, const cv::Mat& desc2) {
  bool check = false;
  cv::Mat difference = desc1 - desc2;
  double norm_diff = cv::norm(difference);
  if (norm_diff < 0.01) {
    check = true;
  }
  return check;
}

cv::Mat kMeans(const std::vector<cv::Mat>& descriptors, int k, int max_iter) {
  cv::Mat centers;
  cv::Mat stack_descriptors;

  for (const auto& i : descriptors) {
    stack_descriptors.push_back(i);
  }

  std::cout << stack_descriptors.size;

  // initially uniform assignment of the centres
  const int uniform = static_cast<int>(stack_descriptors.rows / k);
  for (int iter = 0; iter < k; iter++) {
    const int next = iter * uniform;
    centers.push_back(stack_descriptors.row(next));
  }

  // k-means assignment
  for (int iter = 0; iter < max_iter; iter++) {
    // flann based kmeans
    cv::Ptr<cv::FlannBasedMatcher> matcher = cv::FlannBasedMatcher::create();
    matcher->add(centers);
    matcher->train();

    // zero valued centres is updated centres
    cv::Mat updated_centers =
        cv::Mat::zeros(centers.rows, centers.cols, centers.type());
    std::vector<float> label_count(k, 0.0);

    // loop through each descriptor
    for (int i = 0; i < stack_descriptors.rows; i++) {
      int center_label = 0;
      cv::Mat this_descriptor = stack_descriptors.row(i);

      // see which centre is close to the descriptor
      std::vector<cv::DMatch> match;
      matcher->match(this_descriptor, match);
      center_label = match[0].trainIdx;

      // update through running average
      label_count[center_label]++;
      updated_centers.row(center_label) =
          updated_centers.row(center_label) +
          (1.0 / label_count[center_label]) *
              (this_descriptor - updated_centers.row(center_label));
    }

    bool check_continue = check_centers_similarity(centers, updated_centers);
    centers = updated_centers;
    if (check_continue) {
      break;
    }
  }
  return centers;
}
}  // namespace ipb