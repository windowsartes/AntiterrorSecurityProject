#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

#include <filters/filters.hpp>

TEST(maxNeighbourFilter, exceptionWrongNumberOfChannelsCase) {
    cv::Mat image = cv::Mat::zeros(10, 10, CV_8UC3);
    EXPECT_THROW({
        try {
            maxNeighbourFilter(image, 3);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Only 1-channel image can be used there;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(maxNeighbourFilter, exceptionWrongInputTypeCase) {
    cv::Mat image = cv::Mat::zeros(10, 10, CV_16SC1);
    EXPECT_THROW({
        try {
            maxNeighbourFilter(image, 3);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Only 1-channel image can be used there;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(maxNeighbourFilter, exceptionEvenKernelSizeCase) {
    cv::Mat image = cv::Mat::zeros(10, 10, CV_8U);
    EXPECT_THROW({
        try {
            maxNeighbourFilter(image, 2);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Kernel size must be an odd number;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(maxNeighbourFilter, exceptionNegativeKernelSizeCase) {
    cv::Mat image = cv::Mat::zeros(10, 10, CV_8U);
    EXPECT_THROW({
        try {
            maxNeighbourFilter(image, -3);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Kernel size must be a positive number;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(maxNeighbourFilter, whiteSquareCase) {
    cv::Mat image = cv::imread("../tests/data/input/white_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, whiteLongRectangleCase) {
    cv::Mat image = cv::imread("../tests/data/input/white_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, whiteWideRectangleCase) {
    cv::Mat image = cv::imread("../tests/data/input/white_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);

    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, blackSquareCase) {
    cv::Mat image = cv::imread("../tests/data/input/black_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, blackLongRectangleCase) {
    cv::Mat image = cv::imread("../tests/data/input/black_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, blackWideRectangleCase) {
    cv::Mat image = cv::imread("../tests/data/input/black_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, storedRandomSquareFirstCase) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, storedRandomSquareSecondCase) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, storedRandomSquareThirdCase) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_3.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_3_size_3.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(maxNeighbourFilter, storedRandomSquareThirdCase2) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_3.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_3_size_5.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 5);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}