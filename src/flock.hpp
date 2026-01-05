#ifndef FLOCK_HPP
#define FLOCK_HPP
#include "velox.hpp"
#include <cassert>
namespace Bd {
struct boid {
  sf::ConvexShape boid;
};
void characterizationBoid(Bd::boid &u);
} // namespace Bd
namespace fl {
class flock {
private:
  std::vector<Bd::boid> flock_;
  std::vector<sf::Vector2f> velocityFLock_;

public:
  flock(const int numBoids);
  void set_FlockSize(const int numBoids);
  void draw_Flock(sf::RenderWindow &window);
  const std::vector<sf::Vector2f> getPositionFlock();
  void collision();
  std::vector<sf::Vector2f> getVelocityFlock();
  void moveFlock(const float d_s, const float d, const float s, const float a,
                 const float c, std::vector<sf::Vector2f> &posBoids,
                 std::vector<sf::Vector2f> &vBoids,
                 std::array<sf::Vector2f, 4> &posObstacle);

  inline Bd::boid operator[](int i) { return flock_[i]; }
  inline int size() { return flock_.size(); }
  inline std::vector<Bd::boid>::iterator begin() { return flock_.begin(); }
  inline std::vector<Bd::boid>::iterator end() { return flock_.end(); }
};
} // namespace fl
namespace obs {
struct obstacle {
  sf::CircleShape circle_;
  sf::Vector2f position_;
};
void characterizationObs(obs::obstacle &O);
void draw_Obs(sf::RenderWindow &window, obs::obstacle &O);
} // namespace obs

#endif