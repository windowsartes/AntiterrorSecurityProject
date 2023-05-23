#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "detection.hpp"


void findObject(cv::Mat& thresholdedImage, std::vector<std::vector<bool>>& visited, int indexI, int indexJ,
                            int& leftBorder, int& rightBorder, int& topBorder, int& bottomBorder) {

    visited[indexI][indexJ] = true;
    
    if (indexI < topBorder) {
        topBorder = indexI;
    }
    if (indexI > bottomBorder) {
        bottomBorder = indexI;
    }
    if (indexJ < leftBorder) {
        leftBorder = indexJ;
    }
    if (indexJ > rightBorder) {
        rightBorder = indexJ;
    }

    if ((indexI - 1 >= 0) && (thresholdedImage.at<uchar>(indexI-1, indexJ)) && (!visited[indexI-1][indexJ])) {
        findObject(thresholdedImage, visited, indexI-1, indexJ, leftBorder, rightBorder, topBorder, bottomBorder);
    }
    if ((indexI + 1 < thresholdedImage.rows) && (thresholdedImage.at<uchar>(indexI+1, indexJ)) && (!visited[indexI+1][indexJ])) {
        findObject(thresholdedImage, visited, indexI+1, indexJ, leftBorder, rightBorder, topBorder, bottomBorder);
    }
    if ((indexJ - 1 >= 0) && (thresholdedImage.at<uchar>)(indexI, indexJ-1) && (!visited[indexI][indexJ-1])) {
        findObject(thresholdedImage, visited, indexI, indexJ-1, leftBorder, rightBorder, topBorder, bottomBorder);
    }
    if ((indexJ + 1 < thresholdedImage.cols) && (thresholdedImage.at<uchar>(indexI, indexJ+1)) && (!visited[indexI][indexJ+1])) {
        findObject(thresholdedImage, visited, indexI, indexJ+1, leftBorder, rightBorder, topBorder, bottomBorder);
    }    
}

std::vector<std::vector<int>> detectObjects(cv::Mat thresholdedImage) {
    if ((thresholdedImage.channels() != 1) || (thresholdedImage.type() != CV_8U)) {
        throw std::invalid_argument("Only 1-channel image with CV_8U type can be used there;");
    }

    std::vector<std::vector<bool>> visited(thresholdedImage.rows, std::vector<bool>(thresholdedImage.cols, false));
    std::vector<std::vector<int>> objects;
    int left, right, bottom, top;

    for (int indexI = 0; indexI < thresholdedImage.rows; ++indexI) {
        for (int indexJ = 0; indexJ < thresholdedImage.cols; ++indexJ) {
            if ((!visited[indexI][indexJ]) && (thresholdedImage.at<uchar>(indexI, indexJ))) {
                left = indexJ;
                right = indexJ;
                bottom = indexI;
                top = indexI;
                findObject(thresholdedImage, visited, indexI, indexJ, left, right, top, bottom);
                objects.push_back({left, right, top, bottom});
            }
        }
    }
    
    return objects;
}