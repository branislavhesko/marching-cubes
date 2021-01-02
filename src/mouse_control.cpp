//
// Created by brani on 28.12.20.
//

#include "../include/mouse_control.h"
//
// Created by brani on 24.10.2016.
//


void MouseControl::onLeftButton(int x, int y) {
    y_new_ = y_old_ + y - y_;
    x_new_ = x_old_ + x - x_;
}

void MouseControl::onRightButton(int x, int y) {
    z_new_ = z_old_ + y - z_;
}



void MouseControl::setXx(int x_coord) {
    MouseControl::x_ = x_coord;
}


void MouseControl::setXold(int x_old) {
    MouseControl::x_old_ = x_old;
}


void MouseControl::setYy(int y_coord) {
    MouseControl::y_ = y_coord;
}


void MouseControl::setYold(int y_old) {
    MouseControl::y_old_ = y_old;
}


void MouseControl::setZz(int z) {
    z_ = z;
}


void MouseControl::setZold(int z_old) {
    MouseControl::z_old_ = z_old;
}


void MouseControl::setState(MouseControl::State state) {
    MouseControl::state_ = state;
}

int MouseControl::getXNew() const {
    return x_new_;
}

int MouseControl::getYNew() const {
    return y_new_;
}

int MouseControl::getZNew() const {
    return z_new_;
}

MouseControl::State MouseControl::getState() const {
    return state_;
}
