#pragma once


/// @brief 
namespace RGB {

    /// @brief 
    /// @param image 
    /// @param mask 
    /// @param useHitigramEqualization 
    /// @return 
    cv::Mat prepareImage(cv::Mat image, cv::Mat mask, bool useHistogramEqualization);

    /// @brief 
    /// @param image 
    /// @return 
    cv::Mat equalizeHist(cv::Mat image);
}