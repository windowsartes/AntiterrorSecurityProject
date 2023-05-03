/// @brief 
/// @param first_value 
/// @param last_value 
/// @return 
int getRandomNumber(int first_value, int last_value);

/// @brief 
/// @param values 
/// @return 
float getVectorMedian(std::vector<int> values);

/// @brief 
/// @param image1 
/// @param image2 
/// @return 
std::pair<int, int> getLocalUpperAndLowerBorder(cv::Mat image1, cv::Mat image2);

/// @brief 
/// @param initialImage 
/// @param emptyImages 
/// @param mask 
/// @param borderType 
/// @return 
std::pair<int, int> getGLobalUpperAndLowerBorder(cv::Mat initialImage, std::vector<cv::String> emptyImages, cv::Mat mask,
                                                 std::string borderType, std::string imageType, bool useHistogramEqualization);