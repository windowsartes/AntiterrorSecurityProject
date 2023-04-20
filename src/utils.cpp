#include "utils.h"


cv::Mat prepareImage(cv::Mat originalImage, cv::Size newSize, bool resize) {
    if (resize) {
        cv::resize(originalImage, originalImage, newSize);
    }
    cv::cvtColor(originalImage, originalImage, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(originalImage, originalImage);

    return originalImage;
}

std::vector<cv::String> getImagesFromFolder(std::string pathToData) {
    std::vector<cv::String> images;
    cv::glob(pathToData,
            images, false);
    
    return images;
}

cv::Mat prepareImage(cv::Mat image, cv::Mat mask) {
    image  = equalizeHistRGB(image);
    cv::Mat buffImage;
    image.copyTo(buffImage, mask);

    return buffImage;
}

cv::Mat equalizeHistRGB(cv::Mat image) {
    cv::Mat buffImage;
    cv::cvtColor(image, buffImage, cv::COLOR_BGR2YCrCb);

    std::vector<cv::Mat> channels(3);
    cv::split(buffImage, channels);   // Y, C_r, C_b

    cv::equalizeHist(channels[0], channels[0]);

    merge(channels, buffImage);

    cv::cvtColor(buffImage, buffImage, cv::COLOR_YCrCb2BGR);
    return buffImage;
}

cv::Mat getDifference(cv::Mat image1, cv::Mat image2, cv::Mat difference) {
    for (int indexI = 0; indexI < difference.rows; ++indexI) {
        for (int indexJ = 0; indexJ < difference.cols; ++indexJ) {
            cv::Vec3b pixel1 = image1.at<cv::Vec3b>(indexI, indexJ);
            cv::Vec3b pixel2 = image2.at<cv::Vec3b>(indexI, indexJ);
            int val1 = int(pixel1[0]) + int(pixel1[1]) + int(pixel1[2]);
            int val2 = int(pixel2[0]) + int(pixel2[1]) + int(pixel2[2]);
            difference.at<signed>(indexI, indexJ) = val1 - val2;
        }
    }
    return difference;
}

std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2) {
    int maxValue = -255*3 - 1; 
    int minValue = 255*3 + 1;
    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            cv::Vec3b pixel1 = image1.at<cv::Vec3b>(indexI, indexJ);
            cv::Vec3b pixel2 = image2.at<cv::Vec3b>(indexI, indexJ);
            int value1 = int(pixel1[0]) + int(pixel1[1]) + int(pixel1[2]);
            int value2 = int(pixel2[0]) + int(pixel2[1]) + int(pixel2[2]);
            
            int difference = value1 - value2;
            minValue = (difference < minValue) ? difference : minValue;
            maxValue = (maxValue < difference) ? difference : maxValue;
        }
    }
    return std::make_pair(minValue, maxValue);
}

std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask) {
    initialImage = prepareImage(initialImage, mask);

    std::vector<int> upperBorders, lowerBorders;
    std::pair<int, int> currentBorders;

    for (int indexI = 0; indexI < int(emptyImages.size()); ++indexI) {
        cv::Mat currentImage = cv::imread(emptyImages[indexI], cv::IMREAD_COLOR);
        currentImage = prepareImage(currentImage, mask);

        /*
        cv::Mat diff;
        cv::absdiff(initialImage, currentImage, diff);
        cv::imshow(emptyImages[indexI], diff);
        cv::waitKey(0);
        */

        currentBorders = getLocalUpperAndLowerBorder(initialImage, currentImage);
        upperBorders.push_back(currentBorders.second);
        lowerBorders.push_back(currentBorders.first);
    }

    for (int indexI = 0; indexI < int(lowerBorders.size()); ++indexI) {
        std::cout << lowerBorders[indexI] << " ";
    }

    std::cout << std::endl;

    for (int indexI = 0; indexI < int(upperBorders.size()); ++indexI) {
        std::cout << upperBorders[indexI] << " ";
    }

    std::cout << std::endl;

    std::vector<int>::iterator minValueIterator = std::min_element(lowerBorders.begin(), lowerBorders.end());
    std::vector<int>::iterator maxValueIterator = std::max_element(upperBorders.begin(), upperBorders.end());

    return std::make_pair(*minValueIterator, *maxValueIterator);
}  

/*
/// @brief 
/// @param image1 
/// @param image2 
/// @return 
cv::Mat getDifferenceMatrix(cv::Mat image1, cv::Mat image2) {

    cv::Mat difference(image1.size(), CV_16, cv::Scalar(0));

    for(int j=0; j < difference.rows; ++j) {
        for(int i=0; i< difference.cols; ++i){
            cv::Vec3b pix = diff.at<cv::Vec3b>(j,i);
            int val = (pix[0] + pix[1] + pix[2]);
            if(val>th){
                mask.at<unsigned char>(j,i) = 255;
            }
        }
    }
}
*/