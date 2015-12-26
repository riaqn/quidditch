include(FindPkgConfig)
cmake_minimum_required (VERSION 3.3)
project (Quidditch)
add_executable(quidditch main.cpp Table.cpp Projection.cpp View.cpp Scene.cpp Sphere.cpp Texture.cpp Log.cpp  BallWrapper.cpp Box.cpp Wave.cpp Flag.cpp Translate.cpp Scale.cpp Bezier.cpp NoiseTexture.cpp Texture.cpp FileTexture.cpp PerlinNoise.cpp Shape.cpp Program.cpp SimpleLight.cpp FollowSpotLight.cpp GhostBall.cpp Importer.cpp utils.cpp Ball.cpp)


pkg_check_modules(BULLET REQUIRED bullet)

target_include_directories(quidditch PRIVATE ${BULLET_INCLUDE_DIRS})
target_link_libraries(quidditch ${BULLET_LIBRARIES})
target_link_libraries(quidditch -lboost_system -lboost_filesystem)


execute_process(
  COMMAND "GraphicsMagick++-config" "--cppflags" "--cxxflags"
  OUTPUT_VARIABLE GM_CXX_FLAGS)

execute_process(
  COMMAND "GraphicsMagick++-config" "--ldflags" "--libs"
  OUTPUT_VARIABLE GM_LINKER_FLAGS)

string(REPLACE "\n" " " GM_CXX_FLAGS "${GM_CXX_FLAGS}")
string(REPLACE "\n" " " GM_LINKER_FLAGS "${GM_LINKER_FLAGS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -ggdb -O0 ${GM_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -lGLEW ${GM_LINKER_FLAGS}")
