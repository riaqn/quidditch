#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <Magick++.h>

#include "Texture.hpp"
#include "Table.hpp"
#include "Sphere.hpp"
#include "Scale.hpp"
#include "Scene.hpp"

#include "Translate.hpp"

#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "Wall.hpp"

int main(int argc, char *argv[]) {
  Magick::InitializeMagick(argv[0]);
  
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  settings.attributeFlags = sf::ContextSettings::Attribute::Core
    || sf::ContextSettings::Attribute::Debug; 
  
  sf::Window window(sf::VideoMode(800, 600), "Quidditch", sf::Style::Close, settings);
  window.setVerticalSyncEnabled(true);

  glewExperimental = GL_TRUE;
  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
    return EXIT_FAILURE;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  Arena arena;
  GhostBall ball(0.05f, 0.1f, glm::vec3(0, 0, 0), glm::vec3(0, 0, -0.5));
  arena.attach(&ball);

  WanderBall ball0(0.05, 0.1, glm::vec3(1, 0, -1), glm::vec3(-0.1, 0, 0),
                   1, 0.5);
  arena.attach(&ball0);

  Wall wall0{glm::vec3(0, 0, 1), 2};
  arena.attach(&wall0);

  Wall wall1{glm::vec3(0, 0, -1), 0};
  arena.attach(&wall1);

  Wall wall2{glm::vec3(1, 0, 0), 1};
  arena.attach(&wall2);

  Wall wall3{glm::vec3(-1, 0, 0), 1};
  arena.attach(&wall3);


  View view(glm::vec3(0, 2, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  Scene scene(view, projection);

  Table table;
  scene.attach(&table);

  Texture texRed(GL_TEXTURE_2D, "res/red.jpg");
  Sphere sphere(texRed);
  Scale scale(sphere, glm::vec3(0.1, 0.1, 0.1));
  Translate translate(scale, ball.x);
  scene.attach(&translate);

  Sphere sphere0(texRed);
  Scale scale0(sphere, glm::vec3(0.1, 0.1, 0.1));
  Translate translate0(scale, ball0.x);
  scene.attach(&translate0);
  
  bool running = true;
  while (running) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        running = false;
      } else if (event.type == sf::Event::Resized) {
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }
    arena.deduce(1.0/60);
    scene.render();

    window.display();
  }
}
