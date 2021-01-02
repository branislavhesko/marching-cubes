//
// Created by brani on 20.02.20.
//

#ifndef MARCHING_CUBES_VISUALIZER_HPP
#define MARCHING_CUBES_VISUALIZER_HPP


#include "data_holder.h"

class Visualizer {
private:

    DataHolder &data_holder;
public:

    explicit Visualizer(DataHolder &holder): data_holder(holder) {

    }

    void showSliceZ(int z, int duration);
    void showSliceX(int x, int duration);
    void showSliceY(int y, int duration);
};


#endif //MARCHING_CUBES_VISUALIZER_HPP
