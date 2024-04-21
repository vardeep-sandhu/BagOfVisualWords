#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "bow.h"
#include "utils/current_path.hpp"

namespace fs = std::filesystem;

namespace {
template <typename Tp>
bool inline mat_are_equal(const cv::Mat& m1, const cv::Mat& m2) {
  return std::equal(m1.begin<Tp>(), m1.end<Tp>(), m2.begin<Tp>());
}
}  // namespace

TEST(imgSerialization, Serialize) {
  const std::string lenna_path = ipb::ProjectPath + "tests/data/lenna.png";
  const std::string lenna_bin_path = ipb::ProjectPath + "tests/data/lenna.bin";

  auto lenna = cv::imread(lenna_path, cv::IMREAD_GRAYSCALE);
  ASSERT_TRUE(!lenna.empty());

  ipb::serialization::Serialize(lenna, lenna_bin_path);
  ASSERT_TRUE(fs::exists(lenna_bin_path));
  fs::remove(lenna_bin_path);
}

TEST(imgSerialization, DeSerialize) {
  const std::string lenna_path = ipb::ProjectPath + "tests/data/lenna.png";
  const std::string lenna_bin_path = ipb::ProjectPath + "tests/data/lenna.bin";

  auto lenna = cv::imread(lenna_path, cv::IMREAD_GRAYSCALE);
  ASSERT_TRUE(!lenna.empty());

  ipb::serialization::Serialize(lenna, lenna_bin_path);
  auto lenna_bin = ipb::serialization::Deserialize(lenna_bin_path);
  fs::remove(lenna_bin_path);
  ASSERT_TRUE(!lenna_bin.empty());
  ASSERT_EQ(lenna.size(), lenna_bin.size());
  ASSERT_TRUE(mat_are_equal<uchar>(lenna, lenna_bin));
}

TEST(SIFTSerialization, Serialize) {
  const std::string lenna_path = ipb::ProjectPath + "tests/data/lenna.png";
  const std::string descriptors_bin_path =
      ipb::ProjectPath + "tests/data/lenna_sifts.bin";

  const auto descriptors =
      ipb::serialization::sifts::GetDescriptors(lenna_path);
  ASSERT_TRUE(!descriptors.empty());

  ipb::serialization::Serialize(descriptors, descriptors_bin_path);
  ASSERT_TRUE(fs::exists(descriptors_bin_path));
  fs::remove(descriptors_bin_path);
}

TEST(SIFTSerialization, DeSerialize) {
  const std::string lenna_path = ipb::ProjectPath + "tests/data/lenna.png";
  const std::string descriptors_bin_path =
      ipb::ProjectPath + "tests/data/lenna_sifts.bin";

  const auto descriptors =
      ipb::serialization::sifts::GetDescriptors(lenna_path);
  ASSERT_TRUE(!descriptors.empty());

  ipb::serialization::Serialize(descriptors, descriptors_bin_path);
  auto descriptors_bin = ipb::serialization::Deserialize(descriptors_bin_path);
  fs::remove(descriptors_bin_path);
  ASSERT_TRUE(!descriptors_bin.empty());
  ASSERT_EQ(descriptors.size(), descriptors_bin.size());
  ASSERT_TRUE(mat_are_equal<uchar>(descriptors, descriptors_bin));
}