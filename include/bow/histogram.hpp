#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/features2d.hpp>

#include "bow_dictionary.hpp"

namespace ipb {
class Histogram {
 public:
  explicit Histogram(const std::vector<int>& data) : data_{data} {}

  Histogram(const cv::Mat& descriptors, const ipb::BowDictionary& dictionary);

  Histogram(const cv::Mat& descriptors,
            const cv::Ptr<cv::FlannBasedMatcher>& matcher,
            const int& diction_size);

  Histogram() = default;

  friend std::ostream& operator<<(std::ostream& os, const Histogram& hist);
  void WriteToCSV(const std::string& file_name);
  static Histogram ReadFromCSV(const std::string& file_name);
  std::vector<int> get_occurences();
  int& operator[](const size_t& i);
  int operator[](const size_t& i) const;
  [[nodiscard]] std::vector<int> data() const;
  [[nodiscard]] unsigned long size() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] auto begin() const { return data_.begin(); }
  [[nodiscard]] auto cbegin() const { return data_.cbegin(); }
  [[nodiscard]] auto end() const { return data_.end(); }
  [[nodiscard]] auto cend() const { return data_.cend(); }

 private:
  std::vector<int> data_;
};
}  // namespace ipb

#endif  // HISTOGRAM_HPP_