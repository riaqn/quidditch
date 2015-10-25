#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 0;
  settings.attributeFlags = sf::ContextSettings::Attribute::Debug;
  
  sf::RenderWindow window(sf::VideoMode(800, 600), "test", sf::Style::Close, settings);
  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);

  glewExperimental = GL_TRUE;
  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
    return EXIT_FAILURE;
  }

  sf::Font font;
  if (!font.loadFromFile("/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc")) {
    return -1;
  }
  
  while (true) {
    sf::Text text;
    text.setFont(font);
    text.setString("mother fucker");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);
    text.setPosition(100,100);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    window.draw(text);

    //window.popGLStates();
    window.display();
  }
}
