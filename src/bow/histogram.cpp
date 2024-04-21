#include "histogram.hpp"

#include <filesystem>
#include <fstream>

namespace ipb {
Histogram::Histogram(const cv::Mat& descriptors,
                     const ipb::BowDictionary& dictionary) {
  auto diction = dictionary.vocabulary();
  cv::Ptr<cv::FlannBasedMatcher> matcher = cv::FlannBasedMatcher::create();
  matcher->add(diction);
  matcher->train();
  Histogram histogram(descriptors, matcher, dictionary.size());
  data_ = histogram.data_;
}

Histogram::Histogram(const cv::Mat& descriptors,
                     const cv::Ptr<cv::FlannBasedMatcher>& matcher,
                     const int& diction_size) {
  std::vector<cv::DMatch> matches;
  matcher->match(descriptors, matches);
  if (!descriptors.empty()) {
    std::vector<int> data(diction_size, 0);
    for (const auto& m : matches) {
      data[m.trainIdx] += 1;
    }
    data_ = data;
  }
}

std::ostream& operator<<(std::ostream& os, const Histogram& hist) {
  for (auto i : hist.data_) {
    os << i << ", ";
  }
  return os;
}

void Histogram::WriteToCSV(const std::string& file_name) {
  std::ofstream out(file_name);
  out << data_.size() << std::endl;
  for (auto i : data_) {
    out << i << std::endl;
  }
}

Histogram Histogram::ReadFromCSV(const std::string& file_name) {
  std::ifstream in(file_name, std::ios_base::in);
  unsigned long size = 0;
  in >> size;
  std::vector<int> data;
  for (unsigned long i = 0; i < size; i++) {
    int num = 0;
    in >> num;
    data.push_back(num);
  }
  return Histogram(data);
}

std::vector<int> Histogram::get_occurences() {
  std::vector<int> hist_occurence(this->size(), 0);
  for (unsigned long i = 0; i < this->size(); i++) {
    if (data_[i] > 0) {
      hist_occurence[i] += 1;
    }
  }
  return hist_occurence;
}

int& Histogram::operator[](const size_t& i) { return data_[i]; }
int Histogram::operator[](const size_t& i) const { return data_[i]; }

std::vector<int> Histogram::data() const { return data_; }
unsigned long Histogram::size() const { return data_.size(); }
bool Histogram::empty() const { return data_.empty(); }
}  // namespace ipb
