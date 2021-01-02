//
// Created by brani on 11.02.20.
//

#include "../include/data_loader.h"

#include <utility>


DataLoader::DataLoader(fs::path path, std::string method):
    path_to_data(std::move(path)),
    processing_method(std::move(method)),
    data_size_(0, 0, 0) {
}

std::vector<std::string> DataLoader::load_image_paths() {
    std::vector<std::string> image_paths;
    image_paths.reserve(4000);
    for (auto&& image_path: fs::directory_iterator(path_to_data)) {
        image_paths.emplace_back(image_path.path().c_str());
        std::cout << image_path.path().c_str() << std::endl;
    }
    std::sort(image_paths.begin(), image_paths.end());
    return image_paths;
}

DataLoader::pair DataLoader::load_data_3d_into_memory() {
    auto image_paths = load_image_paths();
    data_size_ = get_images_size(image_paths);
    std::vector<uint8_t > data;
    data.reserve(data_size_.total_size());
    for (const auto &image: image_paths) {
        cv::Mat img = imageProcessingFunctions[processing_method](image);
        std::copy(img.data, img.data + img.cols * img.rows, std::back_inserter(data));
    }
    std::cout << data.size();
    return {data, data_size_};
}

cv::Mat DataLoader::ct_data_processing(const std::string &image) {
    cv::Mat img = cv::imread(image, cv::IMREAD_ANYCOLOR);
    cv::threshold(img, img, 2, 255, cv::THRESH_BINARY);
    return img;
}


cv::Mat DataLoader::tick_data_processing(const std::string &image) {
    std::cout << "Loading image: " << image << "."  << std::endl;
    cv::Mat img = cv::imread(image, cv::IMREAD_GRAYSCALE);
    cv::threshold(img, img, 128, 255, cv::THRESH_BINARY);
    cv::erode(img, img, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(51, 21)));
    cv::dilate(img, img, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(31, 21)));
    return img;
}

DataLoader::DataSize DataLoader::get_images_size(const std::vector<std::string> &images) {
    auto z = static_cast<uint64_t >(images.size());
    auto shape = cv::imread(images[0]).size();
    return DataSize(shape.width, shape.height, z);
}
