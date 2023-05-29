#pragma once


/// @brief This filter changes pixel's value to the most popular value of pixel's neigbours in given radius; So the bright zones will be 
/// brighter and dark zone will be darker;
/// By convention, given image can only have 1 channel and its pixels value can be either 0 or 255;
/// @param image cv::Mat instance with only 1 channel;
/// @param kernelSize a size of a kernel that will be applied to every pixel; Radius in the description means kernelSize a floor of kernelSize / 2;
/// @return cv::Mat instance with applied filter;
cv::Mat maxNeighbourFilter(cv::Mat image, int kernelSize);