#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <utils/utils.cpp>


TEST(getDifference, exceptionEqualNumnerOfChannelsCase) {
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

TEST(getDifference, exception1Or3ChannelsCase) {
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

TEST(getDifference, 3ChannelsWithFirstImageAllZeros) {
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

TEST(getDifference, 3ChannelsWithSecondImageAllZeros) {
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

TEST(getDifference, 3ChannelsWithFirstImageAllMaxValues) {
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

TEST(getDifference, 3ChannelsWithSecondImageAllMaxValues) {
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

TEST(getDifference, 1ChannelWithFirstImageAllZeros) {
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

TEST(getDifference, 1ChannelWithSecondImageAllZeros) {
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

TEST(getDifference, 1ChannelWithFirstImageAllMaxValues) {
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

TEST(getDifference, 1ChannelWithSecondImageAllMaxValues) {
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