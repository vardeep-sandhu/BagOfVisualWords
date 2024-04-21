#ifndef HTML_WRITER_H_
#define HTML_WRITER_H_

#include <fstream>
#include <string>

namespace ipb {
class html_writer {
 public:
  html_writer() = default;
  explicit html_writer(const std::string& filename);
  void OpenDocument();
  void CloseDocument();
  void AddCSSStyle(const std::string& stylesheet);
  void AddTitle(const std::string& title);
  void AddNavigation();
  void OpenBody();
  void CloseBody();
  void OpenRow();
  void QueryImage(const std::string& query_path);
  void AddImage(const std::string& img_path, float score);
  void RestStuff();

 private:
  std::ofstream outfile;
};
}  // namespace ipb
#endif  // HTML_WRITER_H_
