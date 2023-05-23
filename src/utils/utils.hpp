#pragma once


/// @brief a wapper for cv::glob function;
/// @param pathToData path to directory with images you want to get;
/// @return  std::vector of cv::String with path to every image from given directory;
std::vector<cv::String> getImagesFromFolder(std::string pathToData);

/// @brief This function computes the difference between two given images;
/// In the case of 1-channel images, difference will be computed as a substraction of first image and second image pixel-by-pixel;
/// In the case of 3-channel images, firstly for every pixel will be computed a sum of its 3 components, then the substraction will 
/// be computed pixel-by-pixel;
/// @param image1 cv::Mat instance; Image from which image 2 will be subtracted;
/// @param image2 cv::Mat instance; Image that will be substracted from image1;
/// @return difference between image1 and image2 as a cv::Mat instance wuth CV_16S type; 
cv::Mat getDifference(cv::Mat image1, cv::Mat image2);
