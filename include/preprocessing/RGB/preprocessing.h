#include <opencv2/opencv.hpp>


/// @brief 
/// @param image 
/// @param mask 
/// @param useHitigramEqualization 
/// @return 
cv::Mat prepareImage(cv::Mat image, cv::Mat mask, bool useHitigramEqualization=true);

/// @brief 
/// @param image 
/// @return 
cv::Mat equalizeHist(cv::Mat image);