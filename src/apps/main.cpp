#include "bow.h"
#include "utils/current_path.hpp"

int main(int argc, char* argv[]) {
  std::string img_path;
  img_path = argv[argc - 1];

  const std::filesystem::path image_file_path(img_path);
  const auto& hist_path =
      image_file_path.parent_path().parent_path().string() + "/histogram/";
  const auto& bin_path =
      image_file_path.parent_path().parent_path().string() + "/bin/";

  // convert the sifts to binary files for easier access
  ipb::serialization::sifts::ConvertDataset(img_path);

  // define and get the dictionary using k-means
  auto& dictionary = ipb::BowDictionary::GetInstance();
  const int max_iter = 10;
  const int dict_size = 50;
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);

  dictionary.build(max_iter, dict_size, descriptors);

  // get histogram based on the dictionary for each image (include tf-idf) and
  // saves in hist_path
  ipb::GetHistograms(bin_path, dictionary);

  // loop for query image
  bool take_query = true;
  while (take_query) {
    // take input of query image
    std::cout << "\n Enter query image path or a random image is selected from "
                 "database for query if enter is pressed:";

    std::string query_path;
    getline(std::cin, query_path);
    if (query_path.empty()) {
      for (const auto& bin : std::filesystem::directory_iterator(img_path)) {
        query_path = bin.path().string();
        break;
      }
    }

    // 9 similiar images
    int num_similar_imgs = 9;

    // extract descriptors out of the query image
    cv::Mat query_descriptors =
        ipb::serialization::sifts::GetDescriptors(query_path);

    ipb::QueryImage query_img(query_descriptors, dictionary);

    std::vector<image_browser::ScoredImage> rows =
        query_img.get_similar_images(hist_path, num_similar_imgs);

    const std::string html_path = "webpage/display_bow_results.html";

    image_browser::CreateImageBrowser("BoVW", "style.css", rows, html_path,
                                      query_path);

    std::string web_command = "xdg-open " + html_path;
    const char* command = web_command.c_str();
    system(command);

    std::cout << std::endl
              << "The browser was opened with the results. Close the browser "
                 "and press enter to continue in terminal."
              << std::endl
              << std::endl;

    std::string enter;
    std::getline(std::cin, enter);

    std::cout << std::endl
              << "Do you want to query for more images? Press 'N/n' to "
                 "finish program and any other key to query more: "
              << std::endl;
    std::string continue_ques;
    std::getline(std::cin, continue_ques);
    if (continue_ques[0] == 'N' || continue_ques[0] == 'n') {
      take_query = false;
    }
  }
  return 0;
}
