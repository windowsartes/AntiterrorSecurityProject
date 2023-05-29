#pragma once


/// @brief This function will return a random value from the interval [first_value, last_value];
/// @param first_value lower limit of the interval, included;
/// @param last_value upper limit of the interval, included;
/// @return an int instance from the interval [first_value, last_value];
int getRandomNumber(int first_value, int last_value);

/// @brief This function will return a k-statistics of a given vector of int;
/// @param values a vector of ints instance; Must be not empty;
/// @param k a K-statistic you want to find;
/// @return a float instance representing k-statistic of a given array;
float quickSelect(std::vector<int> values, int k);

/// @brief This function will return a median of a given vector of int;
/// @param values a vector of ints instance, must be not empty;
/// @return a float instance representing the median of a given array;
float quickSelectMedian(std::vector<int> values);

/// @brief This function substracts second given image, image2, from first given image, image1; Then computes minimal and maximum 
/// pixel values from resulting image and return it as a std::pair of ints; If given images have 1 channel, substracion will be
/// just pixel-by-pixel, if they have 3 channels, for every pixel of image1, function will sum values in its 3 components,
/// then sum values of pixel's components for every pixel in image2, then the substraction will be computed; 
/// @param image1 cv::Mat instance; Image from which image 2 will be subtracted;
/// @param image2 cv::Mat instance; Image that will be substracted from image1;
/// @return std::pair instance with lower and upper border of image1 and image2 substraction;
std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2);

/// @brief This function applies getLocalUpperAndLowerBorder to initialImage and every image from emptyImages one-by-one;
/// As a result, you get a vector of lower borders and a vector of upper borders; Then using borderType parameter, final estimation 
/// for both lower and upper border will be computed;
/// @param initialImage cv::Mat instance representing empty image you got at the very beginning of elevator's work;
/// @param emptyImages std::vector instance with path to images without any unnecessary items in the cabine;
/// @param mask binaty mask that will be applied to every image to highlight a working surface;
/// @param borderType std::string instance that can be either "max" or "mean" or "median"; 
/// @param useHistogramEqualization binary parameter which tells the function whether to use istogramEqualization for every images or not;
/// @return 
std::pair<float, float> getGlobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask,
                                                     std::string borderType, bool useHistogramEqualization);

/// @brief This function will threshold given image with given lower and upper bordrs. Means that every pixel with value bigger than
/// upper border or lower than lower border will produce 255 in returned image, in other cases, it will produce 0;
/// @param image cv::Mat instance you want to threshold;
/// @param lowerBorder lower border for pizels' values;
/// @param upperBorder upper border for pizels' values;
/// @return cv::Mat instance of type CV_8U with only 0 and 255 values;
cv::Mat thresholdImage(cv::Mat image, float lowerBorder, float upperBorder);