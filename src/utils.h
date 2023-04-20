#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <stddef.h>

#include <opencv2/opencv.hpp>


/// @brief 
/// @param  
/// @param  
/// @param resize 
/// @return 
cv::Mat prepareImage(cv::Mat, cv::Size, bool resize=false); // done

/// @brief 
/// @param  
/// @return 
std::vector<cv::String> getImagesFromFolder(std::string); // done

/// @brief 
/// @param image 
/// @param mask 
/// @return 
cv::Mat prepareImage(cv::Mat image, cv::Mat mask); // done

/// @brief 
/// @param image 
/// @return 
cv::Mat equalizeHistRGB(cv::Mat image); // done

/// @brief 
/// @param initialImage 
/// @param emptyImages 
/// @param mask 
/// @return 
std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask);

/// @brief
/// @param image1 
/// @param image2 
/// @param difference 
cv::Mat getDifference(cv::Mat image1, cv::Mat image2, cv::Mat difference);

/// @brief 
/// @param image1 
/// @param image2 
/// @return 
std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2, int& argMax, int& argMin);

/// @brief 
/// @param image1 
/// @param image2 
/// @return 
cv::Mat getDifferenceMatrix(cv::Mat image1, cv::Mat image2);