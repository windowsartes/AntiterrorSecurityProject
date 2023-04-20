#include "../../include/filters/filters.h"


cv::Mat maxNeighbourFilter(cv::Mat image, int kernelSize) {
    int radius = kernelSize/2;
    cv::Mat filteredImage(image.size(), CV_8UC1);

    for (int indexI = 0; indexI < image.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image.cols; ++ indexJ) {
            int valueWhite = 0, valueBlack = 0;
            for (int indexILocal = -radius; indexILocal <= radius; ++indexILocal) {
                for (int indexJLocal = -radius; indexJLocal <= radius; ++indexJLocal) {
                    if (((indexI + indexILocal < image.rows) && (indexI + indexILocal >= 0)) &&
                        ((indexJ + indexJLocal < image.cols) && (indexJ + indexJLocal >= 0))) {

                        uint currentValue = image.at<uchar>(indexI + indexILocal, indexJ + indexJLocal);

                        if (currentValue == 255) {
                            ++valueWhite;
                        }
                        else {
                            ++valueBlack;
                        }
                    }
                }
            }
            if (valueWhite == valueBlack) {
                filteredImage.at<uchar>(indexI, indexJ) = image.at<uchar>(indexI, indexJ);
            }
            else {
                if (valueWhite > valueBlack) {
                    filteredImage.at<uchar>(indexI, indexJ) = 255;
                }
                else {
                    filteredImage.at<uchar>(indexI, indexJ) = 0;
                }
            }
        }
    }

    return filteredImage;
}