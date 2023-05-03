#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

#include <filters/filters.hpp>


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