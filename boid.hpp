#ifndef BOID_HPP
#define BOID_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "velox.hpp"
#include <SFML/Graphics/Texture.hpp>

class boids {
  sf::ConvexShape boid_1_;

public:
  boids();
  void drawBoid(sf::RenderWindow &window);
  void eraseBoid();
  void moveBoid();
  /*sf::Vector2f getpositionb();*/
  void getdistance(); // serve?
};
#endif