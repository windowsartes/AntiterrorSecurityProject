#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <noise_borders/noise_borders.hpp>
#include <utils/utils.hpp>


TEST(quickSelectMedian, exampleCase) {
    std::vector<int> testArray = {9,1,0,2,3,4,6,8,7,10,5};

    ASSERT_TRUE(quickSelectMedian(testArray) == 5);
}

TEST(quickSelectMedian, randomInputWithOddLengthCase) {
    for (int indexI = 0; indexI < 1000; indexI++) {
        int size = (rand() % 100)*2 + 1;
        std::vector<int> testArray = {};
        for (int indexJ = 0; indexJ < size; indexJ++) {
            testArray.push_back(rand() % 1000);
        }
        std::vector<int> testArrayCopy;
        testArrayCopy = testArray;
        float result = quickSelectMedian(testArrayCopy);

        std::sort(testArray.begin(), testArray.end());
        float answer = testArray[size/2];

        ASSERT_TRUE(result == answer);
    }
}

TEST(quickSelectMedian, randomInputWithEvenLengthCase) {
    for (int indexI = 0; indexI < 1000; indexI++) {
        int size = (rand() % 100 + 1)*2; // so size can't be 0; this case covered in the another test;
        std::vector<int> testArray = {};
        for (int indexJ = 0; indexJ < size; indexJ++) {
            testArray.push_back(rand() % 1000);
        }
        std::vector<int> testArrayCopy;
        testArrayCopy = testArray;
        float result = quickSelectMedian(testArrayCopy);


        std::sort(testArray.begin(), testArray.end());
        float answer = (static_cast<float>(testArray[size/2]) + testArray[(size-1)/2])/2;

        ASSERT_TRUE(result == answer);
    }
}

TEST(quickSelectMedian, emptyIectorCase) {
    std::vector<int> testArray = {};
    EXPECT_THROW({
        try {
            quickSelectMedian(testArray);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("This vector is empty;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(getRandomNumber, checkingForCorrectBorders) {
    srand(42);
    int bottom = 0, top = 100;
    for (int indexI = 0; indexI < 100000; ++indexI) {
        int currentValue = getRandomNumber(bottom, top);
        ASSERT_FALSE((currentValue < bottom) || (currentValue > top));
    }
}

TEST(quickSelect, exceptionNegativeStatisticsCase) {
    std::vector<int> input = {1, 2, 3};
    EXPECT_THROW({
        try {
            quickSelect(input, -1); 
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("k must be greater of equal to zero;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}


TEST(getLocalUpperAndLowerBorder, exception1Or3ChannelsCase) {
    cv::Mat image1(100, 100, CV_8UC2);
    cv::Mat image2(100, 100, CV_8UC2);
    EXPECT_THROW({
        try {
            getLocalUpperAndLowerBorder(image1, image2);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("Images can have only 1 or 3 channels;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(getLocalUpperAndLowerBorder, exceptionEqualChannelsCase) {
    cv::Mat image1(100, 100, CV_8UC1);
    cv::Mat image2(100, 100, CV_8UC3);
    EXPECT_THROW({
        try {
            getLocalUpperAndLowerBorder(image1, image2);
        }
        catch(const std::invalid_argument& exception) {
            EXPECT_STREQ("First and second images must have the same number of channels;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(getLocalUpperAndLowerBorder, storedRBGImageFirstCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_1_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_1_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -626) && (result.second == 644));
}

TEST(getLocalUpperAndLowerBorder, storedRBGImageSecondCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_2_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_2_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -662) && (result.second == 661));
}

TEST(getLocalUpperAndLowerBorder, storedRBGImageThirdCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_3_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_3_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -616) && (result.second == 610));
}

TEST(getLocalUpperAndLowerBorder, storedRBGImageFourthCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_4_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_4_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -657) && (result.second == 696));
}

TEST(getLocalUpperAndLowerBorder, storedRBGImageFifthCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_5_1.png", cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_5_2.png", cv::IMREAD_COLOR);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -654) && (result.second == 641));
}

TEST(getLocalUpperAndLowerBorder, storedGrayImageFirstCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_1_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_1_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}

TEST(getLocalUpperAndLowerBorder, storedGrayImageSecondCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_2_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_2_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 160));
}

TEST(getLocalUpperAndLowerBorder, storedGrayImageThirdCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_3_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_3_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}

TEST(getLocalUpperAndLowerBorder, storedGrayImageFourthCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_4_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_4_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -159) && (result.second == 160));
}

TEST(getLocalUpperAndLowerBorder, storedGrayImageFifthCase) {
    cv::Mat image1 = cv::imread("../tests/data/input/random_image_5_1_gray.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread("../tests/data/input/random_image_5_2_gray.png", cv::IMREAD_GRAYSCALE);

    std::pair<int, int> result = getLocalUpperAndLowerBorder(image1, image2); 

    ASSERT_TRUE((result.first == -160) && (result.second == 159));
}

TEST(thresholdImage, 16SMaxValueFirstCase) {
    cv::Mat image = cv::Mat(10, 10, CV_16SC1, cv::Scalar(255*3));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));

    cv::Mat result;
    result = thresholdImage(image, 0, 255*3);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 16SMaxValueSecondCase) {
    cv::Mat image = cv::Mat(10, 10, CV_16SC1, cv::Scalar(255*3));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));

    cv::Mat result;
    result = thresholdImage(image, 0, 255*3-1);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 16SMinValueFirstCase) {
    cv::Mat image = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-255*3));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));

    cv::Mat result;
    result = thresholdImage(image, -255*3, 0);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 16SMinValueSecondCase) {
    cv::Mat image = cv::Mat(10, 10, CV_16SC1, cv::Scalar(-255*3));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));

    cv::Mat result;
    result = thresholdImage(image, -255*3+1, 0);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 16SSimpleCase) {
    cv::Mat image = cv::Mat(5, 5, CV_16SC1, cv::Scalar(100));
    for (int indexI = 1; indexI < 4; ++indexI) {
        for (int indexJ = 1; indexJ < 4; ++indexJ) {
            image.at<short>(indexI, indexJ) = 200;
        }
    }
    
    cv::Mat answer = cv::Mat(5, 5, CV_8UC1, cv::Scalar(0));
    for (int indexI = 1; indexI < 4; ++indexI) {
        for (int indexJ = 1; indexJ < 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }
    
    cv::Mat result;
    result = thresholdImage(image, 0, 150);

    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 8UMaxValueFirstCase) {
    cv::Mat image = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));

    cv::Mat result;
    result = thresholdImage(image, 0, 255);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 8UMaxValueSecondCase) {
    cv::Mat image = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));

    cv::Mat result;
    result = thresholdImage(image, 0, 255-1);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 8UMinValueFirstCase) {
    cv::Mat image = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));

    cv::Mat result;
    result = thresholdImage(image, 0, 0);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 8UMinValueSecondCase) {
    cv::Mat image = cv::Mat(10, 10, CV_8UC1, cv::Scalar(0));
    cv::Mat answer = cv::Mat(10, 10, CV_8UC1, cv::Scalar(255));

    cv::Mat result;
    result = thresholdImage(image, 1, 0);
    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(thresholdImage, 8USimpleCase) {
    cv::Mat image = cv::Mat(5, 5, CV_8UC1, cv::Scalar(100));
    for (int indexI = 1; indexI < 4; ++indexI) {
        for (int indexJ = 1; indexJ < 4; ++indexJ) {
            image.at<uchar>(indexI, indexJ) = 200;
        }
    }
    
    cv::Mat answer = cv::Mat(5, 5, CV_8UC1, cv::Scalar(0));
    for (int indexI = 1; indexI < 4; ++indexI) {
        for (int indexJ = 1; indexJ < 4; ++indexJ) {
            answer.at<uchar>(indexI, indexJ) = 255;
        }
    }
    
    cv::Mat result;
    result = thresholdImage(image, 0, 150);

    for (int indexI = 0; indexI < result.rows; ++indexI) {
        for (int indexJ = 0; indexJ < result.cols; ++indexJ) {
            ASSERT_TRUE(answer.at<uchar>(indexI, indexJ) == result.at<uchar>(indexI, indexJ));
        }
    }
}

TEST(getGlobalUpperAndLowerBorder, exception1Or3ChannelsCase) {
    cv::Mat initialImage = cv::Mat::zeros(10, 10, CV_8UC2);
    cv::Mat mask = cv::Mat::zeros(10, 10, CV_8U);

    EXPECT_THROW({
        try {
            getGlobalUpperAndLowerBorder(initialImage, getImagesFromFolder("../data/input"), mask, "max", true);
        } 
        catch(const std::invalid_argument& exception) {
            ASSERT_STREQ("Initial image can have either 3 or 1 channel;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(getGlobalUpperAndLowerBorder, exceptionEmptyImagesCase) {
    cv::Mat initialImage = cv::Mat::zeros(10, 10, CV_8UC2);
    cv::Mat mask = cv::Mat::zeros(10, 10, CV_8U);

    EXPECT_THROW({
        try {
            getGlobalUpperAndLowerBorder(initialImage, getImagesFromFolder("this_path_doesnt_exist"), mask, "max", true);
        } 
        catch(const std::invalid_argument& exception) {
            ASSERT_STREQ("Initial image can have either 3 or 1 channel;", exception.what());
            throw;
        }
    }, std::invalid_argument);
}