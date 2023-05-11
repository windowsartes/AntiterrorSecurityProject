#pragma once

/// @brief 
namespace grayscale {

    /// @brief 
    /// @param image 
    /// @param mask 
    /// @param useHistogramEqualization
    /// @return 
    cv::Mat prepareImage(cv::Mat image, cv::Mat mask, bool useHistogramEqualization);

}

int temp();