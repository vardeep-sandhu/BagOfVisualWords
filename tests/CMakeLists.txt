# ~~~
# @file      CMakeLists.txt
# @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
#
# Copyright (c) 2020 Ignacio Vizzo, all rights reserved
find_package(GTest REQUIRED)

set(TEST_BINARY ${PROJECT_NAME}_test)

add_executable(${TEST_BINARY} test_bow_dictionary.cpp test_histograms.cpp test_query_image.cpp test_convert_dataset.cpp test_serialize.cpp test_browser.cpp test_kmeans.cpp test_dataset.cpp test_data.cpp)

target_link_libraries(${TEST_BINARY} bow GTest::Main ${OpenCV_LIBS})

gtest_discover_tests(${TEST_BINARY})
