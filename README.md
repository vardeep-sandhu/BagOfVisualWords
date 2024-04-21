# C++ Final Project: "Place Recognition using Bag of Visual Words"

This provides an overview of how to run the project.

## Running the Project

In the generated folder results, the binary by the name of `main` in placed in the `bin` folder. This can be simply executed by running this binary with one argument as the destination of the folder where your images are kept.

For example:

`./main /path/of/images/`

- Results are automatically opened in the web browser through `display_bow_results.html`. Close the browser after inspection and return to terminal to move forward. The program runs in a loop reading query images till whenever the user wants.  

- Binaries of sift descriptors and histograms are generated in folders `bin` and `histogram` respectively in the `bow_data` folder. 

- Make sure your images are in the folder name `images`.

Webpage adapted from [here](https://templatemo.com/tm-500-fluid-gallery).