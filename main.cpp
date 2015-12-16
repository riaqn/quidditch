#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Magick++.h>

#include "Texture.hpp"
#include "Table.hpp"
#include "Sphere.hpp"
#include "Flag.hpp"
#include "Wave.hpp"

#include "Scene.hpp"

#include "Translate.hpp"
#include "Scale.hpp"

#include "BallWrapper.hpp"

#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "SnitchBall.hpp"
#include "CueBall.hpp"
#include "Wall.hpp"

#include "Log.hpp"

int main(int argc, char *argv[]) {
  Magick::InitializeMagick(argv[0]);
  
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 0;
  settings.attributeFlags =  sf::ContextSettings::Attribute::Debug; 
  
  sf::RenderWindow window(sf::VideoMode(800, 600), "Quidditch", sf::Style::Close, settings);
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


  /*
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  */


  sf::SoundBuffer buffer0;
  if (!buffer0.loadFromFile("res/ball-wall.wav")) {
    return -1;
  }
  sf::Sound sound0(buffer0);

  sf::SoundBuffer buffer1;
  if (!buffer1.loadFromFile("res/ball-ball.wav")) {
    return -1;
  }
  sf::Sound sound1(buffer1);


  Arena arena([&sound0](const Wall *w, const Ball *b) -> void {
      debug << "playing buffer0\n";
      sound0.setVolume(glm::length(b->v));
      sound0.play();
    }, [&sound1](const Ball *, const Ball *) -> void {
      debug << "playing buffer1\n";
      sound1.play();
    });
  
  GhostBall ballGhost0(Ball(0.05f, 0.05, glm::vec3(-0.5, 0.05, -1.5), glm::vec3(0, 0, 1)));
  arena.attach(&ballGhost0);
  GhostBall ballGhost1(Ball(0.05f, 0.05, glm::vec3(0, 0.05, -1.5), glm::vec3(0, 0, 1)));
  arena.attach(&ballGhost1);
  GhostBall ballGhost2(Ball(0.05f, 0.05, glm::vec3(0.5, 0.05, -1.5), glm::vec3(0, 0, 0)));
  arena.attach(&ballGhost2);
  GhostBall ballGhost3(Ball(0.05f, 0.05, glm::vec3(-0.5, 0.05, -1.5), glm::vec3(0, 0, 0)));
  arena.attach(&ballGhost3);
  GhostBall ballGhost4(Ball(0.05f, 0.05, glm::vec3(0, 0.05, -1.5), glm::vec3(0, 0, 0)));
  arena.attach(&ballGhost4);
  GhostBall ballGhost5(Ball(0.05f, 0.05, glm::vec3(0.5, 0.05, -1.5), glm::vec3(0, 0, 0)));
  arena.attach(&ballGhost5);
  

  WanderBall ballWander0(Ball(0.02, 0.05, glm::vec3(-0.5, 0.05, -1.0), glm::vec3(1, 0, 0)),
                   1, 1);
  arena.attach(&ballWander0);

  WanderBall ballWander1(Ball(0.02, 0.05, glm::vec3(0, 0.05, -1.0), glm::vec3(0, 0, 0)),
                        1, 1);
  arena.attach(&ballWander1);

  WanderBall ballWander2(Ball(0.02, 0.05, glm::vec3(0.5, 0.05, -1.0), glm::vec3(0, 0, 0)),
                   1, 1);
  arena.attach(&ballWander2);

  WanderBall ballWander3(Ball(0.02, 0.05, glm::vec3(-0.5, 0.05, -0.5), glm::vec3(0, 0, 0)),
                        1, 1);
  arena.attach(&ballWander3);
  
  WanderBall ballWander4(Ball(0.02, 0.05, glm::vec3(0, 0.05, -0.5), glm::vec3(0, 0, 0)),
                   1, 1);
  arena.attach(&ballWander4);

  WanderBall ballWander5(Ball(0.02, 0.05, glm::vec3(0.5, 0.05, -0.5), glm::vec3(0, 0, 0)),
                        1, 1);
  arena.attach(&ballWander5);

  CueBall ballCue(GhostBall(Ball(0.05f, 0.05, glm::vec3(0, 0.05, -0.2), glm::vec3(0, 0, 0))));
  arena.attach(&ballCue);

  SnitchBall ballSnitch(Ball(0.05f, 0.05, glm::vec3(0.2, 0.05, -0.2), glm::vec3(0, 0, 0)), 10, true, glm::vec3(-1, 0.3, -2), glm::vec3(1, 0.5, 0), 1, 2);
  arena.attach(&ballSnitch);

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

  Wall wall5{glm::vec3(0, -1, 0), 1, 0.8};
  arena.attach(&wall5);

  View view(glm::vec3(0, 2, 0), glm::vec2(-glm::pi<float>(), -1.0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  Scene scene(view, projection);

  Table table;
  scene.attach(&table);

  Sphere sphere;

  Texture texRed(GL_TEXTURE_2D, "res/red.jpg");
  Texture texWhite(GL_TEXTURE_2D, "res/white0.jpg");
  Texture texBlue(GL_TEXTURE_2D, "res/blue.jpg");
  Texture texGolden(GL_TEXTURE_2D, "res/golden.jpg");

  sf::Font font;
  if (!font.loadFromFile("/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc")) {
    return -1;
  }

  BallWrapper sphereGhost0(ballGhost0, sphere, texRed);
  scene.attach(&sphereGhost0);
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

  BallWrapper sphereSnitch(ballSnitch, sphere, texGolden);
  scene.attach(&sphereSnitch);

  Texture uk(GL_TEXTURE_2D, "res/flag1.png");
  Texture usa(GL_TEXTURE_2D, "res/flag2.png");
  Wave wave0(100, 100, Wave::WAVE_BEZIER);
  Wave wave1(100, 100, Wave::WAVE_TRIANGLE);
  Flag flag0(wave0, uk);
  Flag flag1(wave1, usa);

  Translate flag0_t(flag0, glm::vec3(0, 1, 0));
  Scale flag0_s(flag0_t, glm::vec3(1, 0.5, 1));
  scene.attach(&flag0_s);

  Translate flag1_t(flag1, glm::vec3(0, 1, -2));
  Scale flag1_s(flag1_t, glm::vec3(1, 0.5, 1));
  scene.attach(&flag1_s);

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
      } else if (event.type == sf::Event::MouseWheelScrolled) {
        view.eye_ += glm::normalize(view.direction_) * event.mouseWheelScroll.delta;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      glm::vec3 v0 = ballCue.x - view.eye_;
      v0.y = 0;
      ballCue.v = glm::normalize(v0) * 5.0f;
    }

    arena.deduce(elapsed.asSeconds() );
    scene.render();

    window.pushGLStates();

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(arena.score));
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);
    text.setPosition(100,100);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);

    window.popGLStates();
    window.display();
  }
}
