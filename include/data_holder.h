//
// Created by brani on 12.02.20.
//

#ifndef MARCHING_CUBES_DATA_HOLDER_H
#define MARCHING_CUBES_DATA_HOLDER_H

#include <string>
#include <vector>
#include <memory>
#include "data_loader.h"
#include "structures.h"

/*
 * Class holding 3D data_array
 */
class DataHolder {
public:
    DataHolder(std::vector<uint8_t>&& data,  DataLoader::DataSize data_size): data_(std::move(data)), data_size_(data_size) {
        std::cout << "Data with size " << data_size_.total_size() << std::endl;
    }
    [[nodiscard]] DataLoader::DataSize get_data_size() const;
    [[nodiscard]] uint8_t at(uint64_t, uint64_t, uint64_t) const;
    template <typename T> Vector4D<T> at(Vector3D<T> &&point) const{
        return Vector4D<T> (point, at(static_cast<uint64_t >(point.x), static_cast<uint64_t>(point.y), static_cast<uint64_t>(point.z)));
    }

private:
    std::vector<uint8_t> data_;
    DataLoader::DataSize data_size_;

};


#endif //MARCHING_CUBES_DATA_HOLDER_H
