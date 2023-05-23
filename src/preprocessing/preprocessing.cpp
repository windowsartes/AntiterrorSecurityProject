#include <opencv2/opencv.hpp>

#include "preprocessing.hpp"

#include <stdexcept>


cv::Mat prepareImage(cv::Mat image, cv::Mat mask, bool useHistogramEqualization, cv::Size newSize) {
    int channels = image.channels();
    if ((channels != 3) && (channels != 1)) {
        throw std::invalid_argument("Only 3- or 1-channel images can be used here;");
    }

    if (channels == 3) { 
        if ((image.cols != newSize.width) && (image.rows != newSize.height)) {
            cv::resize(image, image, newSize, 0, 0, cv::INTER_LINEAR);
        }

        cv::Mat imageRisezed = image.clone();

        if (useHistogramEqualization) {
            imageRisezed = equalizeHistRGB(imageRisezed);
        }
    
        cv::Mat imageMasked;
        imageRisezed.copyTo(imageMasked, mask);

        return imageMasked;
    }

    if ((image.cols != newSize.width) && (image.rows != newSize.height)) {
        cv::resize(image, image, newSize, 0, 0, cv::INTER_LINEAR);
    }

    cv::Mat imageRisezed = image.clone();

    if (useHistogramEqualization) {
        cv::equalizeHist(imageRisezed, imageRisezed);
    }

    cv::Mat imageMasked;
    imageRisezed.copyTo(imageMasked, mask);

    return imageMasked;
}

cv::Mat equalizeHistRGB(cv::Mat image) {
    cv::Mat buffImage;
    cv::cvtColor(image, buffImage, cv::COLOR_BGR2YCrCb);

    std::vector<cv::Mat> channels(3);
    cv::split(buffImage, channels);   // Y, C_r, C_b

    cv::equalizeHist(channels[0], channels[0]);

    merge(channels, buffImage);

    cv::cvtColor(buffImage, buffImage, cv::COLOR_YCrCb2BGR);
    return buffImage;
}