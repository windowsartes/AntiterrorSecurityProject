#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

#include <filters/filters.hpp>

TEST(exception, wrong_number_of_channels) {
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

TEST(exception, wrong_input_type) {
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

TEST(exception, even_kernel_size) {
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

TEST(exception, negative_kernel_size) {
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

TEST(white_image, square) {
    cv::Mat image = cv::imread("../tests/data/input/white_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(white_image, rectangular_long) {
    cv::Mat image = cv::imread("../tests/data/input/white_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(white_image, rectangular_wide) {
    cv::Mat image = cv::imread("../tests/data/input/white_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/white_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);

    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(black_image, square) {
    cv::Mat image = cv::imread("../tests/data/input/black_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_square.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(black_image, rectangular_long) {
    cv::Mat image = cv::imread("../tests/data/input/black_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_rectangular_long.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(black_image, rectangular_wide) {
    cv::Mat image = cv::imread("../tests/data/input/black_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/input/black_rectangular_wide.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(random_image, square_1) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(random_image, square_2) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(random_image, square_3_kernel_size_3) {
    cv::Mat image = cv::imread("../tests/data/input/random_square_3.png", cv::IMREAD_GRAYSCALE);
    cv::Mat answer = cv::imread("../tests/data/answer/answer_random_square_3_size_3.png", cv::IMREAD_GRAYSCALE);
    cv::Mat result = maxNeighbourFilter(image, 3);
    
    ASSERT_TRUE(answer.size() == result.size());
    ASSERT_TRUE(countNonZero(cv::Mat(result - answer)) == 0);
}

TEST(random_image, square_3_kernel_size_5) {
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