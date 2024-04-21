#ifndef QUERY_IMAGE_HPP_
#define QUERY_IMAGE_HPP_

#include <filesystem>
#include <tuple>
#include <vector>

#include "bow_dictionary.hpp"

namespace ipb {

using IndexedHist = std::tuple<float, std::vector<float>, std::string>;
using ScoredImage = std::tuple<std::string, float>;

class QueryImage {
 private:
  std::vector<int> query_histogram_;
  std::vector<int> query_occurence_;
  std::vector<float> query_histogram_tf_idf_;

 public:
  QueryImage() = default;
  QueryImage(const cv::Mat& query_descriptors,
             const ipb::BowDictionary& dictionary);
  [[nodiscard]] unsigned long size() const;
  std::vector<IndexedHist> tf_idf_histograms(
      const std::filesystem::path& hist_path);
  static std::vector<float> get_tf(const std::vector<int>& histogram,
                                   const int& num_images,
                                   const std::vector<int>& occurence);
  static float norm(const std::vector<float>& vec);
  static float cosine_similarity(const std::vector<float>& a,
                                 const std::vector<float>& b);
  std::vector<ScoredImage> get_similar_images(
      const std::filesystem::path& hist_path, const int& num_similar);
};
}  // namespace ipb

#endif  // QUERY_IMAGE_HPP_
