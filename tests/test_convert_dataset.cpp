#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <string>

#include <opencv2/core/mat.hpp>

#include "bow.h"
#include "utils/current_path.hpp"

namespace fs = std::filesystem;

TEST(ConvertHistogram, ComputeSIFTS) {
  const std::string img_path = ipb::ProjectPath + "tests/data/freiburg/images/";
  const std::string bin_path = ipb::ProjectPath + "tests/data/freiburg/bin/";
  ipb::serialization::sifts::ConvertDataset(img_path);

  for (const auto& entry : fs::directory_iterator(img_path)) {
    const auto& stem = entry.path().stem().string();
    const auto& extension = entry.path().extension();
    if (extension == ".png") {
      const auto& descriptors_filename = bin_path + stem + ".bin";
      ASSERT_TRUE(fs::exists(descriptors_filename));
    }
  }
}

TEST(ConvertHistogram, Deserialize) {
  const std::string bin_path = ipb::ProjectPath + "tests/data/freiburg/bin/";
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);
  for (const auto& descriptor : descriptors) {
    ASSERT_TRUE(!descriptor.empty());
  }
  fs::remove_all(bin_path);
}