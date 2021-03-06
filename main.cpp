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

#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "CueBall.hpp"
#include "SnitchBall.hpp"
#include "FantasyBall.hpp"
#include "Smoke.hpp"
#include "Spark.hpp"
#include "Cloth.hpp"
#include "Anchor.hpp"

#include "Ground.hpp"
#include "Wall.hpp"

#include "SimpleLight.hpp"
#include "FollowSpotLight.hpp"
#include "MovingLight.hpp"
#include "ToggleLight.hpp"

#include "Scene.hpp"

#include "SphereShape.hpp"
#include "TriangleMeshShape.hpp"
#include "BoxShape.hpp"
#include "SoftBodyShape.hpp"

#include "Log.hpp"

#include "Importer.hpp"
#include "MaterialImporter.hpp"

#include "RigidBodyRender.hpp"
#include "SoftBodyRender.hpp"

#include "SimpleParticle.hpp"
#include "BulletParticle.hpp"

#include "ParticleController.hpp"

#include <btBulletDynamicsCommon.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>

#include <boost/filesystem.hpp>

#include <map>
#include <fstream>
#include <sstream>

#include <glm/gtc/constants.hpp>

#include "ContactHandler.hpp"


#include <exception>
#include <memory>

#include "SoundPool.hpp"


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
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  View view(glm::vec3(0, 1.5, 1.5), glm::vec2(-glm::pi<float>(), -1.0));
  Projection projection(45, 4.0f/3, 0.1, 100);
  scene = new Scene(view, projection);
  
  Light::Spec spec;
  spec.position = glm::fvec4(0, 1, 1, 1);
  spec.intensities = glm::fvec3(1, 1, 1);
  spec.attenuation = 1;
  spec.ambientCoefficient = 0.05f;
  spec.coneAngle = 45.0f;
  spec.coneDirection = glm::vec3(0, -1, -1);
  SimpleLight light0(spec);
  scene->add(&light0);

  
  Light::Spec spec2;
  spec2.position = glm::fvec4(0, 1, -1, 1);
  spec2.intensities = glm::fvec3(1, 1, 1);
  spec2.attenuation = 1;
  spec2.ambientCoefficient = 0.05f;
  spec2.coneAngle = 45.0f;
  spec2.coneDirection = glm::vec3(0, -1, 1);
  SimpleLight light2(spec2);
  scene->add(&light2);

  const btVector3 gravity(0, -9.8, 0);

  btVector3 worldAabbMin(-10, -10, -10);
  btVector3 worldAabbMax(10, 10, 10);
  
  btDbvtBroadphase broadphase;
  //btAxisSweep3 broadphase(worldAabbMin, worldAabbMax, 1024);
  btSoftBodyRigidBodyCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher(&collisionConfiguration);
  btSequentialImpulseConstraintSolver solver;
  btSoftRigidDynamicsWorld world(&dispatcher, &broadphase, &solver, &collisionConfiguration);
  world.setGravity(gravity);

  arena = new Arena(world);

  std::map<btRigidBody *, Render *> bodies;
  CueBall *cue;
  ToggleLight *tl;

  Importer importer(*arena);
  importer.loadArena(boost::filesystem::path("arenas/simple.arena"), [&cue, &tl](Controller *const con, istream &is) -> void {
      string materialPath;
      is >> materialPath;

      static MaterialImporter mi;
      Render::Material m = mi.import(materialPath);
      
      Shape *shape;
      auto sc = dynamic_cast<SingleController *const>(con);
      if (sc == NULL)
        return ;
      const btRigidBody &rb = sc->getBody();

      const btCollisionShape *const cs = rb.getCollisionShape();
      if (auto b = dynamic_cast<Ball *>(con)) {
        shape = new SphereShape(dynamic_cast<const btSphereShape *>(cs));
        if (auto b0 = dynamic_cast<CueBall *>(b)) {
          auto spec = new Light::Spec();
          spec->position = glm::vec4(0, 1, 0, 1);
          spec->intensities = glm::vec3(2, 2, 2);
          spec->attenuation = 0.1;
          spec->coneAngle = 15;
          spec->ambientCoefficient = 0;
          cue = b0;
          auto sl = new SimpleLight(*spec);
          auto fsl = new FollowSpotLight(rb.getMotionState(), *sl);
          tl = new ToggleLight(*fsl);
          scene->add(tl);
        } else if (auto b0 = dynamic_cast<SnitchBall *>(b)) {
          auto spec = new Light::Spec();
          spec->intensities = glm::vec3(2, 1.68, 0);
          spec->attenuation = 2;
          spec->ambientCoefficient = 0;
          spec->coneAngle = 180;
          spec->coneDirection = glm::vec3(0, -1, 0);
          auto light = new SimpleLight(*spec);
          scene->add(new MovingLight(rb.getMotionState(), *light));
        } else if (auto b0 = dynamic_cast<FantasyBall *>(b)) {
          auto color = new glm::vec4(0.11, 0.16, 0.0, 1);
          auto noise = new PerlinNoise();
          float radius = dynamic_cast<const btSphereShape *>(rb.getCollisionShape())->getRadius();
          float pi = glm::pi<float>();
          auto sc = new Smoke([&rb, radius, pi]() -> glm::vec4 {
              auto center = convert<glm::vec3>(rb.getWorldTransform().getOrigin());
              float u = random<float>(0, 1), v = random<float>(-1, 1);
              float phi = 2 * pi * u;
              float theta = glm::acos(v);
              return glm::vec4(center + glm::vec3(sin(theta) * sin(phi),
                                                  cos(theta),
                                                  sin(theta) * cos(phi)) * radius, 0.007);
            }, 20000, 20000, *color, *noise);
          auto m = new Particle::Material{0, glm::vec3(0, 0, 0), 0};
          auto sp = new SimpleParticle(sc->getNum(), sc->getVertOffset(), sc->getVertColor(), *m);
          arena->add(sc);
          sc->setDestroyCallback([sp]() {
              scene->remove(sp);
              delete sp;
            });
          scene->add(sp);
        }
      } else if (auto b = dynamic_cast<Ground *>(con)) {
        const btTriangleMeshShape *tms = dynamic_cast<const btTriangleMeshShape *>(cs);
        const btStridingMeshInterface *interface = tms->getMeshInterface();
        if (interface->getNumSubParts() > 1)
          throw std::runtime_error("TriangleMeshShape with more than 1 subpart");
        shape = new TriangleMeshShape(tms, 0);
      } else if (auto b = dynamic_cast<Wall *>(con)) {
        shape = new BoxShape(*dynamic_cast<const btBoxShape *>(cs));
      } else
        throw std::runtime_error("unrecognized controller. WTF?");
      auto render = new RigidBodyRender(shape, rb.getMotionState(), m);
      scene->add(render);
      con->setDestroyCallback([render]() -> void {
          scene->remove(render);
          delete render;
        });
    });

  btSoftBodyWorldInfo worldinfo;
  worldinfo.m_broadphase = &broadphase;
  worldinfo.m_dispatcher = &dispatcher;
  worldinfo.m_sparsesdf.Initialize();
  worldinfo.m_gravity = gravity;
  worldinfo.air_density = 1.2f;
  worldinfo.water_density = 0;
  worldinfo.water_offset = 0;
  worldinfo.water_normal = btVector3(0, 0, 0);
  std::vector<glm::vec2> uv;
  std::vector<glm::ivec3> faces;
  Cloth::getRectangle(10, 10, uv, faces);
  auto cloth = new Cloth(worldinfo, uv, faces,
                         glm::vec3(-0.5, 2, 0),
                         glm::vec3(0, -0.4, 0),
                         glm::vec3(0.6, 0, 0));


  btSoftBody &cloth_body = cloth->getBody();
  auto sbs = new SoftBodyShape(cloth->getBody(), uv);
  Render::Material m_flag{FileTexture::get(GL_TEXTURE0, "res/flag1.png"),
      50, glm::vec3(0, 0, 0), 0};
  auto sbr = new SoftBodyRender(sbs, m_flag);
  scene->add(sbr);
  cloth->setDestroyCallback([sbr]() {
      scene->remove(sbr);
      delete sbr;
    });
  arena->add(cloth);

  auto anchor0 = new Anchor(btVector3(-0.5, 2, 0));
  auto anchor1 = new Anchor(btVector3(0.1, 2, 0));
  cloth_body.appendAnchor(0, &anchor0->getBody());
  cloth_body.appendAnchor(10, &anchor1->getBody());
  cloth_body.setWindVelocity(btVector3(1, 0, 1));

  const size_t spark_num = 1024;
  const float spark_radius = 0.01;
  btBoxShape spark_shape(btVector3(spark_radius, spark_radius, spark_radius));
  Particle::Material spark_material{100, glm::vec3(0, 0, 0), 1};
  auto spark = new Spark(spark_num, 1, &spark_shape,
                         btQuaternion(0, 0, 0, 1), 0.001, 64, glm::vec4(215, 255, 0, 256) / 256.0f);
  auto spark_particle = new BulletParticle(spark_num, spark->getGroup(), spark->getVertColor(), spark_material, spark_radius);
  spark->setDestroyCallback([&spark_particle]() {
      scene->remove(spark_particle);
      delete spark_particle;
    });
  arena->add(spark);
  scene->add(spark_particle);
  
  gContactProcessedCallback = ContactHandler<Controller>::handle;
  ContactHandler<Controller>::add(typeid(CueBall), typeid(SnitchBall),
                                  [spark, spark_num](btManifoldPoint &cp,
                                     btRigidBody *const rb0,
                                     btRigidBody *const rb1,
                                     Controller *const b0, Controller *const b1) -> void {
                                    auto count = min((size_t)(cp.getAppliedImpulse() * 10000), spark_num);
                                    for (auto i = 0; i < count; ++i)
                                      spark->add(cp.getPositionWorldOnA(), 2);
                                  });

  ContactHandler<Controller>::add(typeid(CueBall), typeid(FantasyBall),
                                  [](btManifoldPoint &cp,
                                     btRigidBody *const rb0,
                                     btRigidBody *const rb1,
                                     Controller *const b0, Controller *const b1) -> void {
                                    CueBall *cue = dynamic_cast<CueBall *>(b0);
                                    FantasyBall *f = dynamic_cast<FantasyBall *>(b1);
                                    //cue->setFantasy(f->getDuration());
                                  });

  const std::type_info *ti_ball[] = {
    &typeid(SnitchBall),
    &typeid(WanderBall),
    &typeid(GhostBall),
    &typeid(CueBall),
    &typeid(FantasyBall)
  };

  const std::type_info *ti_wall[] = {
    //&typeid(Ground),
    &typeid(Wall)
  };

  SoundPool sp;

  sf::SoundBuffer buffer0;
  if (!buffer0.loadFromFile("res/ball-wall.wav")) {
    return -1;
  }

  for (auto i : ti_ball)
    for (auto j : ti_wall)
      ContactHandler<Controller>::add(*i, *j, [&buffer0, &sp](btManifoldPoint &cp,
                                                              btRigidBody *const rb0,
                                                              btRigidBody *const rb1,
                                                              Controller *const b0, Controller *const b1) {
                                        const float vol = glm::pow(cp.getAppliedImpulse() * 200, 2);
                                        if (vol < 1)
                                          return ;
                                        auto sound = sp.pop();
                                        sound->setBuffer(buffer0);
                                        sound->setPosition(convert<sf::Vector3f>(cp.getPositionWorldOnA()));
                                        sound->setMinDistance(5.0f);
                                        sound->setAttenuation(10.f);
                                        sound->setVolume(vol);

                                        sound->play();
                                        sp.push(sound);
                                      });

  sf::SoundBuffer buffer1;
  if (!buffer1.loadFromFile("res/ball-ball.wav")) {
    return -1;
  }

  for (auto i : ti_ball)
    for (auto j : ti_ball)
      ContactHandler<Controller>::add(*i, *j, [&buffer1, &sp](btManifoldPoint &cp,
                                                              btRigidBody *const rb0,
                                                              btRigidBody *const rb1,
                                                              Controller *const b0, Controller *const b1) {
                                        const float vol = glm::pow(cp.getAppliedImpulse() * 500, 2);
                                        if (vol < 1)
                                          return ;
                                        auto sound = sp.pop();
                                        sound->setBuffer(buffer1);
                                        sound->setPosition(convert<sf::Vector3f>(cp.getPositionWorldOnA()));
                                        sound->setMinDistance(5.0f);
                                        sound->setAttenuation(10.f);
                                        sound->setVolume(vol);
                                        sound->play();
                                        sp.push(sound);
                                      }, false);


  /*
  PerlinNoise noise;
  NoiseTexture texGreen(GL_TEXTURE0, noise, 800, 800, glm::vec4(0, 0,
  0, 255), glm::vec4(0.22, 0.32, 0.0, 1) * 256.0f);
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
        view.zoom(event.mouseWheelScroll.delta * 0.1);
      } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::H)
          tl->toggle();
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
      cue->dir += convert<btVector3>(view.up);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      cue->dir -= convert<btVector3>(view.up);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      cue->dir += convert<btVector3>(view.right);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      cue->dir -= convert<btVector3>(view.right);
    
    arena->step(elapsed.asSeconds());
    sf::Listener::setPosition(convert<sf::Vector3f>(view.eye));
    sf::Listener::setDirection(convert<sf::Vector3f>(view.direction));
    sf::Listener::setUpVector(convert<sf::Vector3f>(view.up));
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
