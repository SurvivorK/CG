cmake_minimum_required(VERSION 3.10)
project(Project)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
link_directories(lib/x64)

add_compile_options(-lglut -lglu)
add_executable(Project main.cpp src/Entity.cpp include/Entity.h src/Player.cpp include/Player.h src/Worlds.cpp include/Worlds.h src/Block.cpp include/Block.h include/stb_image.h include/header.h src/header.cpp src/Image.cpp include/Image.h)

target_link_libraries(Project libopengl32.a  libfreeglut.a glu32.dll)