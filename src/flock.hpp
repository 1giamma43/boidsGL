#ifndef FLOCK_HPP
#define FLOCK_HPP
#include "velox.hpp"
#include <cassert>

struct boid {
  sf::ConvexShape boid;
};
struct obstacle {
  sf::CircleShape circle_;
  sf::Vector2f position_;
};
class flock {
private:
  std::vector<boid> flock_;
  std::vector<sf::Vector2f> velocityFLock_;

public:
  flock(const int numBoids);
  void setFlockSize(const int numBoids);
  void drawFlock(sf::RenderWindow &window);
  const std::vector<sf::Vector2f> getPositionFlock();
  void collision();
  std::vector<sf::Vector2f> getVelocityFlock();
  void moveFlock(const float d_s, const float d, const float s, const float a,
                 const float c, std::vector<sf::Vector2f> &posBoids,
                 std::vector<sf::Vector2f> &vBoids,
                 std::array<sf::Vector2f, 4> &posObstacle);

  inline boid operator[](int i) { return flock_[i]; }
  inline int size() { return flock_.size(); }
  inline std::vector<boid>::iterator begin() { return flock_.begin(); }
  inline std::vector<boid>::iterator end() { return flock_.end(); }
};
// obstacle
void characterizationObs(obstacle &O);
void drawObs(sf::RenderWindow &window, obstacle &O);
// boid
void characterizationBoid(boid &u);
#endif