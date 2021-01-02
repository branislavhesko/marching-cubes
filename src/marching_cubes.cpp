//
// Created by brani on 10.04.20.
//

#include "../include/marching_cubes.h"
#include "../include/structures.h"
#include <vector>
#include <thread>

std::vector<Triangle<float>> MarchingCubes::compute() {
    return computeInternal(1, data_holder_.get_data_size().x - grid_size_);
}

std::vector<Triangle<float>> MarchingCubes::computeInternal(unsigned x_start, unsigned x_end) const {
    std::vector<Triangle<float>> output_triangles;
    unsigned counter = 0;
    float state = 0;
    output_triangles.reserve(100000);
    for (unsigned x = x_start; x < x_end; x += grid_size_) {
        for (unsigned y = 1; y < data_holder_.get_data_size().y - grid_size_; y += grid_size_) {
            for (unsigned z = 1; z < data_holder_.get_data_size().z - grid_size_; z += grid_size_) {
                counter += grid_size_ * grid_size_ * grid_size_;
                auto edges = extractEdges(x, y, z);
                Cube cube(edges, kisoline);
                auto single_cube_triangles = cube.get_triangle();
                std::move(single_cube_triangles.begin(), single_cube_triangles.end(), std::back_inserter(output_triangles));
                if (state < (float) counter * 100.0f / (float) data_holder_.get_data_size().total_size()) {
                    state += 1;
                    std::cout << "Progress: " << state << "%." << " Number of single_cube_triangles: "<<
                        output_triangles.size() << "." << std::endl;
                }
            }
        }
    }
    return output_triangles;
}

std::array<Vector4D<unsigned>, 8> MarchingCubes::extractEdges(unsigned int x, unsigned int y, unsigned int z) const {
    return std::array<Vector4D<unsigned>, 8> {
            data_holder_.at(Vector3D<unsigned>{x, y, z}),
            data_holder_.at(Vector3D<unsigned>{x + grid_size_, y, z}),
            data_holder_.at(Vector3D<unsigned>{x + grid_size_, y + grid_size_, z}),
            data_holder_.at(Vector3D<unsigned>{x, y + grid_size_, z}),
            data_holder_.at(Vector3D<unsigned>{x, y, z + grid_size_}),
            data_holder_.at(Vector3D<unsigned>{x + grid_size_, y, z + grid_size_}),
            data_holder_.at(Vector3D<unsigned>{x + grid_size_, y + grid_size_, z + grid_size_}),
            data_holder_.at(Vector3D<unsigned>{x, y + grid_size_, z + grid_size_})
    };
}

std::vector<Triangle<float>>& MarchingCubes::computeMultiThreaded(bool shift_to_center) {
    unsigned num_threads = 6;
    std::vector<std::thread> threads;
    unsigned step = data_holder_.get_data_size().x / num_threads;
    std::vector<std::pair<unsigned, unsigned>> range;
    for (unsigned i=0; i<num_threads; i++) {
        range.emplace_back(i * step, (i + 1) * step);
    }
    range[num_threads - 1].second -= grid_size_; // Range check

    for (unsigned  i=0; i<num_threads; i++) {
        threads.emplace_back(std::thread(&MarchingCubes::computeMultiThreadedInternal, this, range[i]));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    if (shift_to_center) {
        shiftTrianglesToCenter();
    }

    return triangles_;
}

void MarchingCubes::shiftTrianglesToCenter() {
    float cx = 0, cy = 0, cz = 0;
    for (const auto &triangle: triangles_) {
        // as triangles_ are small, only first vertex is sufficient
        cx += triangle.vertices[0].x;
        cy += triangle.vertices[0].y;
        cz += triangle.vertices[0].z;
    }
    cx = cx / static_cast<float>(triangles_.size());
    cy = cy / static_cast<float>(triangles_.size());
    cz = cz / static_cast<float>(triangles_.size());

    for (auto &triangle: triangles_) {
        for (auto &vertex: triangle.vertices) {
            vertex.x -= cx;
            vertex.y -= cy;
            vertex.z -= cz;
        }
    }
}

void MarchingCubes::computeMultiThreadedInternal(std::pair<unsigned, unsigned> x_range) {
    auto partial_triangles = computeInternal(x_range.first, x_range.second);
    std::lock_guard<std::mutex> lock(g_triangles_mutex_);
    std::move(partial_triangles.begin(), partial_triangles.end(), std::back_inserter(triangles_));
}
