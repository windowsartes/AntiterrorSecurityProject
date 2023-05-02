#include <vector>

#include <opencv2/opencv.hpp>

#include "utils.hpp"


std::vector<cv::String> getImagesFromFolder(std::string pathToData) {
    std::vector<cv::String> images;
    cv::glob(pathToData,
            images, false);
    
    return images;
}