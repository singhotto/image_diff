#ifndef IMAGE_LOADER_HH
#define IMAGE_LOADER_HH

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cassert>

class ImageHandler
{
private:
    cv::Mat subtract(cv::Mat& image1, cv::Mat& image2);

    void cleanImage(cv::Mat& image);

    void markShape(cv::Mat& image, const std::vector<std::vector<cv::Point>> &contours);

    std::vector<std::vector<cv::Point>> findCorners(cv::Mat& image);
public:
    cv::Mat load(std::string name);
    void show(cv::Mat& image);
    void save(std::string name, cv::Mat& image);

    cv::Mat showDifference(cv::Mat& image1, cv::Mat& image2);
};


#endif