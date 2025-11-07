#include "flock.hpp"
#include <chrono>

// determina il movimento dello stormo
/*void flock::moveFlock(float d_s, float d, float s, float a, float c,
                      std::vector<sf::Vector2f> &vBoids) {

  for (auto b : flock_) {
    int j = 0;
    b.moveBoid();
   std::vector<sf::Vector2f> pBoids= getPositionBoids();
   std::vector<sf::Vector2f> vBoids= getVelocityBoids(j);
    veloxBoid(j,d_s, d, s, a, c, pBoids, vBoids).x;

    j++;
  }

}

// restituisce le posizioni di tutti i boids nello stormo
std::vector<sf::Vector2f> flock::getPositionBoids() {
  std::vector<sf::Vector2f> posBoids = {{}};
  for (auto i : flock_) {
    posBoids.push_back(i.getpositionb());
  }
  return posBoids;
}

// restituisce le velocità di tutti i boids nello stormo
std::vector<sf::Vector2f> flock::getVelocityBoids(int i) {
  std::vector<sf::Vector2f> velocityBoids = {{}};
  for (auto j : flock_) {
  }

  return;
}*/

// disegna i boids nella finestra
void flock::drawFlock(sf::RenderWindow &window) {
  for (auto j : flock_) {
    j.drawBoid(window);
  }
}

void flock::setFlockSize(int numBoids) {
  if (numBoids != flock_.size()) {   
    if (numBoids > flock_.size()) {
      while (flock_.size() < numBoids) {
        boids m;
        flock_.push_back(m);
      }
    } else {
      flock_[rand() % (flock_.size() - 1)].eraseBoid();
    }
  }
}

void flock::moveFlock() {
  for (size_t i = 0; i < flock_.size(); i++)
  {
  flock_[i].moveBoid();}
}
