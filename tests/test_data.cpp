// @file      test_data.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include "test_data.hpp"

#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

std::vector<cv::Mat>& GetDummyData() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  static std::vector<Mat> data;
  data.clear();
  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat GetAllFeatures() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat Get18Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 3; j++) {
      data.push_back(Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat Get5Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  for (int i = 0; i < 100; i += 20) {
    Mat_<float> vec(rows_num, cols_num, i);
    data.push_back(vec);
  }

  return data;
}

cv::Mat Get3Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  data.push_back(Mat_<float>(rows_num, cols_num, 0.0F));
  data.push_back(Mat_<float>(rows_num, cols_num, 20.0F));
  data.push_back(Mat_<float>(rows_num, cols_num, 59.999996F));

  return data;
}

cv::Mat Get2Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  data.push_back(Mat_<float>(rows_num, cols_num, 10.0F));
  data.push_back(Mat_<float>(rows_num, cols_num, 59.999996F));

  return data;
}

//  05,  05,  05,  05,  05,  05,  05,  05,  05,  05;
//  15,  15,  15,  15,  15,  15,  15,  15,  15,  15;
// 115, 115, 115, 115, 115, 115, 115, 115, 115, 115;
cv::Mat Get3Features() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  Mat data;

  data.push_back(Mat_<float>(rows_num, cols_num, 5.0F));
  data.push_back(Mat_<float>(rows_num, cols_num, 15.0F));
  data.push_back(Mat_<float>(rows_num, cols_num, 115.0F));

  return data;
}

std::vector<std::vector<int>> GetHistograms() {
  std::vector<std::vector<int>> histogram;
  histogram.push_back({5, 2, 1, 0, 0});
  histogram.push_back({4, 0, 1, 1, 0});
  histogram.push_back({3, 1, 1, 0, 2});
  histogram.push_back({1, 2, 1, 0, 0});
  return histogram;
}

std::vector<std::vector<float>> GetTFHistograms() {
  std::vector<std::vector<float>> tf_histogram;
  tf_histogram.push_back({0.0, 0.07, 0.0, 0.0, 0.0});
  tf_histogram.push_back({0.0, 0.0, 0.0, 0.23, 0.0});
  tf_histogram.push_back({0.0, 0.04, 0.0, 0.0, 0.4});
  tf_histogram.push_back({0.0, 0.14, 0.0, 0.0, 0.0});
  return tf_histogram;
}