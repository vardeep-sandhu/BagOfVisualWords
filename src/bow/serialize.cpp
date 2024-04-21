#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/mat.hpp>

namespace ipb::serialization {
using std::ios_base;

void Serialize(const cv::Mat& m, const std::string& filename) {
  std::ofstream file(filename, ios_base::out | ios_base::binary);
  file.write(reinterpret_cast<const char*>(&m.rows), sizeof(m.rows));
  file.write(reinterpret_cast<const char*>(&m.cols), sizeof(m.cols));
  file.write(reinterpret_cast<char*>(m.data), m.rows * m.cols * m.elemSize());
}

cv::Mat Deserialize(const std::string& filename) {
  int row = 0;
  int col = 0;
  std::ifstream file(filename, ios_base::in | ios_base::binary);
  if (!file) {
    exit(EXIT_FAILURE);
  }
  file.read(reinterpret_cast<char*>(&row), sizeof(row));
  file.read(reinterpret_cast<char*>(&col), sizeof(col));
  long present = file.tellg();
  file.seekg(0, ios_base::end);
  long end = file.tellg();
  auto size_elem = (end - present) / (row * col);
  cv::Mat des_mat = cv::Mat_<float>(row, col);
  if (size_elem == 1) {
    des_mat = cv::Mat_<uchar>(row, col);
  }
  file.seekg(present);
  file.read(reinterpret_cast<char*>(des_mat.data), end - present);
  return des_mat;
}

}  // namespace ipb::serialization
