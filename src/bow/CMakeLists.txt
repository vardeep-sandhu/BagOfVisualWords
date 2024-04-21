add_library(bow_dictionary bow_dictionary.cpp)
add_library(histogram histogram.cpp)
add_library(histogram_dataset histogram_dataset.cpp)
add_library(kmeans kmeans.cpp)
add_library(serialization serialize.cpp convert_dataset.cpp)
add_library(query_image query_image.cpp)
add_library(html html_writer.cpp image_browser.cpp)
add_library(bow bow_dictionary.cpp histogram.cpp kmeans.cpp serialize.cpp query_image.cpp html_writer.cpp image_browser.cpp convert_dataset.cpp histogram_dataset.cpp)
target_link_libraries(serialization ${OpenCV_LIBS})
target_link_libraries(kmeans ${OpenCV_LIBS})
target_link_libraries(bow_dictionary kmeans ${OpenCV_LIBS})
target_link_libraries(histogram bow_dictionary ${OpenCV_LIBS})
target_link_libraries(histogram_dataset bow_dictionary ${OpenCV_LIBS})
target_link_libraries(query_image histogram bow_dictionary serialization html ${OpenCV_LIBS})
target_link_libraries(bow ${OpenCV_LIBS})

install(TARGETS bow_dictionary histogram kmeans serialization query_image html 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
