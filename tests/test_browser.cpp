#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "bow.h"
#include "test_data.hpp"
#include "utils/current_path.hpp"

namespace fs = std::filesystem;

TEST(WebBrowser, FileExistence) {
  const std::string query_path =
      ipb::ProjectPath +
      "tests/data/freiburg/images/imageCompressedCam0_0000000.png";

  std::vector<image_browser::ScoredImage> rows;
  for (int i = 0; i < 3; i++) {
    rows.emplace_back(std::make_tuple(query_path, 0.3));
  }

  const std::string html_file =
      ipb::ProjectPath + "tests/data/display_bow_results.html";

  image_browser::CreateImageBrowser("BoVW", "style.css", rows, html_file,
                                    query_path);
  ASSERT_TRUE(fs::exists(html_file));
  fs::remove(html_file);
}
