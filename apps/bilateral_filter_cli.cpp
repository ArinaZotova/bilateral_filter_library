#include "bilateral_filter/bilateral_filter.hpp"

#include <opencv2/imgcodecs.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace {

void printUsage(const char* appName) {
    std::cerr
        << "Usage:\n"
        << "  " << appName
        << " <input_image> <output_image> <diameter> <sigma_color> <sigma_space>\n\n"
        << "Example:\n"
        << "  " << appName << " input.png output.png 10 100 10\n";
}

int parseInt(const std::string& value, const std::string& name) {
    try {
        size_t processed = 0;
        const int result = std::stoi(value, &processed);

        if (processed != value.size()) {
            throw std::invalid_argument("extra characters");
        }

        return result;
    } catch (...) {
        throw std::invalid_argument("invalid integer value for " + name + ": " + value);
    }
}

double parseDouble(const std::string& value, const std::string& name) {
    try {
        size_t processed = 0;
        const double result = std::stod(value, &processed);

        if (processed != value.size()) {
            throw std::invalid_argument("extra characters");
        }

        return result;
    } catch (...) {
        throw std::invalid_argument("invalid double value for " + name + ": " + value);
    }
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 6) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    try {
        const std::string inputPath = argv[1];
        const std::string outputPath = argv[2];

        const int diameter = parseInt(argv[3], "diameter");
        const double sigmaColor = parseDouble(argv[4], "sigma_color");
        const double sigmaSpace = parseDouble(argv[5], "sigma_space");

        cv::Mat inputImage = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);

        if (inputImage.empty()) {
            std::cerr << "Error: cannot read image: " << inputPath << '\n';
            return EXIT_FAILURE;
        }

        cv::Mat result;

        bf::bilateralFilterCustom(
            inputImage,
            result,
            diameter,
            sigmaColor,
            sigmaSpace
        );

        if (!cv::imwrite(outputPath, result)) {
            std::cerr << "Error: cannot write image: " << outputPath << '\n';
            return EXIT_FAILURE;
        }

        std::cout << "Bilateral filtering completed successfully.\n";
        std::cout << "Input: " << inputPath << '\n';
        std::cout << "Output: " << outputPath << '\n';
        std::cout << "Parameters: d=" << diameter
                  << ", sigmaColor=" << sigmaColor
                  << ", sigmaSpace=" << sigmaSpace << '\n';

        return EXIT_SUCCESS;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
}
