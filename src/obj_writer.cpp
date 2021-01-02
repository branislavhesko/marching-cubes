//
// Created by brani on 28.12.20.
//

#include "../include/obj_writer.h"
#include <fstream>
#include <vector>

bool ObjWriter::write(const std::string& path) {
    std::ofstream output_stream(path.c_str(), std::ofstream::out);
    std::vector<Vector3D<float>> vertices;
    vertices.reserve(triangles_.size() * 3);
    for (const auto &triangle: triangles_) {
        for (const auto &vertex: triangle.vertices) {
            output_stream << "v" << " " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
        }
    }
    for (int i=0; i < triangles_.size(); i++) {
        output_stream << "f" << " " << i * 3 + 1 << " " << i * 3 + 2 << " " << i * 3 + 3 << std::endl;
    }
    return true;
}
