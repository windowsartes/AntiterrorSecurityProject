#pragma once


/// @brief 
/// @param pathToData
/// @return 
std::vector<cv::String> getImagesFromFolder(std::string pathToData);

/// @brief 
/// @param firstImage 
/// @param secondImage 
/// @return 
cv::Mat getDifference(cv::Mat image1, cv::Mat image2);
