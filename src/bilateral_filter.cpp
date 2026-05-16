#include "bilateral_filter/bilateral_filter.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace bf {

double gaussian(double x, double sigma) {
    if (sigma <= 0.0) {
        throw std::invalid_argument("sigma must be positive");
    }

    return std::exp(-(x * x) / (2.0 * sigma * sigma));
}

double colorDistance(int color1, int color2) {
    return std::abs(color1 - color2);
}

namespace {

int clampToByte(double value) {
    value = std::round(value);
    value = std::clamp(value, 0.0, 255.0);
    return static_cast<int>(value);
}

void validateInput(const cv::Mat& src,
                   int d,
                   double sigmaColor,
                   double sigmaSpace) {
    if (src.empty()) {
        throw std::invalid_argument("source image is empty");
    }

    if (src.type() != CV_8UC1) {
        throw std::invalid_argument("only grayscale CV_8UC1 images are supported");
    }

    if (d <= 0) {
        throw std::invalid_argument("filter diameter must be positive");
    }

    if (sigmaColor <= 0.0 || sigmaSpace <= 0.0) {
        throw std::invalid_argument("sigmaColor and sigmaSpace must be positive");
    }
}

} // namespace

void bilateralFilterCustom(const cv::Mat& src,
                           cv::Mat& dst,
                           int d,
                           double sigmaColor,
                           double sigmaSpace) {
    validateInput(src, d, sigmaColor, sigmaSpace);

    dst = cv::Mat::zeros(src.size(), src.type());

    const int radius = d / 2;

    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            const int centerValue = src.at<uchar>(y, x);

            double weightedSum = 0.0;
            double weightsSum = 0.0;

            for (int dy = -radius; dy <= radius; ++dy) {
                const int yy = std::clamp(y + dy, 0, src.rows - 1);

                for (int dx = -radius; dx <= radius; ++dx) {
                    const int xx = std::clamp(x + dx, 0, src.cols - 1);

                    const int currentValue = src.at<uchar>(yy, xx);

                    const double spatialDistance =
                        std::sqrt(static_cast<double>(dx * dx + dy * dy));

                    const double intensityDistance =
                        colorDistance(centerValue, currentValue);

                    const double spatialWeight =
                        gaussian(spatialDistance, sigmaSpace);

                    const double colorWeight =
                        gaussian(intensityDistance, sigmaColor);

                    const double weight = spatialWeight * colorWeight;

                    weightedSum += weight * currentValue;
                    weightsSum += weight;
                }
            }

            dst.at<uchar>(y, x) =
                static_cast<uchar>(clampToByte(weightedSum / weightsSum));
        }
    }
}

} // namespace bf
