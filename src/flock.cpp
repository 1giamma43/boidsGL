#include "flock.hpp"
#include <iostream>

// disegna i boids nella finestra
void flock::drawFlock(sf::RenderWindow &window) {
  for (auto j : flock_) {
    j.drawBoid(window);
  }
}

// restituisce le posizioni di tutti i boids nello stormo
std::vector<sf::Vector2f> flock::getPositionFlock() {
  std::vector<sf::Vector2f> posBoids;
  for (auto b : flock_) {
    posBoids.push_back(b.getpositionb());
  }
  return posBoids;
}

std::vector<sf::Vector2f>
flock::getVelocityFlock(std::vector<sf::Vector2f> &posFlock,
                        std::vector<sf::Vector2f> &prevPosFlock) {
  // cosa fare se i due vettori hanno dimensioni diverse?
  std::vector<sf::Vector2f> velocityBoids;
  for (size_t i = 0; i < posFlock.size(); i++) {
    velocityBoids.push_back({(posFlock[i].x - prevPosFlock[i].x),
                             (posFlock[i].y - prevPosFlock[i].y)});
  }
  return velocityBoids;
}

void flock::setFlockSize(int numBoids) {
  assert(numBoids >= 0);
  if (numBoids != flock_.size()) {
    if (numBoids > flock_.size()) {
      while (flock_.size() < numBoids) {
        boids m;
        flock_.push_back(m);
      }
    } else {
      while (numBoids < flock_.size()) {
        int i = rand() % (flock_.size() - 1);
        flock_.erase(flock_.begin() + i);
        flock_.shrink_to_fit();
      }
    }
  }
}

void flock::moveFlock(std::vector<sf::Vector2f>& velocity) {
  for (size_t i = 0; i < flock_.size(); i++) {
    if (velocity[i].x < 50.f && velocity[i].x > -50.f && velocity[i].y < 50.f && velocity[i].y > -50.f) {
      flock_[i].moveBoid(velocity[i]);
    } 
  }
}

void flock::collision() { 

  for (auto &b : flock_) {
    if (b.getpositionb().x > 1000.f) {
      float p=b.getpositionb().x-1000.f;
      b.setPositionBoid(p, b.getpositionb().y);
    }
  }

  for (auto &b : flock_) {
    if (b.getpositionb().x < 0.f) {
      float p=1000.f+b.getpositionb().x;
      b.setPositionBoid(p, b.getpositionb().y);
    }
  }

  for (auto &b : flock_) {
    if (b.getpositionb().y > 600.f) {
      float p=b.getpositionb().y-600.f;
      b.setPositionBoid(b.getpositionb().x, p);
    }
  }

  for (auto &b : flock_) {
    if (b.getpositionb().y < 0.f) {
      float p=600.f+b.getpositionb().y;
      b.setPositionBoid(b.getpositionb().x, p);
    }
  }
}