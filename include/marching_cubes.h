//
// Created by brani on 10.04.20.
//

#ifndef MARCHING_CUBES_MARCHING_CUBES_H
#define MARCHING_CUBES_MARCHING_CUBES_H

#include <array>
#include <mutex>
#include "data_holder.h"
#include "triangle_table.h"
#include "structures.h"


class MarchingCubes {
public:
    explicit MarchingCubes(const DataHolder &holder, unsigned int grid_size): data_holder_(holder), grid_size_(grid_size) {};
    std::vector<Triangle<float>>  compute();

    [[nodiscard]] std::array<Vector4D<unsigned int>, 8> extractEdges(
            unsigned int x, unsigned int y, unsigned int z) const;

    std::vector<Triangle<float>>& computeMultiThreaded(bool shift_to_center);

    [[nodiscard]] std::vector<Triangle<float>> computeInternal(unsigned x_start, unsigned x_end) const;
    void computeMultiThreadedInternal(std::pair<unsigned, unsigned> x_range);

private:
    const DataHolder &data_holder_;
    const uint8_t kisoline = 128;
    unsigned grid_size_ = 10;
    std::mutex g_triangles_mutex_;
    std::vector<Triangle<float>> triangles_;
    void shiftTrianglesToCenter();
};


#endif //MARCHING_CUBES_MARCHING_CUBES_H
