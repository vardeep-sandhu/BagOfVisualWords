#include "html_writer.hpp"

#include <filesystem>

namespace ipb {

html_writer::html_writer(const std::string& filename) {
  outfile.open(filename, std::ofstream::out);
}
void html_writer::OpenDocument() {
  outfile << "<!DOCTYPE html>" << std::endl;
  outfile << R"(<html lang="en">)" << std::endl;
}

void html_writer::AddTitle(const std::string& title) {
  outfile << "<title>" << title << "</title>" << std::endl;
}

void html_writer::CloseDocument() { outfile << "</html>\n" << std::endl; }

void html_writer::AddCSSStyle(const std::string& stylesheet) {
  outfile << "<head>" << std::endl;
  outfile << R"(<link rel="stylesheet" type="text/css" href=")" << stylesheet
          << R"(" />)" << std::endl;
  outfile
      << R"(<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600">
)" << std::endl;
  outfile
      << R"(<link rel="stylesheet" href="Font-Awesome-4.7/css/font-awesome.min.css">
)" << std::endl;
  outfile << R"(<link rel="stylesheet" href="css/bootstrap.min.css">
)" << std::endl;
  outfile << R"(<link rel="stylesheet" href="css/hero-slider-style.css">
)" << std::endl;
  outfile << R"(<link rel="stylesheet" href="css/magnific-popup.css">
)" << std::endl;
  outfile << R"(<link rel="stylesheet" href="css/templatemo-style.css">
)" << std::endl;
  outfile << R"(<script src="js/jquery-1.11.3.min.js"></script>
)" << std::endl;
  outfile << R"(<script>

        var tm_gray_site = false;

        if (tm_gray_site) {
            $('html').addClass('gray');
        }
        else {
            $('html').removeClass('gray');
        }
    </script>)"
          << std::endl;
  outfile << "</head>" << std::endl;
}

void html_writer::OpenBody() { outfile << "<body>" << std::endl; }

void html_writer::AddNavigation() {
  outfile << R"(<div class="cd-slider-nav">
            <nav class="navbar">
                <div class="tm-navbar-bg">

                    <a class="navbar-brand text-uppercase" href="#"><i class="fa fa-picture-o tm-brand-icon"></i>BAG OF
                        VISUAL WORDS
                    </a>

                    <button class="navbar-toggler hidden-lg-up" type="button" data-toggle="collapse"
                        data-target="#tmNavbar">
                        &#9776;
                    </button>

                </div>
            </nav>
        </div>)";

  outfile << R"()" << std::endl;
}

void html_writer::OpenRow() {
  // outfile << R"(<div class="row">)" << std::endl;
  outfile << R"(<ul class="cd-hero-slider">

            <!-- Page 1 Gallery One -->
            <li class="selected">
                <div class="cd-full-width">
                    <div class="container-fluid js-tm-page-content" data-page-no="1" data-page-type="gallery">
                        <div class="tm-img-gallery-container">
                            <div class="tm-img-gallery gallery-one">)";
}

void html_writer::QueryImage(const std::string& query_path) {
  outfile << R"(<div class="grid-item">)" << std::endl;
  outfile << R"(<figure class="effect-sadie">)" << std::endl;
  outfile << R"(<img src=")" << query_path
          << R"(" alt="Image" class="img-fluid tm-img">)";
  outfile << R"(<figcaption>)" << std::endl;
  outfile << R"( <h2 class="tm-figure-title">)"
          << "Query Image"
          << R"(</h2>)" << std::endl;
  // outfile << R"(<p class="tm-figure-description">)" << score << "</p>";
  outfile << R"(<a href=")" << query_path << R"("></a>)";
  outfile << R"(</figcaption>)" << std::endl;
  outfile << R"(</figure>)" << std::endl;
  outfile << R"(</div>)" << std::endl;
}

void html_writer::AddImage(const std::string& img_path, float score) {
  outfile << R"(<div class="grid-item">)" << std::endl;
  outfile << R"(<figure class="effect-sadie">)" << std::endl;
  outfile << R"(<img src=")" << img_path
          << R"(" alt="Image" class="img-fluid tm-img">)";
  outfile << R"(<figcaption>)" << std::endl;
  outfile << R"( <h3 class="tm-figure-title">)"
          << std::filesystem::path(img_path).stem().string() << R"(</h3>)"
          << std::endl;
  outfile << R"(<p class="tm-figure-description">)" << score << "</p>";
  outfile << R"(<a href=")" << img_path << R"("></a>)";
  outfile << R"(</figcaption>)" << std::endl;
  outfile << R"(</figure>)" << std::endl;
  outfile << R"(</div>)" << std::endl;
}

void html_writer::CloseBody() { outfile << "</body>\n"; }

void html_writer::RestStuff() {
  outfile << R"(<script src="js/tether.min.js"></script> 
                <script src="js/bootstrap.min.js"></script>
                <script src="js/hero-slider-main.js"></script>
                <script src="js/jquery.magnific-popup.min.js"></script>

                <script>

                    function adjustHeightOfPage(pageNo) {

                        var pageContentHeight = 0;

                        var pageType = $('div[data-page-no="' + pageNo + '"]').data("page-type");

                        if (pageType != undefined && pageType == "gallery") {
                            pageContentHeight = $(".cd-hero-slider li:nth-of-type(" + pageNo + ") .tm-img-gallery-container").height();
                        }
                        else {
                            pageContentHeight = $(".cd-hero-slider li:nth-of-type(" + pageNo + ") .js-tm-page-content").height() + 20;
                        }

                        // Get the page height
                        var totalPageHeight = $('.cd-slider-nav').height()
                            + pageContentHeight
                            + $('.tm-footer').outerHeight();

                        // Adjust layout based on page height and window height
                        if (totalPageHeight > $(window).height()) {
                            $('.cd-hero-slider').addClass('small-screen');
                            $('.cd-hero-slider li:nth-of-type(' + pageNo + ')').css("min-height", totalPageHeight + "px");
                        }
                        else {
                            $('.cd-hero-slider').removeClass('small-screen');
                            $('.cd-hero-slider li:nth-of-type(' + pageNo + ')').css("min-height", "100%");
                        }
                    }

                    $(window).load(function () {

                        adjustHeightOfPage(1); // Adjust page height

                        $('.gallery-one').magnificPopup({
                            delegate: 'a', // child items selector, by clicking on it popup will open
                            type: 'image',
                            gallery: { enabled: true }
                        });


                        $('#tmNavbar a').click(function () {
                            $('#tmNavbar').collapse('hide');

                            adjustHeightOfPage($(this).data("no")); // Adjust page height       
                        });

                        $(window).resize(function () {
                            var currentPageNo = $(".cd-hero-slider li.selected .js-tm-page-content").data("page-no");

                            // wait 3 seconds
                            setTimeout(function () {
                                adjustHeightOfPage(currentPageNo);
                            }, 1000);

                        });
                    });


                </script>
)";
}
}  // namespace ipb