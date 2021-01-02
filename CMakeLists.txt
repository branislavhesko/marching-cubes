cmake_minimum_required(VERSION 3.15)
project(marching_cubes)

set(CMAKE_CXX_STANDARD 17)
add_executable(marching_cubes main.cpp src/data_loader.cpp include/data_loader.h src/data_holder.cpp
        include/data_holder.h src/visualizer.cpp include/visualizer.hpp src/marching_cubes.cpp
        include/marching_cubes.h include/triangle_table.h include/structures.h src/viewer_3D.cpp
        include/viewer_3D.h src/mouse_control.cpp include/mouse_control.h src/obj_writer.cpp include/obj_writer.h
        include/json.hpp)

find_package(OpenCV REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIRECTORY})
if (SFML_FOUND)
    message("Found SFML!")
    target_link_libraries(marching_cubes sfml-window sfml-graphics sfml-system)

endif()
target_link_libraries(marching_cubes ${OpenCV_LIBS})
# target_link_libraries(marching_cubes gdi32.lib)
target_link_libraries(marching_cubes ${OPENGL_LIBRARIES})
# target_link_libraries(marching_cubes ${SFML_DEPENDENCIES})
target_link_libraries(marching_cubes libstdc++fs.a)
target_link_libraries(marching_cubes -lpthread)