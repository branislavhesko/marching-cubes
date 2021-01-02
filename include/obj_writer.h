//
// Created by brani on 28.12.20.
//

#ifndef MARCHING_CUBES_OBJ_WRITER_H
#define MARCHING_CUBES_OBJ_WRITER_H

#include "structures.h"
#include <vector>


class ObjWriter {
public:
    std::vector<Triangle<float>> &triangles_;
    explicit ObjWriter(std::vector<Triangle<float>> &triangles): triangles_(triangles) {
    }
    bool write(const std::string& path);
};


#endif //MARCHING_CUBES_OBJ_WRITER_H
