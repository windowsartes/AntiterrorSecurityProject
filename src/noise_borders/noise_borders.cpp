#include "../../include/noise_borders/noise_borders.h"


std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2) {
    if (image1.channels() != image2.channels()) {
        throw std::invalid_argument("First and second images must have the same number of channels!");
    }
    if ((image1.channels() != 3) && (image1.channels() != 1)) {
        throw std::invalid_argument("Images can have only 1 or 3 channels!");
    }
    int numberOfChannels = image1.channels();
    int maxValue = -255*numberOfChannels - 1; 
    int minValue = 255*numberOfChannels + 1;
    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            int value1 = 0, value2 = 0;

            if (numberOfChannels == 3) {
                cv::Vec3b pixel1 = image1.at<cv::Vec3b>(indexI, indexJ);
                cv::Vec3b pixel2 = image2.at<cv::Vec3b>(indexI, indexJ);
                for (int indexILocal = 0; indexILocal < 3; ++indexILocal) {
                    value1 += int(pixel1[indexILocal]);
                    value2 += int(pixel2[indexILocal]);
                }
            }
            else {
                value1 = int(image1.at<uchar>(indexI, indexJ));
                value2 = int(image2.at<uchar>(indexI, indexJ));
            }            
            int difference = value1 - value2;
            minValue = (difference < minValue) ? difference : minValue;
            maxValue = (maxValue < difference) ? difference : maxValue;
        }
    }
    return std::make_pair(minValue, maxValue);
}