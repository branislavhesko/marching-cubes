//
// Created by brani on 20.02.20.
//

#include "../include/visualizer.hpp"

void Visualizer::showSliceZ(int z, int duration) {
    const DataLoader::DataSize & data_size = data_holder.get_data_size();
    cv::Mat slice(data_holder.get_data_size().y, data_holder.get_data_size().x, CV_8U);
    for (uint64_t x=0; x < data_size.x; x++) {
        for (uint64_t y=0; y < data_size.y; y++) {
            slice.at<uchar>(y, x) = this->data_holder.at(x, y, z);
        }
    }
    cv::imshow("okno", slice);
    cv::waitKey(duration);
}

void Visualizer::showSliceX(int x, int duration) {
    const DataLoader::DataSize & data_size = data_holder.get_data_size();
    cv::Mat slice(data_size.y, data_size.z, CV_8U);
    for (uint64_t y=0; y<data_size.y; y++) {
        for (uint64_t z=0; z<data_size.z; z++) {
            slice.at<uchar>(y, z) = this->data_holder.at(x, y, z);
        }
    }
    cv::imshow("okno", slice);
    cv::waitKey(duration);
}

void Visualizer::showSliceY(int y, int duration) {
    const DataLoader::DataSize & data_size = data_holder.get_data_size();
    cv::Mat slice(data_size.y, data_size.z, CV_8U);
    for (uint64_t x=0; x<data_size.x; x++) {
        for (uint64_t z=0; z<data_size.z; z++) {
            slice.at<uchar>(x, z) = this->data_holder.at(x, y, z);
        }
    }
    cv::imshow("okno", slice);
    cv::waitKey(duration);
}