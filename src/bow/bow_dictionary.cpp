#include "bow_dictionary.hpp"

#include "kmeans.hpp"

namespace ipb {
int BowDictionary::size() const { return dictionary_.rows; }

cv::Mat BowDictionary::vocabulary() const { return dictionary_; }

bool BowDictionary::empty() const { return dictionary_.empty(); }

void BowDictionary::set_vocabulary(const cv::Mat &dictionary) {
  dictionary_ = dictionary;
}

void BowDictionary::build(const int &max_iter, const int &size,
                          const std::vector<cv::Mat> &descriptors) {
  max_iter_ = max_iter;
  dict_size_ = size;
  descriptors_ = descriptors;
  dictionary_ = ipb::kMeans(descriptors_, dict_size_, max_iter_);
}
}  // namespace ipb