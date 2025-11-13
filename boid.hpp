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
  void setInitVelocity();
  void moveBoid(sf::Vector2f velox);
  sf::Vector2f getpositionb();
  void setPositionBoid(float x,float y);
  void getdistance(); // serve?
  float horizontalV = static_cast<float>(rand() % 10 - 5);
  float verticalV = static_cast<float>(rand() % 10 - 5);
};
#endif