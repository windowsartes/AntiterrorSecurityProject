#include <gtest/gtest.h>

#include <detection/detection.cpp>


TEST(find_object, square_1) {
cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    for (int i = 50; i < 150; ++i) {
        for (int j = 50; j < 150; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    int l = 50, r = 50, b = 50, t = 50;

    findObject(image, visited, 50, 50, l, r, t, b);

    ASSERT_TRUE((l == 50) && (r == 149) && (t == 50) && (b == 149));
}

TEST(find_object, rectangle_1) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);
    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    for (int i = 50; i < 150; ++i) {
        for (int j = 20; j < 30; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    int l = 20, r = 20, b = 50, t = 50;

    findObject(image, visited, 50, 20, l, r, t, b);

    ASSERT_TRUE((l == 20) && (r == 29) && (t == 50) && (b == 149));
}

TEST(find_object, corner_case_square) {
    cv::Mat image = cv::Mat::ones(200, 200, CV_8U);
    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    int l = 0, r = 0, b = 0, t = 0;

    findObject(image, visited, 0, 0, l, r, t, b);

    ASSERT_TRUE((l == 0) && (r == image.cols - 1) && (t == 0) && (b == image.rows - 1));
}

TEST(find_object, corner_case_wide_rectangle) {
    cv::Mat image = cv::Mat::ones(100, 200, CV_8U);
    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    int l = 0, r = 0, b = 0, t = 0;

    findObject(image, visited, 0, 0, l, r, t, b);

    ASSERT_TRUE((l == 0) && (r == image.cols - 1) && (t == 0) && (b == image.rows - 1));
}

TEST(find_object, corner_case_long_rectangle) {
    cv::Mat image = cv::Mat::ones(200, 100, CV_8U);
    std::vector<std::vector<bool>> visited(image.rows, std::vector<bool>(image.cols, false));

    int l = 0, r = 0, b = 0, t = 0;

    findObject(image, visited, 0, 0, l, r, t, b);

    ASSERT_TRUE((l == 0) && (r == image.cols - 1) && (t == 0) && (b == image.rows - 1));
}

TEST(detect_objects, empty_image) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    std::vector<std::vector<int>> objects = detectObjects(image);

    ASSERT_TRUE(objects.size() == 0);
}

TEST(detect_objects, 1_square) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    for (int i = 20; i < 100; ++i) {
        for (int j = 20; j < 100; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    std::vector<std::vector<int>> objects = detectObjects(image);

    ASSERT_TRUE(objects.size() == 1);

    std::vector<int> object1 = objects[0];

    ASSERT_TRUE((object1[0] == 20) && (object1[1] == 99) && (object1[2] == 20) && (object1[3] == 99));
}

TEST(detect_objects, 2_squares) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    for (int i = 20; i < 100; ++i) {
        for (int j = 20; j < 100; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }
    for (int i = 120; i < 160; ++i) {
        for (int j = 120; j < 160; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    std::vector<std::vector<int>> objects = detectObjects(image);
    
    ASSERT_TRUE(objects.size() == 2);

    std::vector<int> object1 = objects[0];
    std::vector<int> object2 = objects[1];

    ASSERT_TRUE((object1[0] == 20) && (object1[1] == 99) && (object1[2] == 20) && (object1[3] == 99));
    ASSERT_TRUE((object2[0] == 120) && (object2[1] == 159) && (object2[2] == 120) && (object2[3] == 159));
}

TEST(detect_objects, 2_squares_minimum_distance_shared_rows) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    for (int i = 20; i < 100; ++i) {
        for (int j = 20; j < 100; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }
    for (int i = 20; i < 100; ++i) {
        for (int j = 101; j < 160; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    std::vector<std::vector<int>> objects = detectObjects(image);
    
    ASSERT_TRUE(objects.size() == 2);

    std::vector<int> object1 = objects[0];
    std::vector<int> object2 = objects[1];

    ASSERT_TRUE((object1[0] == 20) && (object1[1] == 99) && (object1[2] == 20) && (object1[3] == 99));
    ASSERT_TRUE((object2[0] == 101) && (object2[1] == 159) && (object2[2] == 20) && (object2[3] == 99));
}

TEST(detect_objects, 2_squares_minimum_distance_shared_cols) {
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8U);

    for (int i = 20; i < 100; ++i) {
        for (int j = 20; j < 100; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }
    for (int i = 101; i < 150; ++i) {
        for (int j = 20; j < 100; ++j) {
            image.at<uchar>(i, j) = 1;
        }
    }

    std::vector<std::vector<int>> objects = detectObjects(image);
    
    ASSERT_TRUE(objects.size() == 2);

    std::vector<int> object1 = objects[0];
    std::vector<int> object2 = objects[1];

    ASSERT_TRUE((object1[0] == 20) && (object1[1] == 99) && (object1[2] == 20) && (object1[3] == 99));
    ASSERT_TRUE((object2[0] == 20) && (object2[1] == 99) && (object2[2] == 101) && (object2[3] == 149));
}

/*
Still don't know what to do with case like 

1100
0011

Is it 1 or 2 objects?
*/