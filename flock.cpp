#include "flock.hpp"
#include <chrono>
#include <iostream>

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
      while (numBoids < flock_.size()) {
        // per adesso funziona però secondo me ha problemi di memoria
        int i = rand() % (flock_.size() - 1);
        flock_.erase(flock_.begin() + i);
        // flock_[i].eraseBoid();// capire come usare
        flock_.shrink_to_fit();
      }
    }
  }
}

void flock::moveFlock() {
  for (size_t i = 0; i < flock_.size(); i++) {
    flock_[i].moveBoid();
  }
}


void flock::collision() {
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().x > 800.f; })) {
    for (auto &b: flock_) {
      if (b.getpositionb().x > 800.f) {
        b.setPositionBoid(0.f, b.getpositionb().y);

      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().x < 0.f; })) {
    for (auto &b: flock_) {
      if (b.getpositionb().x < 0.f) {
        b.setPositionBoid(800.f, b.getpositionb().y);
        
      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().y > 600.f; })) {
    for (auto &b: flock_) {
      if (b.getpositionb().y > 600.f) {
      b.setPositionBoid(b.getpositionb().x, 0.f);
        
      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().y < 0.f; })) {
    for (auto &b: flock_) {
      if (b.getpositionb().y < 0.f) {
        b.setPositionBoid( b.getpositionb().x,600.f);
        
      }
    }
  }
}
