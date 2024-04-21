// @file      convert_dataset.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef CONVERT_DATASET_HPP_
#define CONVERT_DATASET_HPP_

#include <filesystem>
#include <vector>

#include <opencv2/core/mat.hpp>

namespace ipb::serialization::sifts {
cv::Mat GetDescriptors(const std::filesystem::path& img_file);
void ConvertDataset(const std::filesystem::path& img_path);
std::vector<cv::Mat> LoadDataset(const std::filesystem::path& bin_path);

}  // namespace ipb::serialization::sifts

#endif  // CONVERT_DATASET_HPP_