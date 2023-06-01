#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "utils.hpp"


std::vector<cv::String> getImagesFromFolder(std::string pathToData) {
    std::vector<cv::String> images;
    cv::glob(pathToData,
            images, false);
    
    return images;
}

cv::Mat getDifference(cv::Mat image1, cv::Mat image2) {
    if (image1.channels() != image2.channels()) {
        throw std::invalid_argument("First and second images must have the same number of channels;");
    }
    if ((image1.channels() != 3) && (image1.channels() != 1)) {
        throw std::invalid_argument("Images can have only 1 or 3 channels;");
    }

    int numberOfChannels = image1.channels();

    if (numberOfChannels == 3) {
        cv::Mat difference = cv::Mat(image1.size(), CV_16SC1, cv::Scalar(0));

        for (int indexI = 0; indexI < image1.rows; ++indexI) {
            for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
                int value1 = 0, value2 = 0;

                cv::Vec3b pixel1 = image1.at<cv::Vec3b>(indexI, indexJ);
                for (int i = 0; i < 3; ++i) {
                    value1 += short(pixel1[i]);
                }

                cv::Vec3b pixel2 = image2.at<cv::Vec3b>(indexI, indexJ);
                for (int i = 0; i < 3; ++i) {
                    value2 += short(pixel2[i]);
                }
                
                difference.at<short>(indexI, indexJ) = value1 - value2;
            }
        }

        return difference;
    }
    else {

        cv::Mat difference = cv::Mat(image1.size(), CV_16SC1, cv::Scalar(0));

        for (int indexI = 0; indexI < image1.rows; ++indexI) {
            for (int indexJ = 0; indexJ < image2.cols; ++indexJ) {
                int value1 = short(image1.at<uchar>(indexI, indexJ));
                int value2 = short(image2.at<uchar>(indexI, indexJ));

                difference.at<short>(indexI, indexJ) = value1 - value2;
            }
        }

        return difference.clone();
    }
}