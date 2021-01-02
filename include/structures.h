//
// Created by brani on 26.12.20.
//

#ifndef MARCHING_CUBES_STRUCTURES_H
#define MARCHING_CUBES_STRUCTURES_H

#include <cmath>
#include <array>
#include <vector>
#include "triangle_table.h"

template <class T>
struct Vector3D {
    T x;
    T y;
    T z;
    Vector3D(): x(0), y(0), z(0) {};
    Vector3D(T x, T y, T z): x(x), y(y), z(z) {};
    Vector3D(const Vector3D &vec) noexcept : x(vec.x), y(vec.y), z(vec.z) {};
};

template <class T>
struct Vector4D: public Vector3D<T> {
    T value;
    Vector4D(T x, T y, T z, T value=0): Vector3D<T>(x, y, z), value(value) {};
    explicit Vector4D(Vector3D<T> vec, T value=0): Vector3D<T>(vec), value(value) {};
};

template <class T>
struct Triangle {
    std::array<Vector3D<T>, 3> vertices;
    Triangle(Vector3D<T> v1, Vector3D<T> v2, Vector3D<T> v3):
        vertices(std::array<Vector3D<T>, 3>{v1, v2, v3}) {};
    explicit Triangle(std::array<Vector3D<T>, 3> vertices):
        vertices(vertices) {};
    explicit Triangle(Triangle<float> &&triangle)  noexcept {
        vertices = std::move(triangle.vertices);
    }

    [[nodiscard]] std::array<float, 3> get_normal() const{
        std::array<float, 3> v1 = {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].y - vertices[0].y};
        std::array<float, 3> v2 = {vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y, vertices[2].y - vertices[0].y};
        std::array<float, 3> normal = {v1[1] * v2[2] - v2[1] * v1[2], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]};
        float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        normal[0] /= length; normal[1] /= length; normal[2] /= length;
        return normal;
    }
};


struct Cube {
    static const unsigned kmaxFaces = 13;
    uint8_t index;
    std::array<Vector4D<unsigned>, 8> edges;
    Cube(std::array<Vector4D<unsigned>, 8> edge_values, uint8_t isolevel): edges(edge_values) {
        index = 0;
        if (edge_values[0].value < isolevel) index |= 1;
        if (edge_values[1].value < isolevel) index |= 2;
        if (edge_values[2].value < isolevel) index |= 4;
        if (edge_values[3].value < isolevel) index |= 8;
        if (edge_values[4].value < isolevel) index |= 16;
        if (edge_values[5].value < isolevel) index |= 32;
        if (edge_values[6].value < isolevel) index |= 64;
        if (edge_values[7].value < isolevel) index |= 128;
        // index = 128; //TODO: remove
    }

    std::vector<Triangle<float>> get_triangle() {
        std::vector<Vector3D<float>> vertices;
        std::vector<Triangle<float>> triangles;
        for (int i=0; i < kmaxFaces; i++) {
            if (aCases[index][i] == -1) break;
            vertices.push_back(std::move(get_face_coords(aCases[index][i])));
        }
        for (int i=0; i < vertices.size(); i+=3) {
            triangles.push_back(std::move(Triangle<float>(vertices[i], vertices[i+1], vertices[i+2])));
        }
        return triangles;
    }

    Vector3D<float> get_face_coords(unsigned face_id) {
        if (face_id == 0) return Vector3D<float>(get_center(edges[1].x, edges[0].x),
                                                 get_center(edges[1].y, edges[0].y),
                                                 get_center(edges[1].z, edges[0].z));
        if (face_id == 1) return Vector3D<float>(get_center(edges[2].x, edges[1].x), get_center(edges[2].y, edges[1].y), get_center(edges[2].z, edges[1].z));
        if (face_id == 2) return Vector3D<float>(get_center(edges[3].x, edges[2].x), get_center(edges[3].y, edges[2].y), get_center(edges[3].z, edges[2].z));
        if (face_id == 3) return Vector3D<float>(get_center(edges[3].x, edges[0].x), get_center(edges[3].y, edges[0].y), get_center(edges[3].z, edges[0].z));
        if (face_id == 4) return Vector3D<float>(get_center(edges[5].x, edges[4].x), get_center(edges[5].y, edges[4].y), get_center(edges[5].z, edges[4].z));
        if (face_id == 5) return Vector3D<float>(get_center(edges[6].x, edges[5].x), get_center(edges[6].y, edges[5].y), get_center(edges[6].z, edges[5].z));
        if (face_id == 6) return Vector3D<float>(get_center(edges[7].x, edges[6].x), get_center(edges[7].y, edges[6].y), get_center(edges[7].z, edges[6].z));
        if (face_id == 7) return Vector3D<float>(get_center(edges[7].x, edges[4].x), get_center(edges[7].y, edges[4].y), get_center(edges[7].z, edges[4].z));
        if (face_id == 8) return Vector3D<float>(get_center(edges[4].x, edges[0].x), get_center(edges[4].y, edges[0].y), get_center(edges[4].z, edges[0].z));
        if (face_id == 9) return Vector3D<float>(get_center(edges[5].x, edges[1].x), get_center(edges[5].y, edges[1].y), get_center(edges[5].z, edges[1].z));
        if (face_id == 10) return Vector3D<float>(get_center(edges[6].x, edges[2].x), get_center(edges[6].y, edges[2].y), get_center(edges[6].z, edges[2].z));
        if (face_id == 11) return Vector3D<float>(get_center(edges[7].x, edges[3].x), get_center(edges[7].y, edges[3].y), get_center(edges[7].z, edges[3].z));
    }

    static float get_center(float coord_a, float coord_b) {
        return static_cast<float>(std::min(coord_a, coord_b)) + std::abs(coord_b - coord_a) / 2.0f;
    }
};
#endif //MARCHING_CUBES_STRUCTURES_H
