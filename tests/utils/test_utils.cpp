#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <utils/utils.cpp>


TEST(get_difference, exception_equal_numner_of_channels) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC1, cv::Scalar::all(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC3, cv::Scalar::all(5));

    EXPECT_THROW({
        try {
            getDifference(image1, image2);
        } 
        catch(const std::invalid_argument& exception) {
            ASSERT_STREQ("First and second images must have the same number of channels;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(get_difference, exception_1_or_3_channels) {
    cv::Mat image1 = cv::Mat(10, 10, CV_8UC2, cv::Scalar::all(0));
    cv::Mat image2 = cv::Mat(10, 10, CV_8UC2, cv::Scalar::all(5));

    EXPECT_THROW({
        try {
            getDifference(image1, image2);
        } 
        catch(const std::invalid_argument& exception) {
            ASSERT_STREQ("Images can have only 1 or 3 channels;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(get_difference, 3_channels_first_zeros) {
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

TEST(get_difference, 3_channels_second_zeros) {
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

TEST(get_difference, 3_channels_max_value) {
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

TEST(get_difference, 3_channels_min_value) {
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

TEST(get_difference, 1_channel_first_zeros) {
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

TEST(get_difference, 1_channel_second_zeros) {
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

TEST(get_difference, 1_channel_max_value) {
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

TEST(get_difference, 1_channel_min_value) {
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