//
// Created by brani on 27.12.20.
//

#include "../include/viewer_3D.h"


void Viewer3D::show() {
    window_.setActive();
    while(window_.isOpen()) {
        sf::Event event{};
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                window_.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window_ is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    mouse_.setState(MouseControl::State::Left);
                    mouse_.setXx(sf::Mouse::getPosition(window_).x);
                    mouse_.setYy(sf::Mouse::getPosition(window_).y);
                }
                mouse_.onLeftButton(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y);
            }
            if (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    mouse_.setState(MouseControl::State::Right);
                    mouse_.setZz(sf::Mouse::getPosition(window_).y);
                }
                mouse_.onRightButton(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y);            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (mouse_.getState() == MouseControl::State::Left) {
                    mouse_.setXold(mouse_.getXNew());
                    mouse_.setYold(mouse_.getYNew());
                } else if (mouse_.getState() == MouseControl::State::Right) {
                    mouse_.setZold(mouse_.getZNew());
                }
                mouse_.setState(MouseControl::State::None);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        transformObject(mouse_.getXNew(), mouse_.getYNew(), mouse_.getZNew());
        drawTriangles();
        window_.display();
    }
}

sf::ContextSettings Viewer3D::getSettings() {
    sf::ContextSettings settings{};
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    return settings;
}

[[maybe_unused]] void Viewer3D::drawCircle(double perimeter, int numberofpoints) {
    double xx, y;
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < numberofpoints; i++) {
        xx = perimeter * cos(i * 2.0 * 3.14159 / (float) numberofpoints);
        y = perimeter * sin(i * 2.0 * 3.14159 / (float) numberofpoints);
        glVertex2f((float) xx,(float) y);
    }
    glEnd();

    glFlush();
}

void Viewer3D::drawTriangles() {
    glBegin(GL_TRIANGLES);
    for (const auto &triangle: triangles_) {
        if (kUseNormals) {
            auto normal = triangle.get_normal();
            glNormal3f(normal[0], normal[1], normal[2]);
        }
        for (const auto &point: triangle.vertices) {
            glVertex3f(point.x, point.y, point.z);
        }
    }
    glEnd();
    glFlush();
}

Extremes Viewer3D::getTrianglesExtremas() {
    Extremes extremas_(1e6, -1e6, 1e6, -1e6, 1e6, -1e6);
    if (triangles_.empty()) return extremas_;
    for (const auto &triangle: triangles_) {
        for (const auto &vertx: triangle.vertices) {
            extremas_.min_x = std::min(extremas_.min_x, vertx.x);
            extremas_.min_y = std::min(extremas_.min_y, vertx.y);
            extremas_.min_z = std::min(extremas_.min_z, vertx.z);
            extremas_.max_x = std::max(extremas_.max_x, vertx.x);
            extremas_.max_y = std::max(extremas_.max_y, vertx.y);
            extremas_.max_z = std::max(extremas_.max_z, vertx.z);
        }
    }
    return extremas_;
}

void Viewer3D::initialize() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
            2 * extremes_.min_x,
            2 * extremes_.max_x,
            2 * extremes_.min_y,
            2 * extremes_.max_y,
            2 * extremes_.min_z,
            2 * extremes_.max_z);
    //glScalef(1,-1,1);
    // glTranslatef(0,2.5,0);
    if (kUseNormals) {
        glClearColor(0, 0, 0, 0);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        setLight(GL_LIGHT0, light_color_red_);
        setLight(GL_LIGHT1, light_color_blue_);
        setLight(GL_LIGHT2, light_color_green_);
        glEnable(GL_LIGHTING);
    }
}

void Viewer3D::setLight(int light, const std::unique_ptr<LightColors> &colors) {
    glLightfv(light, GL_AMBIENT, colors->materialAmbient.data());
    glLightfv(light, GL_DIFFUSE, colors->materialDiffuse.data());
    glLightfv(light, GL_SPECULAR, colors->materialShine.data());
    glLightfv(light, GL_SHININESS, colors->materialShineFactor.data());
    glLightfv(light, GL_POSITION, colors->lightPosition.data());
    glEnable(light);

}

void Viewer3D::transformObject(int xnew, int ynew, int znew) const {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, extremes_.min_z);
    glTranslatef(0.0, 0.0, znew);
    glRotatef(ynew, 1.0, 0.0, 0.0);
    glRotatef(xnew, 0.0, 1.0, 0.0);
}
