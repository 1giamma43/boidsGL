#ifndef FLOCK_HPP
#define FLOCK_HPP
#include "boid.hpp"


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
  void moveFlock(std::vector<sf::Vector2f>& velocity);
  //void rotateFlock(std::vector<sf::Vector2f> &vBoidsPrev);
  void collision();
  std::vector<boids>::iterator begin(){return flock_.begin();}
   std::vector<boids>::iterator end(){return flock_.end();}
};

#endif
