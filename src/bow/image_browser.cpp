#include "image_browser.hpp"

#include "html_writer.hpp"

void image_browser::CreateImageBrowser(const std::string &title,
                                       const std::string &stylesheet,
                                       const std::vector<ScoredImage> &rows,
                                       const std::string &filename,
                                       const std::string &query_path) {
  ipb::html_writer outfile(filename);
  outfile.OpenDocument();
  outfile.AddTitle(title);
  outfile.AddCSSStyle(stylesheet);
  outfile.OpenBody();
  outfile.AddNavigation();
  outfile.OpenRow();
  outfile.QueryImage(query_path);
  for (const auto &i : rows) {
    outfile.AddImage(std::get<0>(i), std::get<1>(i));
  }
  outfile.RestStuff();
  outfile.CloseBody();
  outfile.CloseDocument();
}