#include <vector>

#include <opencv2/opencv.hpp>


/// @brief 
/// @param thresholdedImage 
/// @param visited 
/// @param indexI 
/// @param indexJ 
/// @param leftBorder 
/// @param rightBorder 
/// @param topBorder 
/// @param bottomBorder 
void findObject(cv::Mat& thresholdedImage, std::vector<std::vector<bool>>& visited, int indexI, int indexJ,
                            int& leftBorder, int& rightBorder, int& topBorder, int& bottomBorder);

/// @brief 
/// @param thresholdedImage 
/// @return 
std::vector<std::vector<int>> detectObjects(cv::Mat thresholdedImage);