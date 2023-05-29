#include <stdexcept>
#include <string>

#include <opencv2/imgproc.hpp>

#include "working_surface.hpp"


void checkPixel(cv::Mat& image, std::vector<std::vector<bool>>& visited, cv::Mat& surface, int indexI, int indexJ) {
        
    surface.at<uchar>(indexI, indexJ) = 255;    
    visited[indexI][indexJ] = true;

    if ((indexI - 1 >= 0) && (image.at<uchar>(indexI-1, indexJ) == 0) && (!visited[indexI-1][indexJ])) {
        checkPixel(image, visited, surface, indexI-1, indexJ);
    }
    if ((indexI + 1 < image.rows) && (image.at<uchar>(indexI+1, indexJ) == 0) && (!visited[indexI+1][indexJ])) {
        checkPixel(image, visited, surface, indexI+1, indexJ);
    }
    if ((indexJ - 1 >= 0) && (image.at<uchar>(indexI, indexJ-1) == 0) && (!visited[indexI][indexJ-1])) {
        checkPixel(image, visited, surface, indexI, indexJ-1);
    }
    if ((indexJ + 1 < image.cols) && (image.at<uchar>(indexI, indexJ+1) == 0) && (!visited[indexI][indexJ+1])) {
        checkPixel(image, visited, surface, indexI, indexJ+1);
    }
}

void removeHoles(cv::Mat& surface) {
    std::vector<int> topBorders, bottomBorders;
    
    for (int indexJ = 0; indexJ < surface.cols; ++indexJ) {

        bool found = false;
        for (int indexI = 0; indexI < surface.rows; ++indexI) {
            if (surface.at<uchar>(indexI, indexJ) == 255) {
                topBorders.push_back(indexI);
                found = true;
                break;
            }
        }
        if (!found) {
            topBorders.push_back(surface.rows);
        }
        
        found = false;
        for (int indexI = surface.rows - 1; indexI >= 0; --indexI) {
            if (surface.at<uchar>(indexI, indexJ) == 255) {
                bottomBorders.push_back(indexI);
                found = true;
                break;
            }
        }
        if (!found) {
            bottomBorders.push_back(-1);
        }
    }

    for (int indexI = 0; indexI < surface.rows; ++indexI) {
        for (int indexJ = 0; indexJ < surface.cols; ++indexJ) {
            if (surface.at<uchar>(indexI, indexJ) != 255) {
                if ((indexI <= bottomBorders[indexJ]) && (indexI >= topBorders[indexJ])) {
                    surface.at<uchar>(indexI, indexJ) = 255;
                }
            }
        }
    }
}


cv::Mat findSurface(cv::Mat image) {
    if (image.channels() == 3) {
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    }
    if (image.channels() != 1) {
        throw std::invalid_argument("Only 3- or 1-channel image is allowes here;");
    }

    cv::resize(image, image, cv::Size(image.cols/4, image.rows/4));
    cv::equalizeHist(image, image);

    int lowThreshold = 65;
    int kernel_size = 3;
    float ratio = 3.5;

    cv::Mat detectedEdges;
    cv::blur(image, detectedEdges, cv::Size(3,3));
    cv::Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold*ratio, kernel_size);

    cv::dilate(detectedEdges, detectedEdges, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));

    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    cv::Point2d leftTopPount = cv::Point2d(detectedEdges.cols*(0.4), detectedEdges.rows*(0.4));
    cv::Point2d rightBottomPoint = cv::Point2d(detectedEdges.cols*(0.6), detectedEdges.rows*(0.6));

    cv::Mat surface = cv::Mat::zeros(image.rows, image.cols, CV_8U);

    for (int indexI = leftTopPount.y; indexI < rightBottomPoint.y; ++indexI) {
        for (int indexJ = leftTopPount.x; indexJ < rightBottomPoint.x; ++indexJ) {
            if ((!detectedEdges.at<uchar>(indexI, indexJ)) && !(visited[indexI][indexJ])) {
                checkPixel(detectedEdges, visited, surface, indexI, indexJ);
            }
        }
    }

    cv::resize(surface, surface, cv::Size(surface.cols*4, surface.rows*4));

    removeHoles(surface);

    cv::threshold(surface, surface, 1, 255, cv::THRESH_BINARY);

    cv::imwrite("../mask/mask_computed.jpg", surface);

    return surface.clone();
}