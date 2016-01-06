#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Magick++.h>

#include "main.hpp"

#include "FileTexture.hpp"
#include "NoiseTexture.hpp"
#include "PerlinNoise.hpp"

#include "Arena.hpp"

#include "Table.hpp"
#include "Flag.hpp"
#include "Wave.hpp"

#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "CueBall.hpp"
#include "SnitchBall.hpp"
#include "Ground.hpp"
#include "Wall.hpp"

#include "SimpleLight.hpp"
#include "FollowSpotLight.hpp"

#include "Scene.hpp"

#include "SphereShape.hpp"
#include "TriangleMeshShape.hpp"
#include "BoxShape.hpp"

#include "Log.hpp"

#include "Importer.hpp"
#include "MaterialImporter.hpp"
#include "BulletShapeRender.hpp"


#include <btBulletDynamicsCommon.h>

#include <boost/filesystem.hpp>

#include <map>
#include <fstream>
#include <sstream>

#include <glm/gtc/constants.hpp>


#include <exception>

Scene *scene;
Arena *arena;

//yes, I 'm green.
using namespace std;

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

  View view(glm::vec3(0, 2, 2), glm::vec2(-glm::pi<float>(), -1.0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  scene = new Scene(view, projection);
  
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
  light0.position = glm::fvec4(0, 1, 1, 1);
  light0.intensities = glm::fvec3(1, 1, 1);
  light0.attenuation = 1;
  light0.ambientCoefficient = 0.05f;
  light0.coneAngle = 45.0f;
  light0.coneDirection = glm::vec3(0, -1, -1);
  scene->add(&light0);

  
  SimpleLight light2;
  light2.position = glm::fvec4(0, 1, -1, 1);
  light2.intensities = glm::fvec3(1, 1, 1);
  light2.attenuation = 1;
  light2.ambientCoefficient = 0.05f;
  light2.coneAngle = 45.0f;
  light2.coneDirection = glm::vec3(0, -1, 1);
  scene->add(&light2);
  

  btDbvtBroadphase broadphase;
  btDefaultCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher(&collisionConfiguration);
  btSequentialImpulseConstraintSolver solver;
  btDiscreteDynamicsWorld dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration);

  arena = new Arena(dynamicsWorld);

  std::map<btRigidBody *, Renderable *> bodies;
  CueBall *cue;

  Importer importer(*arena);
  importer.loadArena(boost::filesystem::path("arenas/simple.arena"), [&cue](Controller *const con, istream &is) -> void {
      string materialPath;
      is >> materialPath;

      static MaterialImporter mi;
      Renderable::Material m = mi.import(materialPath);
      
      BulletShape *shape;
      auto sc = dynamic_cast<SingleController *const>(con);
      if (sc == NULL)
        return ;
      auto rb = sc->getBody();

      const btCollisionShape *const cs = rb.getCollisionShape();
      if (auto b = dynamic_cast<Ball *>(con)) {
        shape = new SphereShape(dynamic_cast<const btSphereShape *>(cs));
        if (auto b0 = dynamic_cast<CueBall *>(b)) {
          cue = b0;
          scene->add(new FollowSpotLight(rb.getMotionState(), glm::vec3(0, 1, 0), glm::vec3(2, 2, 2), 0.1, 15));
        }
      } else if (auto b = dynamic_cast<Ground *>(con)) {
        const btTriangleMeshShape *tms = dynamic_cast<const btTriangleMeshShape *>(cs);
        const btStridingMeshInterface *interface = tms->getMeshInterface();
        if (interface->getNumSubParts() > 1)
          throw std::runtime_error("");
        shape = new TriangleMeshShape(tms, 0);
      } else if (auto b = dynamic_cast<Wall *>(con)) {
        shape = new BoxShape(dynamic_cast<const btBoxShape *>(cs));
      } else
        throw std::runtime_error("");
      auto render = new BulletShapeRender(shape, rb.getMotionState(), m);
      scene->add(render);
      con->setDestroyCallback([render]() -> void {
          scene->remove(render);
          delete render;
        });
    });

  /*
  gContactProcessedCallback = [](btManifoldPoint &cp, void *body0_, void *body1_) -> bool {
    auto body0 = static_cast<btCollisionObject *>(body0_);
    auto body1 = static_cast<btCollisionObject *>(body1_);

    void *p0 = body0->getUserPointer();
    void *p1 = body1->getUserPointer();

    static int ParticleFilter = 64;

    
    std::vector<glm::vec4> &colors;
    static auto material_spark{0, glm::vec3(0, 0, 0)};
    for (auto i = 0; i < 16; ++i) {
      static btBoxShape *shape = new btBoxShape(btVector3(0.001, 0.001, 0.001));
      static btQuaternion quaternion(0, 0, 0, 1);
      static const btScalar mass = 0.000001;
      static const int ParticleFilter = 64;
      
      btVector3 localInertia;
      shape->calculateLocalInertia(mass, localInertia);
      
      btMotionState *ms = new btDefaultMotionState(btTransform(quaternion, cp.getPositionWorldOnA()));
      btRigidBody *rb = new btRigidBody(mass, ms, shape, localInertia);

      static std::default_random_engine gen;
      static std::uniform_int_distribution<> dist;

      rb->setLinearVelocity(btVector3(dist(gen), dist(gen), dist(gen)));
      dynamicsWorld.addRigidBody(rb, ParticleFilter, btBroadphaseProxy::AllFilter);
      particles.push_back(rb);
      colors.push_back(glm::fvec4(255, 215, 0, 256) / 256.0f);
    }
    auto particle = new BulletParticle(particles, colors, material_spark);
    scene.add(particle);

    };
  */
  
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
        view.zoom(event.mouseWheelScroll.delta);
      }
    }
    static float moveSpeed = 1; //per second
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      view.moveUp(elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      view.moveUp(- elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      view.moveRight(-elapsed.asSeconds() * moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      view.moveRight(elapsed.asSeconds() * moveSpeed);

    cue->dir = btVector3();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      cue->dir += convert(view.up);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      cue->dir -= convert(view.up);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      cue->dir += convert(view.right);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      cue->dir -= convert(view.right);
    
    arena->step(elapsed.asSeconds());
    scene->render();

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
