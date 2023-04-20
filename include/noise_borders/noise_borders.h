#include <utility>
#include <string>
#include <stdexcept>

#include <opencv2/opencv.hpp>


/// @brief 
/// @param image1 
/// @param image2 
/// @return 
std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2);

/// @brief 
/// @param initialImage 
/// @param emptyImages 
/// @param mask 
/// @return 
std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages,
                                                 cv::Mat mask, std::string borderType);