#include <opencv2/opencv.hpp>

#include "preprocessing.hpp"


cv::Mat grayscale::prepareImage(cv::Mat image, cv::Mat mask, bool useHistogramEqualization) {
    if (useHistogramEqualization) {
        cv::equalizeHist(image, image);
    }
    cv::Mat bufferImage;
    image.copyTo(bufferImage, mask);

    return image;
}

int temp() {
    return 6;
}