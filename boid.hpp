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
  //float posX_;
  //float posY_;

public:

  boids();
  void drawBoid(sf::RenderWindow &window);
  void eraseBoid();
  void setInitVelocity();
  void moveBoid(sf::Vector2f &velox);
  void setPositionBoid(float x,float y);
  void getdistance(); // serve?
  void rotate(float angle);
  float getVelocity(sf::Vector2f &vectorVelocity);
  sf::Vector2f getpositionb();
    float horizontalV = static_cast<float>(rand() % 10 - 5);
  float verticalV = static_cast<float>(rand() % 10 - 5);
  //void updatePos(float deltaTime,int k, float d_s, float d, float s, float a, float c,
    //                  std::vector<sf::Vector2f> &posBoids,
      //                std::vector<sf::Vector2f> &vBoids);

};
#endif