#include "../../../include/preprocessing/RGB/preprocessing.h"


cv::Mat RGB::prepareImage(cv::Mat image, cv::Mat mask, bool useHitigramEqualization) {
    if (useHitigramEqualization) {
        image  = equalizeHist(image);
    }
    cv::Mat buffImage;
    image.copyTo(buffImage, mask);

    return buffImage;
}

cv::Mat RGB::equalizeHist(cv::Mat image) {
    cv::Mat buffImage;
    cv::cvtColor(image, buffImage, cv::COLOR_BGR2YCrCb);

    std::vector<cv::Mat> channels(3);
    cv::split(buffImage, channels);   // Y, C_r, C_b

    cv::equalizeHist(channels[0], channels[0]);

    merge(channels, buffImage);

    cv::cvtColor(buffImage, buffImage, cv::COLOR_YCrCb2BGR);
    return buffImage;
}