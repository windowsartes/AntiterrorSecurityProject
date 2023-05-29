#pragma once

#include <vector>

#include <opencv2/opencv.hpp>


/// @brief When findSurface finds surface pixel, this function will be called. It recursively find all pixel, that belongs to the 
/// working surface;
/// @param image cv::Mat instance; it have be already resized and transformed with Canny filter in findSurface function;
/// @param visited vector of vectors with bools that stores information about already visited pixels
/// @param surface sufrace you want to find on given image;
/// @param indexI row index of given sufrace pixel;
/// @param indexJ column index of given surface pixel;
void checkPixel(cv::Mat& image, std::vector<std::vector<bool>>& visited, cv::Mat& surface, int indexI, int indexJ);

/// @brief Canny algorithm is ideal so sometimes there are some holes inside computed surface; This function removes them;
/// @param surface cv::Mat instance representing the sufrace where you want to remove holes; 
void removeHoles(cv::Mat& surface);

/// @brief This function computes a mask from working sufrace from given image; Image will be 4 times resized, then gaussian blur
/// and Canny filter will be applied to it; Using checkPixel function a working sufrace will be found, then it will be improved with 
/// removeHoles. Resulting image will be saved as "mask_computed.jpg" ./mask/ directory and returned as a cv::Mat instance with
/// 1 channel and only 0 or 255 value in its pixels;
/// @param image cv::Mat instance where you want to find a working surface;
/// @return cv::Mat instance representing a mask with computed working surface;
cv::Mat findSurface(cv::Mat image);