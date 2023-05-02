#pragma once

#include <utility>
#include <string>
#include <stdexcept>
#include <iostream>

#include <opencv2/opencv.hpp>

// #include "./../preprocessing/grayscale/preprocessing.h"
#include "../utils/utils.h"
#include "../preprocessing/grayscale/preprocessing.h"


/// @brief 
/// @param image1 
/// @param image2 
/// @return 
std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2);

/// @brief 
/// @param initialImage 
/// @param emptyImages 
/// @param mask 
/// @param borderType 
/// @return 
std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask,
                                                 std::string borderType, std::string imageType, bool useHistogramEqualization);