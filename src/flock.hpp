#ifndef FLOCK_HPP
#define FLOCK_HPP
#include "boid.hpp"

class flock {
private:
  std::vector<boids> flock_;

public:
  void setFlockSize(int numBoids);
  inline boids operator[](int i) { return flock_[i]; }
  inline int size() { return flock_.size(); }
  std::vector<sf::Vector2f> getPositionFlock();
  std::vector<sf::Vector2f>
  getVelocityFlock(std::vector<sf::Vector2f> &posFlock,
                   std::vector<sf::Vector2f> &prevPosFlock);
  void drawFlock(sf::RenderWindow &window);
  void moveFlock(std::vector<sf::Vector2f> &velocity);
  void collision();
  inline std::vector<boids>::iterator begin() { return flock_.begin(); }
  inline std::vector<boids>::iterator end() { return flock_.end(); }
};

#endif
