#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "include/data_loader.h"
#include "include/data_holder.h"
#include "include/json.hpp"
#include "include/marching_cubes.h"
#include "include/visualizer.hpp"
#include "include/marching_cubes.h"
#include "include/structures.h"
#include "include/viewer_3D.h"
#include "include/obj_writer.h"


auto loadConfiguration(const std::string &filename) {
    std::ifstream file(filename);

    return nlohmann::json::parse(file);
};


int main() {
    auto settings = loadConfiguration("../settings.json");
    auto data = DataLoader(fs::path(
            settings["data_folder"]), settings["image_loading_method"]).load_data_3d_into_memory();
    DataHolder holder(std::move(data.first), data.second);
    MarchingCubes marcher(holder, settings["grid_size"]);
    auto &triangles = marcher.computeMultiThreaded(settings["normalize"]);
    std::cout << "Finished MARCHING CUBES!" << std::endl;

    if (settings["save_into_obj_file"]) {
        ObjWriter (triangles).write(settings["output_file"]);
    }
    if (settings["visualize_3D"]) {
        Viewer3D (triangles).show();
    }
    if (settings["visualize_slices"]) {
        Visualizer visualizer(holder);
        for (int i = 0; i < holder.get_data_size().z; i++) {
            std::cout << "X slice: " << i << std::endl;
            visualizer.showSliceZ(i, 10);
        }
    }

    std::cout << "Finished!" << std::endl;
    std::cout << data.first.size() << std::endl;
}
