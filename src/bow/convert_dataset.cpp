#include "convert_dataset.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "serialize.hpp"

namespace ipb::serialization::sifts {
using cv::xfeatures2d::SiftDescriptorExtractor;
using cv::xfeatures2d::SiftFeatureDetector;

cv::Mat GetDescriptors(const std::filesystem::path& img_file) {
  const cv::Mat kInput = cv::imread(img_file, cv::IMREAD_GRAYSCALE);
  // detect key points
  auto detector = SiftFeatureDetector::create();
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(kInput, keypoints);

  // extract the SIFT descriptors
  cv::Mat descriptors;
  auto extractor = SiftDescriptorExtractor::create();
  extractor->compute(kInput, keypoints, descriptors);

  return descriptors;
}

void ConvertDataset(const std::filesystem::path& img_path) {
  for (const auto& image : std::filesystem::directory_iterator(img_path)) {
    const auto& image_file = image.path();
    const auto& stem = image_file.stem().string();
    const auto& bin_path =
        img_path.parent_path().parent_path().string() + "/bin/";
    std::filesystem::create_directory(bin_path);

    if (image_file.extension() == ".png") {
      const auto& descriptor_bin = bin_path + stem + ".bin";
      cv::Mat descriptors = GetDescriptors(image_file);
      ipb::serialization::Serialize(descriptors, descriptor_bin);
    }
  }
}

std::vector<cv::Mat> LoadDataset(const std::filesystem::path& bin_path) {
  std::vector<cv::Mat> vector_bin;
  for (const auto& bin : std::filesystem::directory_iterator(bin_path)) {
    if (bin.path().extension() == ".bin") {
      cv::Mat sift_feat = ipb::serialization::Deserialize(bin.path());
      vector_bin.emplace_back(sift_feat);
    }
  }
  return vector_bin;
}

}  // namespace ipb::serialization::sifts