//
// Created by brani on 28.12.20.
//

#ifndef MARCHING_CUBES_MOUSE_CONTROL_H
#define MARCHING_CUBES_MOUSE_CONTROL_H


class MouseControl {
public:
    void onLeftButton(int x, int y);
    void onRightButton(int x, int y);
    enum class State{None, Right, Left};

private:
    int x_= 0, x_old_= 0, x_new_= 0;
    int y_= 0, y_old_= 0, y_new_= 0;
    int z_= 0, z_old_= 0, z_new_= 0;
    State state_ = State::None;
public:
    [[nodiscard]] int getXNew() const;
    [[nodiscard]] int getYNew() const;
    [[nodiscard]] int getZNew() const;
    [[nodiscard]] State getState() const;
    void setXx(int x_coord);
    void setXold(int x_old);
    void setYy(int y_coord);
    void setYold(int y_old);
    void setZz(int z);
    void setZold(int z_old);
    void setState(State state);

};


#endif //MARCHING_CUBES_MOUSE_CONTROL_H
