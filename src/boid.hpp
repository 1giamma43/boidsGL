#ifndef BOID_HPP
#define BOID_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "velox.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

class boids {
  sf::ConvexShape boid_1_;
public:

  boids();
  void drawBoid(sf::RenderWindow &window);
  void moveBoid(sf::Vector2f &velox);
  void setPositionBoid(float x,float y);
  float getVelocity(sf::Vector2f &vectorVelocity);
  sf::Vector2f getpositionb();
};
#endif