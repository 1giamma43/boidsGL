#include "boid.hpp"


class flock {  
private:
  std::vector<boids> flock_;
  int i = 1;

public:

  flock(std::vector<boids> nBoids_) : flock_{nBoids_} {

    if (i >= flock_.size()) {
      while (flock_.size() < i) {
        boids m();
        flock_.push_back(m());
      }
    } else {
      flock_[rand() % (flock_.size() - 1)].eraseBoid();
    }
  };
  std::vector<sf::Vector2f> getvelocityBoids();
  std::vector<sf::Vector2f> getPositionBoids();
  void moveFlock(float d_s,float d, float s, float a, float c,
                 std::vector<sf::Vector2f> &vBoids);

  void renderWindow();
  void updateWindow();
  void drawBoids(sf::RenderWindow &window);
  void display();
};

