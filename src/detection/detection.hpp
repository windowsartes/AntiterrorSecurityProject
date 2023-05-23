#pragma once


/// @brief This function is used to find the boundaries of an object; When detectObjects find a pixel with non-zero value, 
/// it passes its coordinates to this function, then findObject recursively finds borders of an object that given pixel belongs to;
/// These borders will be stored in a given variables: leftBorder, rightBorder, topBorder, bottomBorder;
/// @param thresholdedImage cv::Mat instance with 1 channel only; 
/// @param visited a datastructure that stores information about already visited pixels;
/// @param indexI row index of a given non-zero value pixel; 
/// @param indexJ column index of a given non-zero value pixel;
/// @param leftBorder a variable that represented a left border of the desired object;
/// @param rightBorder a variable that represented a right border of the desired object;
/// @param topBorder a variable that represented a top border of the desired object;
/// @param bottomBorder a variable that represented a bottom border of the desired object;
void findObject(cv::Mat& thresholdedImage, std::vector<std::vector<bool>>& visited, int indexI, int indexJ,
                            int& leftBorder, int& rightBorder, int& topBorder, int& bottomBorder);

/// @brief This function works with thresholded image, means the image can only have 1 channel and its pixels values can be either 0 or 255;
/// As a result it'll return a vector with found objects coordinates in Left-Right-Top-Bottom format;
/// @param thresholdedImage cv::Mat instance with 1 channel only;
/// @return a vector of vectors instance where coordinates of found objects stored if Left-Right-Top-Bottom format;
std::vector<std::vector<int>> detectObjects(cv::Mat thresholdedImage);