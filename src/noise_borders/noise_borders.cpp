#include <utility>
#include <string>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <stdlib.h>
#include <vector>

#include <opencv2/opencv.hpp>

#include "noise_borders.hpp"
#include <preprocessing/preprocessing.hpp>


int getRandomNumber(int first_value, int last_value) {
    return first_value + rand() % (last_value + 1);
}

float quickSelectMedian(std::vector<int> values) {
    if (!values.size()) {
        throw std::invalid_argument("This vector is empty;");
    }
    if (values.size() % 2 == 0) {
        return (quickSelect(values, values.size()/2) + quickSelect(values, (values.size()-1)/2))/2;
    }
    return quickSelect(values, values.size()/2);
}

float quickSelect(std::vector<int> values, int k) {
    if (k < 0) {
        throw std::invalid_argument("k must be greater of equal to zero;");
    }

    if (values.size() == 1) {
        return values[0];
    }

    int pivot = values[getRandomNumber(0, values.size() - 1)];

    std::vector<int> less = {}, equal = {}, greater = {};

    for (auto elem : values) {
        if (elem < pivot) {
            less.push_back(elem);
        }
        else {
            if (elem == pivot) {
                equal.push_back(elem);
            }
            else {
                greater.push_back(elem);
            }
        }
    }

    if (k < less.size()) {
        return quickSelect(less, k);
    }
    if (k < less.size() + equal.size()) {
        return equal[0];
    }
    else {
        return quickSelect(greater, k - less.size() - equal.size());
    }
}


std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2) {

    if (image1.channels() != image2.channels()) {
        throw std::invalid_argument("First and second images must have the same number of channels;");
    }
    if ((image1.channels() != 3) && (image1.channels() != 1)) {
        throw std::invalid_argument("Images can have only 1 or 3 channels;");
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


std::pair<float, float> getGlobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask,
                                                     std::string borderType, bool useHistogramEqualization) {
    int channels = initialImage.channels();
    if ((channels !=3) || (channels != 1)) {
        throw std::invalid_argument("Initial image can have either 3 or 1 channel;");
    }
    if (emptyImages.empty()) {
        throw std::invalid_argument("Vector of empty images must contain images;");
    }

    initialImage = prepareImage(initialImage, mask, useHistogramEqualization, initialImage.size());
    
    std::vector<int> upperBorders = {}, lowerBorders = {};
    std::pair<int, int> currentBorders;

    for (int indexI = 0; indexI < int(emptyImages.size()); ++indexI) {
        cv::Mat currentImage;
    
        if (channels == 3) {
            currentImage = cv::imread(emptyImages[indexI], cv::IMREAD_COLOR);
            currentImage = prepareImage(currentImage, mask, useHistogramEqualization, initialImage.size());
        }
        else {
            currentImage = cv::imread(emptyImages[indexI], cv::IMREAD_GRAYSCALE);
            currentImage = prepareImage(currentImage, mask, useHistogramEqualization, initialImage.size());
        }

        currentBorders = getLocalUpperAndLowerBorder(initialImage, currentImage);
        lowerBorders.push_back(currentBorders.first);
        upperBorders.push_back(currentBorders.second);
    }

    // zero means there is no noise so we'll remove it;
    lowerBorders.erase(std::remove(lowerBorders.begin(), lowerBorders.end(), 0), lowerBorders.end());
    upperBorders.erase(std::remove(upperBorders.begin(), upperBorders.end(), 0), upperBorders.end());

    if (borderType == "max") {
        std::vector<int>::iterator minValueIterator = std::min_element(lowerBorders.begin(), lowerBorders.end());
        std::vector<int>::iterator maxValueIterator = std::max_element(upperBorders.begin(), upperBorders.end());

        return std::make_pair(*minValueIterator, *maxValueIterator);
    }
    else {
        if (borderType == "mean") {
            float count = static_cast<float>(upperBorders.size());
            float meanUpper = std::reduce(upperBorders.begin(), upperBorders.end()) / count;
            float meanLower = std::reduce(lowerBorders.begin(), lowerBorders.end()) / count;

            return std::make_pair(meanLower, meanUpper);
        }
        else {
            if (borderType == "median") {
                float medianLower = quickSelectMedian(lowerBorders), medianUpper = quickSelectMedian(upperBorders);
                
                return std::make_pair(medianLower, medianUpper);
            }
            else {
                throw std::invalid_argument("Wrong border type;");
            }
        }
    }
}

cv::Mat thresholdImage(cv::Mat image, float lowerBorder, float upperBorder) {
    if (image.channels() != 1) {
        throw std::invalid_argument("There image must have only 1 channel;");
    }
    if ((image.type() != CV_16SC1) && (image.type() != CV_8U)) {
        throw std::invalid_argument("Image type must be either 16SC1 or 8US1;");
    }

    cv::Mat imageThresholded(image.size(), CV_8UC1, cv::Scalar(0));
    if (image.type() == CV_16SC1) {
        for (int indexI = 0; indexI < image.rows; ++indexI) {
            for (int indexJ = 0; indexJ < image.cols; ++indexJ) {
                if ((float(image.at<short>(indexI, indexJ)) > upperBorder) || float((image.at<short>(indexI, indexJ)) < lowerBorder)) {
                    imageThresholded.at<uchar>(indexI, indexJ) = 255;
                }
            }
        }
    }
    else {
        for (int indexI = 0; indexI < image.rows; ++indexI) {
            for (int indexJ = 0; indexJ < image.cols; ++indexJ) {
                if ((float(image.at<uchar>(indexI, indexJ)) > upperBorder) || float((image.at<uchar>(indexI, indexJ)) < lowerBorder)) {
                    imageThresholded.at<uchar>(indexI, indexJ) = 255;
                }
            }
        }
    }

    return imageThresholded;
}