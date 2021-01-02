//
// Created by brani on 27.12.20.
//

#ifndef MARCHING_CUBES_VIEWER_3D_H
#define MARCHING_CUBES_VIEWER_3D_H

#include <array>
#include <vector>
#include "structures.h"
#include "mouse_control.h"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"


struct Extremes {
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    float min_z;
    float max_z;
    Extremes(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z):
        min_x(min_x),
        max_x(max_x),
        min_y(min_y),
        max_y(max_y),
        min_z(min_z),
        max_z(max_z) {};
};


struct LightColors {
    std::array<GLfloat, 4> materialAmbient;
    std::array<GLfloat, 4> materialDiffuse;
    std::array<GLfloat, 4> materialShine;
    std::array<GLfloat, 1> materialShineFactor;
    std::array<GLfloat, 4> lightPosition;
};

struct LightColorsRed: LightColors {
    LightColorsRed(): LightColors() {
            materialAmbient = { 0.5f, 0.0f, 0.0f, 0.0f };
            materialDiffuse = { 0.8f, 0.0f, 0.0f, 0.0f };
            materialShine = { 0.8f, 0.0f, 0.0f, 0.0f };
            materialShineFactor = { 30.0f };
            lightPosition = { 0, 0, -200, 1.0f };
    }
};


struct LightColorsGreen: LightColors {
    LightColorsGreen(): LightColors() {
        materialAmbient = { 0.0f, 0.5f, 0.0f, 0.0f };
        materialDiffuse = { 0.0f, 0.8f, 0.0f, 0.0f };
        materialShine = { 0.0f, 0.8f, 0.0f, 0.0f };
        materialShineFactor = { 30.0f };
        lightPosition = { 200, 0, 0, 1.0f };
    }
};


struct LightColorsBlue: LightColors {
    LightColorsBlue(): LightColors() {
        materialAmbient = { 0.5f, 0.0f, 0.5f, 0.0f };
        materialDiffuse = { 0.8f, 0.0f, 0.8f, 0.0f };
        materialShine = { 0.8f, 0.0f, 0.8f, 0.0f };
        materialShineFactor = { 30.0f };
        lightPosition = { 0, 200, 0, 1.0f };
    }
};


class Viewer3D {
public:
    const std::vector<Triangle<float>> &triangles_;
    Extremes extremes_;
    explicit Viewer3D(const std::vector<Triangle<float>> &triangles):
            triangles_(triangles),
            extremes_(getTrianglesExtremas()),
            window_(sf::Window (sf::VideoMode(kWidth, kHeight),
                                "visualization", sf::Style::Default, getSettings())) {
        glEnable(GL_TEXTURE_2D);
        initialize();
    };
    void show();

private:
    sf::Window window_;
    MouseControl mouse_;
    static sf::ContextSettings getSettings();
    Extremes getTrianglesExtremas();
    void transformObject(int xnew, int ynew, int znew) const;

    [[maybe_unused]] static void drawCircle(double perimeter, int numberofpoints);
    void initialize();
    void drawTriangles();
    static const int kWidth = 1600;
    static const int kHeight = 900;
    static const bool kUseNormals = true; //TODO: add into class constructor as a parameter.

    const std::unique_ptr<LightColors> light_color_red_ = std::make_unique<LightColorsRed>();
    const std::unique_ptr<LightColors> light_color_blue_ = std::make_unique<LightColorsBlue>();
    const std::unique_ptr<LightColors> light_color_green_ = std::make_unique<LightColorsGreen>();

    static void setLight(int light, const std::unique_ptr<LightColors> &colors);
};


#endif //MARCHING_CUBES_VIEWER_3D_H
