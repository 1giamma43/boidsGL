#ifndef FLOCK_HPP
#define FLOCK_HPP
#include "boid.hpp"
#include <chrono>

class flock {
private:
  std::vector<boids> flock_;
  

public:
  
   void setFlockSize(int numBoids);
   boids operator [] (int i) { return flock_[i]; }
   int size() { return flock_.size(); }
  /*std::vector<sf::Vector2f> getVelocityBoids(int i);
  std::vector<sf::Vector2f> getPositionBoids();
  void moveFlock(float d_s, float d, float s, float a, float c,
                 std::vector<sf::Vector2f> &vBoids);*/
  void drawFlock(sf::RenderWindow &window);
  void moveFlock();
};

#endif
