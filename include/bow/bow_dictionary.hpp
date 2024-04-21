#ifndef IPB_BOW_DICTIONARY_HPP_
#define IPB_BOW_DICTIONARY_HPP_

#include <iostream>

#include <opencv2/core/mat.hpp>

namespace ipb {
class BowDictionary {
 private:
  BowDictionary() = default;
  ~BowDictionary() = default;
  int max_iter_ = 0;
  int dict_size_ = 0;
  std::vector<cv::Mat> descriptors_;
  cv::Mat dictionary_;

 public:
  BowDictionary(const BowDictionary &) = delete;
  void operator=(const BowDictionary &) = delete;
  BowDictionary(const BowDictionary &&) = delete;
  void operator=(const BowDictionary &&) = delete;
  static BowDictionary &GetInstance() {
    static BowDictionary instance;
    return instance;
  }
  // Getters methods
  [[nodiscard]] int size() const;  // number of centroids / codewords
  [[nodiscard]] cv::Mat vocabulary() const;
  [[nodiscard]] bool empty() const;
  // Setters methods
  void set_vocabulary(const cv::Mat &dictionary);
  void build(const int &max_iter, const int &size,
             const std::vector<cv::Mat> &descriptors);
};
}  // namespace ipb
#endif  //