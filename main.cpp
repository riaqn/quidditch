#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Magick++.h>

#include "FileTexture.hpp"
#include "NoiseTexture.hpp"
#include "PerlinNoise.hpp"

#include "Table.hpp"
#include "Sphere.hpp"
#include "Flag.hpp"
#include "Wave.hpp"

#include "GhostBall.hpp"

#include "SimpleLight.hpp"
#include "FollowSpotLight.hpp"

#include "Scene.hpp"

#include "Translate.hpp"
#include "Scale.hpp"

#include "BallWrapper.hpp"

#include "Log.hpp"

#include "Importer.hpp"

#include <btBulletDynamicsCommon.h>

#include <boost/filesystem.hpp>

#include <fstream>
#include <glm/gtc/constants.hpp>

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

  View view(glm::vec3(0, 2, 0), glm::vec2(-glm::pi<float>(), -1.0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  Scene scene(view, projection);
  
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

  SimpleLight light0;
  light0.position = glm::fvec4(0, 1, 0, 1);
  light0.intensities = glm::fvec3(1, 1, 1);
  light0.attenuation = 1;
  light0.ambientCoefficient = 0.05f;
  light0.coneAngle = 45.0f;
  light0.coneDirection = glm::vec3(0, -1, -1);
  scene.attach(&light0);

  /*
  FollowSpotLight light1(ballCue, glm::vec3(0, 1, -1), glm::vec3(2, 2, 2), 0.1, 15);
  scene.attach(&light1);*/
  
  SimpleLight light2;
  light2.position = glm::fvec4(0, 1, -2, 1);
  light2.intensities = glm::fvec3(1, 1, 1);
  light2.attenuation = 1;
  light2.ambientCoefficient = 0.05f;
  light2.coneAngle = 45.0f;
  light2.coneDirection = glm::vec3(0, -1, 1);
  scene.attach(&light2);
  

  btDbvtBroadphase broadphase;
  btDefaultCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher(&collisionConfiguration);
  btSequentialImpulseConstraintSolver solver;
  btDiscreteDynamicsWorld dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration);


  Importer importer(&dynamicsWorld, [](const std::string &path) -> void * {
      using namespace std;
      ifstream is(path);
      string type;
      is >> type;
      if (type == "GhostBall")
        return new GhostBall();
    });
  
  importer.loadWorld(boost::filesystem::path("worlds/simple.world"), [&scene](const btRigidBody *const rb) -> void {
      static Sphere sphere;
      static FileTexture texRed("res/red.png");
      static FileTexture texWhite("res/white.png");
      static FileTexture texBlue("res/blue.png");
      static FileTexture texGolden("res/golden.png");
      const btSphereShape *shape = (const btSphereShape *)rb->getCollisionShape();
      const Ball *b = (const Ball *)rb->getUserPointer();
      
      if (auto b0 = dynamic_cast<const GhostBall *>(b)) {
        scene.attach(new BallWrapper(shape->getRadius(),rb->getMotionState(), sphere, texRed));
      }
    });
  
  /*
  PerlinNoise noise;
  NoiseTexture texRed(noise, 800, 800, glm::fvec4(128, 0, 0, 255), glm::fvec4(255, 0, 0, 255));
  NoiseTexture texWhite(noise, 800, 800, glm::fvec4(128, 128, 128, 255), glm::fvec4(255,255,255,255));
  NoiseTexture texBlue(noise, 800, 800, glm::fvec4(0, 0, 128, 255), glm::fvec4(0, 0, 255,255));
  NoiseTexture texGolden(noise, 800, 800, glm::fvec4(128, 128, 0, 255), glm::fvec4(255,255,0,255));
  */
  

  sf::Font font;
  if (!font.loadFromFile("/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc")) {
    return -1;
  }
  
  /*
  FileTexture uk("res/flag1.png");
  FileTexture usa("res/flag2.png");

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
      /*
      glm::vec3 v0 = ballCue.x - view.eye_;
      v0.y = 0;
      ballCue.v = glm::normalize(v0) * 5.0f;
      */
    }

    dynamicsWorld.stepSimulation(elapsed.asSeconds());
    scene.render();


    window.pushGLStates();

    sf::Text text;
    text.setFont(font);
    //text.setString(std::to_string(arena.score));
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);
    text.setPosition(100,100);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);

    window.popGLStates();

    window.display();
  }
}
