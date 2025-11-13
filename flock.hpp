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
  //std::vector<sf::Vector2f> getVelocityBoids(int i);
  std::vector<sf::Vector2f> getPositionFlock();
  std::vector<sf::Vector2f> getVelocityFlock(std::vector<sf::Vector2f> &posFlock, std::vector<sf::Vector2f> &prevPosFlock);
  void drawFlock(sf::RenderWindow &window);
  void setInitVelocityF();
  void moveFlock(float d_s, float d, float s, float a, float c, std::vector<sf::Vector2f> &posFlock,
                        std::vector<sf::Vector2f> &vBoids);
  void collision();
  std::vector<boids>::iterator begin(){return flock_.begin();}
   std::vector<boids>::iterator end(){return flock_.end();}
};

#endif
