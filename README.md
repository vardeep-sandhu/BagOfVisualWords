# Place Recognition using Bag of Visual Words

Place recognition using Bag of Visual Words (BoVW) in C++ is a method in computer vision for identifying and matching locations or scenes based on visual features extracted from images. It involves representing images with local descriptors, quantizing them into a visual vocabulary, and generating histograms of visual word occurrences. This approach is widely used in tasks like image retrieval and scene recognition, and typically involves libraries like OpenCV for implementation. 

More information on this project can be found on [this page](https://www.youtube.com/watch?v=HWIkcMakz-s&pp=ygUeYmFnIG9mIHZpc3VhbCB3b3JkcyBzdGFjaG5pc3Mg)

This project was built as the final project from the course "Modern C++ for Computer Vision and Image Processing", taught by [Ignacio Vizzo](https://github.com/nachovizzo). This project was a jointly built by [Yash Goel](https://github.com/yash-goel) and myself.

## Running the Project

In the generated folder results, the binary by the name of `main` in placed in the `bin` folder. This can be simply executed by running this binary with one argument as the destination of the folder where your images are kept.

For example:

`./main /path/of/images/`

- Results are automatically opened in the web browser through `display_bow_results.html`. Close the browser after inspection and return to terminal to move forward. The program runs in a loop reading query images till whenever the user wants.  

- Binaries of sift descriptors and histograms are generated in folders `bin` and `histogram` respectively in the `bow_data` folder. 

- Make sure your images are in the folder name `images`.

Webpage adapted from [here](https://templatemo.com/tm-500-fluid-gallery).