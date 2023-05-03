#include <utility>
#include <string>
#include <stdexcept>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include "noise_borders.hpp"

#include <preprocessing/grayscale/preprocessing.hpp>
#include <preprocessing/RGB/preprocessing.hpp>


int getRandomNumber(int first_value, int last_value) {
    return first_value + rand() % last_value + 1;
}

float getVectorMedian(std::vector<int> values) {
    return 0;
}


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


std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask,
                                                 std::string borderType, std::string imageType, bool useHistogramEqualization) {
                                            
    if (imageType == "RGB") {
        initialImage = RGB::prepareImage(initialImage, mask, useHistogramEqualization);
    }
    else {
        if (imageType == "grayscale") {
            initialImage = grayscale::prepareImage(initialImage, mask, useHistogramEqualization);
        }
        else {
            throw std::invalid_argument("We can work only with RGB or grayscale images!");
        }
    }
    

    std::vector<int> upperBorders, lowerBorders;
    std::pair<int, int> currentBorders;

    for (int indexI = 0; indexI < int(emptyImages.size()); ++indexI) {
        cv::Mat currentImage = cv::imread(emptyImages[indexI], cv::IMREAD_COLOR);
    
        if (imageType == "RGB") {
            currentImage = RGB::prepareImage(currentImage, mask, useHistogramEqualization);
        }
        else {
            currentImage = grayscale::prepareImage(currentImage, mask, useHistogramEqualization);
        }

        currentBorders = getLocalUpperAndLowerBorder(initialImage, currentImage);
        lowerBorders.push_back(currentBorders.first);
        upperBorders.push_back(currentBorders.second);
    }

    std::cout << temp() << std::endl;
    
    for (int indexI = 0; indexI < int(lowerBorders.size()); ++indexI) {
        std::cout << lowerBorders[indexI] << " ";
    }

    std::cout << std::endl;

    for (int indexI = 0; indexI < int(upperBorders.size()); ++indexI) {
        std::cout << upperBorders[indexI] << " ";
    }

    std::cout << std::endl;

    if (borderType == "max") {
        std::vector<int>::iterator minValueIterator = std::min_element(lowerBorders.begin(), lowerBorders.end());
        std::vector<int>::iterator maxValueIterator = std::max_element(upperBorders.begin(), upperBorders.end());

        return std::make_pair(*minValueIterator, *maxValueIterator);
    }
    else {
        if (borderType == "mean") {
            float count = static_cast<float>(upperBorders.size());
            float meanUpperBorder = std::reduce(upperBorders.begin(), upperBorders.end()) / count;
            float meanLowerBorder = std::reduce(lowerBorders.begin(), lowerBorders.end()) / count;

            return std::make_pair(meanLowerBorder, meanUpperBorder);
        }
        else {
            if (borderType == "median") {
                int size = upperBorders.size();
                if (size % 2 == 1) {
                    std::nth_element(upperBorders.begin(), upperBorders.begin() + size/2, upperBorders.end());
                    std::nth_element(lowerBorders.begin(), lowerBorders.begin() + size/2, lowerBorders.end());

                    return std::make_pair(lowerBorders[size/2], upperBorders[size/2]);
                }
                else {
                    std::nth_element(upperBorders.begin(), upperBorders.begin() + size/2, upperBorders.end());
                    std::nth_element(upperBorders.begin(), upperBorders.begin() + (size - 1)/2, upperBorders.end());
                }
                
            }
            else {
                throw std::invalid_argument("Wrong border type;");
            }
        }
    }
}