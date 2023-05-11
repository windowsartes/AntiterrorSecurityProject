#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <utils/utils.cpp>


TEST(get_difference_3_channels, first_zeros) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(5));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-15));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_3_channels, second_zeros) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(5));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(0));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(15));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_3_channels, max_value) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(255));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(0));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(3*255));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_3_channels, min_value) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(255));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-3*255));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_1_channels, first_zeros) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC1, cv::Scalar::all(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC1, cv::Scalar::all(15));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-15));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_1_channels, second_zeros) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC1, cv::Scalar::all(15));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC1, cv::Scalar::all(0));

    cv::Mat result = getDifference(image1, image2);
    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(15));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_1_channel, max_value) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));

    cv::Mat result = getDifference(image1, image2);

    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(255));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}

TEST(get_difference_1_channel, min_value) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));

    cv::Mat result = getDifference(image1, image2);

    cv::Mat answer = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-255));

    for (int indexI = 0; indexI < image1.rows; ++indexI) {
        for (int indexJ = 0; indexJ < image1.cols; ++indexJ) {
            ASSERT_TRUE(result.at<short>(indexI, indexJ) == answer.at<short>(indexI, indexJ));
        }
    }
}