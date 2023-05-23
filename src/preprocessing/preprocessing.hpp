#pragma once


/// @brief 
/// @param image 
/// @param mask 
/// @param useHistogramEqualization 
/// @return 
cv::Mat prepareImage(cv::Mat image, cv::Mat mask, bool useHistogramEqualization, cv::Size newSize);

/// @brief 
/// @param image 
/// @return 
cv::Mat equalizeHistRGB(cv::Mat image);