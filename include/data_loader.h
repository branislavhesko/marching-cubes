//
// Created by brani on 11.02.20.
//

#ifndef MARCHING_CUBES_DATA_LOADER_H
#define MARCHING_CUBES_DATA_LOADER_H

#include <experimental/filesystem>
#include "opencv2/opencv.hpp"

namespace fs = std::experimental::filesystem;

class DataLoader{
public:
    explicit DataLoader(fs::path path, std::string method);

    struct DataSize{
        uint64_t x;
        uint64_t y;
        uint64_t z;
        DataSize(uint64_t x, uint64_t y, uint64_t z): x{x}, y{y}, z{z}{};
        [[nodiscard]] uint64_t total_size() const {
            return x * y * z;
        }
    };
    using pair=std::pair<std::vector<uint8_t>, DataLoader::DataSize>;
    pair load_data_3d_into_memory();
private:
    std::string processing_method;
    std::vector<std::string> load_image_paths();
    static DataSize get_images_size(const std::vector<std::string>&);
    static cv::Mat ct_data_processing(const std::string &image) ;
    static cv::Mat tick_data_processing(const std::string &image);

    DataSize data_size_;
    fs::path path_to_data;
    std::map<std::string, std::function<cv::Mat(const std::string&)>> imageProcessingFunctions{
            {"ct", DataLoader::ct_data_processing},
            {"tick", DataLoader::tick_data_processing}
    };

};


#endif //MARCHING_CUBES_DATA_LOADER_H
