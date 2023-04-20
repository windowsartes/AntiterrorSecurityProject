#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "../../include/noise_borders/noise_borders.h"


TEST(exception, 1_or_3_channels) {
    cv::Mat image1(100, 100, CV_8UC2);
    cv::Mat image2(100, 100, CV_8UC2);
    EXPECT_THROW({
        try {
            getLocalUpperAndLowerBorder(image1, image2);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Images can have only 1 or 3 channels!", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(exception, equal_channels) {
    cv::Mat image1(100, 100, CV_8UC1);
    cv::Mat image2(100, 100, CV_8UC3);
    EXPECT_THROW({
        try {
            getLocalUpperAndLowerBorder(image1, image2);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("First and second images must have the same number of channels!", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(RBG, random_image_0) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_0_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_0_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -626) && (result.second == 644));
}

TEST(RBG, random_image_1) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_1_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_1_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -662) && (result.second == 661));
}

TEST(RBG, random_image_2) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_2_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_2_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -616) && (result.second == 610));
}

TEST(RBG, random_image_3) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_3_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_3_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -657) && (result.second == 696));
}

TEST(RBG, random_image_4) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_4_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_4_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -654) && (result.second == 641));
}

TEST(gray, random_image_0) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_0_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_0_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}

TEST(gray, random_image_1) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_1_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_1_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 160));
}

TEST(gray, random_image_2) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_2_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_2_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}

TEST(gray, random_image_3) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_3_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_3_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -159) && (result.second == 160));
}

TEST(gray, random_image_4) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_4_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_4_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}