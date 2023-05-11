#pragma once

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>


/// @brief 
/// @param  
/// @return 
std::vector<cv::String> getImagesFromFolder(std::string);

/// @brief 
/// @param firstImage 
/// @param secondImage 
/// @return 
cv::Mat getDifference(cv::Mat image1, cv::Mat image2);
