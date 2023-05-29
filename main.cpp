#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <utils/utils.hpp>
#include <utils/utils.hpp>
#include <noise_borders/noise_borders.hpp>
#include <detection/detection.hpp>
#include <filters/filters.hpp>
#include <working_surface/working_surface.hpp>
#include <preprocessing/preprocessing.hpp>


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Please, specify the path to the image you want to check;" << std::endl;
        return 1;
    }
    cv::Mat mask = cv::imread("../mask/mask_computed.jpg", cv::IMREAD_GRAYSCALE);

    cv::Mat startImage = cv::imread("../data/background/empty/image_07.jpg", cv::IMREAD_COLOR);
    cv::Mat startImagePrepared = prepareImage(startImage, mask, false, startImage.size());

    std::string pathToImage = argv[1];
    cv::Mat image = cv::imread(pathToImage, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Please, chack the path to your image: it's incorrect;" << std::endl;
        return 2;
    }

    cv::Mat imageToDraw = image.clone();

    cv::Mat imagePrepared = prepareImage(image, mask, false, startImage.size());

    cv::Mat difference = getDifference(startImagePrepared, imagePrepared);
    cv::Mat ImageThresholded = thresholdImage(difference, -390.875, 308.125);

    for (int indexI = 0; indexI < 4; ++indexI) {
        ImageThresholded = maxNeighbourFilter(ImageThresholded, 3);
    }

    for (int indexI = 0; indexI < 4; ++indexI) {
        cv::dilate(ImageThresholded, ImageThresholded, getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
    }

    std::vector<std::vector<int>> objects = detectObjects(ImageThresholded);

    cv::Mat ObjectsDetected = makeRectangles(imageToDraw, objects);

    cv::Mat ObjectsDetectedResized;
    cv::resize(ObjectsDetected, ObjectsDetectedResized, cv::Size(), 0.7, 0.7);

    cv::imshow("Detected objects", ObjectsDetectedResized);
    cv::waitKey(0);
        
    if (argc >= 3) {
        std::string saveFlag = argv[2];
        if (saveFlag == "-s") {
            if (argc < 4) {
                std::cerr << "Please, specify the path to directory where you want to save the result;" << std::endl;
                return 3;
            }
            std::string pathToSave = argv[3];
            int length = pathToSave.size();
            if (pathToSave[length - 1] == '/') {
                cv::imwrite(pathToSave + "result.jpg", ObjectsDetected);

                return 0;
            }
            cv::imwrite(pathToSave + "/result.jpg", ObjectsDetected);

            return 0;
        }
    }

    return 0;
}