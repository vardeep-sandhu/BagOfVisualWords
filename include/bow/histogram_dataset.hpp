#ifndef HISTOGRAM_DATASET_HPP_
#define HISTOGRAM_DATASET_HPP_

#include <filesystem>

#include "bow_dictionary.hpp"

namespace ipb {
void GetHistograms(const std::filesystem::path& bin_path,
                   const ipb::BowDictionary& dictionary);
}  // namespace ipb

#endif  // HISTOGRAM_DATASET_HPP_