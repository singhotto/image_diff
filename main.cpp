#include <iostream>
#include "./utils/ImageHandler.hh"

int main() {
    ImageHandler handler;

    for(int i = 0; i<500; i++){
        std::string curr = std::to_string(i);
        // Load the two images
        cv::Mat image1 = handler.load(curr + ".png");
        cv::Mat image2 = handler.load(curr + "_2.png");

        // Ensure the images are of the same size and type
        if (image1.size() != image2.size() || image1.type() != image2.type()) {
            std::cerr << "The images must have the same size and type!" << std::endl;
            return -1;
        }

        cv::Mat result = handler.showDifference(image1, image2);

        handler.save("result_" + curr + ".png", result);
    }

    return 0;
}
