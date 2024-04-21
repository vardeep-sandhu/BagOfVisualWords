// @file      image_browser.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef IMAGE_BROWSER_HPP_
#define IMAGE_BROWSER_HPP_

#include <string>
#include <tuple>
#include <vector>

namespace image_browser {

/// Some Utility Name Types that will make the code more readable
using ScoredImage = std::tuple<std::string, float>;
using ImageRow = std::vector<ScoredImage>;

void CreateImageBrowser(const std::string& title, const std::string& stylesheet,
                        const std::vector<ScoredImage>& rows,
                        const std::string& filename,
                        const std::string& query_path);
}  // namespace image_browser

#endif  // IMAGE_BROWSER_HPP_
