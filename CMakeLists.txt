cmake_minimum_required (VERSION 3.3)
project (Quidditch)
add_executable(quidditch main.cpp loadShader.cpp Table.cpp Projection.cpp View.cpp Scene.cpp Sphere.cpp Translate.cpp Scale.cpp Texture.cpp Log.cpp Arena.cpp GhostBall.cpp WanderBall.cpp Ball.cpp)

execute_process(
  COMMAND "GraphicsMagick++-config" "--cppflags" "--cxxflags"
  OUTPUT_VARIABLE GM_CXX_FLAGS)

execute_process(
  COMMAND "GraphicsMagick++-config" "--ldflags" "--libs"
  OUTPUT_VARIABLE GM_LINKER_FLAGS)

string(REPLACE "\n" " " GM_CXX_FLAGS "${GM_CXX_FLAGS}")
string(REPLACE "\n" " " GM_LINKER_FLAGS "${GM_LINKER_FLAGS}")



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -ggdb -O0 ${GM_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lsfml-window -lsfml-system -lGLEW ${GM_LINKER_FLAGS}")


