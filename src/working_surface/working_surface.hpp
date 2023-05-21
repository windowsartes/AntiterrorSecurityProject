#include <opencv2/opencv.hpp>
#include <string>


/// @brief 
/// @param image 
/// @param visited 
/// @param surface 
/// @param indexI 
/// @param indexJ 
/// @param it 
void checkPixel(cv::Mat& image, std::vector<std::vector<bool>>& visited, cv::Mat& surface, int indexI, int indexJ, int it);

/// @brief 
/// @param image 
void removeHoles(cv::Mat& image);

/// @brief 
/// @param image 
/// @return 
cv::Mat findSurface(cv::Mat image);