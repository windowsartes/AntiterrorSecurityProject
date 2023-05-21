#include <working_surface/working_surface.hpp>

#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>


/*
******
*####*
**##**
**##**
*####*
*####*
*/
TEST(removeHoles, corner_case) {
    cv::Mat result = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexJ = 1; indexJ <= 4; ++indexJ) {
        result.at<uchar>(1, indexJ) = 255;
        result.at<uchar>(4, indexJ) = 255;
        result.at<uchar>(5, indexJ) = 255;
    }
    for (int indexJ = 2; indexJ <= 3; ++indexJ) {
        result.at<uchar>(2, indexJ) = 255;
        result.at<uchar>(3, indexJ) = 255;
    }

    cv::Mat answer = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 5; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }

    removeHoles(result);

    for (int indexI = 0; indexI < answer.rows; ++indexI) {
        for (int indexJ = 0; indexJ < answer.cols; ++indexJ) {
            ASSERT_TRUE(result.at<uchar>(indexI, indexJ) == answer.at<uchar>(indexI, indexJ));
        }
    }
}

/*
******
*####*
*####*
*####*
*####*
*####*
*/
TEST(removeHoles, corner_case_without_holes) {
    cv::Mat result = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 4; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            result.at<uchar>(indexI, indexJ) = 255;
        }
    }

    cv::Mat answer = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 4; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }

    removeHoles(result);

    for (int indexI = 0; indexI < answer.rows; ++indexI) {
        for (int indexJ = 0; indexJ < answer.cols; ++indexJ) {
            ASSERT_TRUE(result.at<uchar>(indexI, indexJ) == answer.at<uchar>(indexI, indexJ));
        }
    }
}

/*
******
*####*
*###**
**#*#*
*####*
******
*/
TEST(removeHoles, inner_case) {
    cv::Mat result = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexJ = 1; indexJ <= 4; ++indexJ) {
        result.at<uchar>(1, indexJ) = 255;
        result.at<uchar>(4, indexJ) = 255;
    }
    for (int indexJ = 1; indexJ <= 3; ++indexJ) {
        result.at<uchar>(2, indexJ) = 255;
    }
    result.at<uchar>(3, 2) = 255;
    result.at<uchar>(3, 4) = 255;

    cv::Mat answer = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 4; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }

    removeHoles(result);

    for (int indexI = 0; indexI < answer.rows; ++indexI) {
        for (int indexJ = 0; indexJ < answer.cols; ++indexJ) {
            ASSERT_TRUE(result.at<uchar>(indexI, indexJ) == answer.at<uchar>(indexI, indexJ));
        }
    }
}

/*
******
*####*
*####*
*####*
*####*
******
*/
TEST(removeHoles, inner_case_without_holes) {
    cv::Mat result = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 4; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            result.at<uchar>(indexI, indexJ) = 255;
        }
    }

    cv::Mat answer = cv::Mat::zeros(6, 6, CV_8U);
    for (int indexI = 1; indexI <= 4; ++indexI) {
        for (int indexJ = 1; indexJ <= 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }

    removeHoles(result);

    for (int indexI = 0; indexI < answer.rows; ++indexI) {
        for (int indexJ = 0; indexJ < answer.cols; ++indexJ) {
            ASSERT_TRUE(result.at<uchar>(indexI, indexJ) == answer.at<uchar>(indexI, indexJ));
        }
    }
}