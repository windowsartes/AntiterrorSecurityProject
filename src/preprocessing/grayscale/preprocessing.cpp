#include "../../../include/preprocessing/grayscale/preprocessing.h"


cv::Mat grayscale::prepareImage(cv::Mat image, cv::Mat mask, bool useHitigramEqualization) {
    if (useHitigramEqualization) {
        cv::equalizeHist(image, image);
    }
    cv::Mat bufferImage;
    image.copyTo(bufferImage, mask);

    return image;
}