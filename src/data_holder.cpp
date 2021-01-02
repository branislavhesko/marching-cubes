//
// Created by brani on 12.02.20.
//

#include "../include/data_holder.h"


DataLoader::DataSize DataHolder::get_data_size() const{
    return data_size_;
}

uint8_t DataHolder::at(uint64_t x, uint64_t y, uint64_t z) const{
    uint64_t index = z * data_size_.x * data_size_.y + y * data_size_.x + x;
    return data_[index];
}
