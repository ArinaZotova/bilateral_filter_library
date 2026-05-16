#pragma once

#include <opencv2/core.hpp>

namespace bf {

double gaussian(double x, double sigma);

double colorDistance(int color1, int color2);

void bilateralFilterCustom(const cv::Mat& src,
                           cv::Mat& dst,
                           int d,
                           double sigmaColor,
                           double sigmaSpace);

} // namespace bf
