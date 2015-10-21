#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <Magick++.h>

#include "Texture.hpp"
#include "Table.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"

#include "BallWrapper.hpp"

#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "Wall.hpp"
#include "Log.hpp"

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
  window.setMouseCursorVisible(false);

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
  
  GhostBall ballGhost0(0.05f, 0.1f, glm::vec3(-0.5, 0.2, -2.0), glm::vec3(0, 0, 0));
  arena.attach(&ballGhost0);
  /*
  GhostBall ballGhost1(0.05f, 0.1f, glm::vec3(0, 0.05, -2.0), glm::vec3(0, 0, 1));
  arena.attach(&ballGhost1);
  GhostBall ballGhost2(0.05f, 0.1f, glm::vec3(0.5, 0.05, -2.0), glm::vec3(0, 0, 0));
  arena.attach(&ballGhost2);
  GhostBall ballGhost3(0.05f, 0.1f, glm::vec3(-0.5, 0.05, -1.5), glm::vec3(0, 0, 0));
  arena.attach(&ballGhost3);
  GhostBall ballGhost4(0.05f, 0.1f, glm::vec3(0, 0.05, -1.5), glm::vec3(0, 0, 0));
  arena.attach(&ballGhost4);
  GhostBall ballGhost5(0.05f, 0.1f, glm::vec3(0.5, 0.05, -1.5), glm::vec3(0, 0, 0));
  arena.attach(&ballGhost5);
  

  WanderBall ballWander0(0.02, 0.1, glm::vec3(-0.5, 0.05, -1.0), glm::vec3(1, 0, 0),
                   1, 0.5);
  arena.attach(&ballWander0);

  WanderBall ballWander1(0.02, 0.1, glm::vec3(0, 0.05, -1.0), glm::vec3(0, 0, 0),
                        1, 0.5);
  arena.attach(&ballWander1);

    WanderBall ballWander2(0.02, 0.1, glm::vec3(0.5, 0.05, -1.0), glm::vec3(0, 0, 0),
                   1, 0.5);
  arena.attach(&ballWander2);

  WanderBall ballWander3(0.02, 0.1, glm::vec3(-0.5, 0.05, -0.5), glm::vec3(0, 0, 0),
                        1, 0.5);
  arena.attach(&ballWander3);
  
  WanderBall ballWander4(0.02, 0.1, glm::vec3(0, 0.05, -0.5), glm::vec3(0, 0, 0),
                   1, 0.5);
  arena.attach(&ballWander4);

  WanderBall ballWander5(0.02, 0.1, glm::vec3(0.5, 0.05, -0.5), glm::vec3(0, 0, 0),
                        1, 0.5);
  arena.attach(&ballWander5);

    GhostBall ballCue(0.05f, 0.1f, glm::vec3(0, 0.05, 0), glm::vec3(0, 0, 0));
  arena.attach(&ballCue);

  */

  Wall wall0{glm::vec3(0, 0, 1), 2, 0.8};
  arena.attach(&wall0);

  Wall wall1{glm::vec3(0, 0, -1), 0, 0.8};
  arena.attach(&wall1);

  Wall wall2{glm::vec3(1, 0, 0), 1, 0.8};
  arena.attach(&wall2);

  Wall wall3{glm::vec3(-1, 0, 0), 1, 0.8};
  arena.attach(&wall3);

  Wall wall4{glm::vec3(0, 1, 0), 0, 0.5};
  arena.attach(&wall4);

  View view(glm::vec3(0, 2, 0), glm::vec2(0, 0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  Scene scene(view, projection);

  Table table;
  scene.attach(&table);

  Sphere sphere;

  Texture texRed(GL_TEXTURE_2D, "res/red.jpg");
  Texture texWhite(GL_TEXTURE_2D, "res/white0.jpg");
  Texture texBlue(GL_TEXTURE_2D, "res/blue.jpg");

  BallWrapper sphereGhost0(ballGhost0, sphere, texRed);
  scene.attach(&sphereGhost0);
  /*
  BallWrapper sphereGhost1(ballGhost1, sphere, texRed);
  scene.attach(&sphereGhost1);
  BallWrapper sphereGhost2(ballGhost2, sphere, texRed);
  scene.attach(&sphereGhost2);
  BallWrapper sphereGhost3(ballGhost3, sphere, texRed);
  scene.attach(&sphereGhost3);
  BallWrapper sphereGhost4(ballGhost4, sphere, texRed);
  scene.attach(&sphereGhost4);
  BallWrapper sphereGhost5(ballGhost5, sphere, texRed);
  scene.attach(&sphereGhost5);

  BallWrapper sphereCue(ballCue, sphere, texWhite);
  scene.attach(&sphereCue);

  BallWrapper sphereWander0(ballWander0, sphere, texBlue);
  scene.attach(&sphereWander0);

  BallWrapper sphereWander1(ballWander1, sphere, texBlue);
  scene.attach(&sphereWander1);

  BallWrapper sphereWander2(ballWander2, sphere, texBlue);
  scene.attach(&sphereWander2);

  BallWrapper sphereWander3(ballWander3, sphere, texBlue);
  scene.attach(&sphereWander3);
  
  BallWrapper sphereWander4(ballWander4, sphere, texBlue);
  scene.attach(&sphereWander4);

  BallWrapper sphereWander5(ballWander5, sphere, texBlue);
  scene.attach(&sphereWander5);

  */
  bool running = true;
  sf::Clock clock;
  while (running) {
    sf::Time elapsed = clock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        running = false;
      } else if (event.type == sf::Event::Resized) {
        glViewport(0, 0, event.size.width, event.size.height);
      } else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2u size = window.getSize();
        if (size.x / 2 == event.mouseMove.x && size.y / 2 == event.mouseMove.y)
          continue;
        sf::Mouse::setPosition(sf::Vector2i(size.x / 2,
                                            size.y / 2), window);
        static float turnSpeed = 0.01;
        view.turn(glm::vec2(size.x / 2.0 - event.mouseMove.x,
                             size.y / 2.0 - event.mouseMove.y) * turnSpeed);
      }
    }
    static float moveSpeed = 1; //per second
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      view.up(elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      view.up(- elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      view.right(-elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      view.right(elapsed.asSeconds() * moveSpeed);

    arena.deduce(elapsed.asSeconds());
    scene.render();

    window.display();
  }
}
