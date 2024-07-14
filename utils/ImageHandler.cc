#include "ImageHandler.hh"

cv::Mat ImageHandler::load(std::string str)
{
    assert(str.size() > 0);

    std::string file_path = "../images/" + str;

    // Load the two images
    cv::Mat image = cv::imread(file_path, cv::IMREAD_COLOR);
    // Check if the images were loaded successfully
    if (image.empty())
        std::cerr << "Could not open or find the images!" << std::endl;

    return image;
}

void ImageHandler::show(cv::Mat &image)
{
    cv::imshow("Result Image", image);
    // Wait for a key press indefinitely
    cv::waitKey(0);
}

void ImageHandler::save(std::string name, cv::Mat &image)
{
    // save the result
    cv::imwrite("../result/" + name, image);
}

cv::Mat ImageHandler::subtract(cv::Mat &image1, cv::Mat &image2)
{

    // Create a matrix to store the result
    cv::Mat result;

    // Subtract the second image from the first
    cv::subtract(image1, image2, result);

    return result;
}

void ImageHandler::cleanImage(cv::Mat &image)
{

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Iterate over the image
    for (int row = 0; row < grayImage.rows; ++row)
    {
        for (int col = 0; col < grayImage.cols; ++col)
        {
            uchar &value = grayImage.at<uchar>(row, col);

            if (value > 100)
            {
                value = 255;
            }
            else
            {
                value = 0;
            }
        }
    }

    int range = 4;
    // Iterate over the image using cv::Mat::at<T>(int row, int col)
    for (int row = 0; row < grayImage.rows - range; ++row)
    {
        for (int col = 0; col < grayImage.cols - range; ++col)
        {
            uchar value = grayImage.at<uchar>(row, col);
            bool isBlank = true;
            for (int i = 0; i < range; i += range - 1)
            {
                for (int j = 0; j < range; j++)
                {
                    if (grayImage.at<uchar>(row + i, col + j) > 0)
                    {
                        isBlank = false;
                    }
                }
            }

            for (int i = 0; i < range; i += range - 1)
            {
                for (int j = 0; j < range; j++)
                {
                    if (grayImage.at<uchar>(row + j, col + i) > 0)
                    {
                        isBlank = false;
                    }
                }
            }
            if (isBlank)
            {
                for (int i = 0; i < range; i++)
                {
                    for (int j = 0; j < range; j++)
                    {
                        grayImage.at<uchar>(row + j, col + i) = 0;
                    }
                }
            }
        }
    }

    cv::GaussianBlur(grayImage, grayImage, cv::Size(31, 31), 0);

    // Iterate over the grayImage
    for (int row = 0; row < grayImage.rows; ++row)
    {
        for (int col = 0; col < grayImage.cols; ++col)
        {
            uchar &value = grayImage.at<uchar>(row, col);

            if (value > 0)
            {
                value = 255;
            }
            else
            {
                value = 0;
            }
        }
    }

    image = grayImage;
}



void ImageHandler::markShape(cv::Mat &image, const std::vector<std::vector<cv::Point>> &contours)
{
    // Draw bounding boxes around each contour
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Rect boundingBox = cv::boundingRect(contours[i]);
        cv::rectangle(image, boundingBox, cv::Scalar(0, 255, 0), 1);
    }
}

std::vector<std::vector<cv::Point>> ImageHandler::findCorners(cv::Mat &image)
{
    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

cv::Mat ImageHandler::showDifference(cv::Mat &image1, cv::Mat &image2)
{
    cv::Mat result = subtract(image1, image2);

    cleanImage(result);

    const std::vector<std::vector<cv::Point>> contours = findCorners(result);

    markShape(image2, contours);

    return image2;
}
