#include "flock.hpp"
#include <chrono>
#include <iostream>

// disegna i boids nella finestra
void flock::drawFlock(sf::RenderWindow &window) {
  for (auto j : flock_) {
    j.drawBoid(window);
  }
}

// restituisce le posizioni di tutti i boids nello stormo
std::vector<sf::Vector2f> flock::getPositionFlock() {
  std::vector<sf::Vector2f> posBoids = {{}};
  for (auto i : flock_) {
    posBoids.push_back(i.getpositionb());
  }
  return posBoids;
}

std::vector<sf::Vector2f>
flock::getVelocityFlock(std::vector<sf::Vector2f> &posFlock,
                        std::vector<sf::Vector2f> &prevPosFlock) {
  // cosa fare se i due vettori hanno dimensioni diverse?
  std::vector<sf::Vector2f> velocityBoids = {};
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
        // per adesso funziona però secondo me ha problemi di memoria
        int i = rand() % (flock_.size() - 1);
        flock_.erase(flock_.begin() + i);
        // flock_[i].eraseBoid();// capire come usare
        flock_.shrink_to_fit();
      }
    }
  }
}

void flock::setInitVelocityF() {
  for (size_t i = 0; i < flock_.size(); i++) {
    flock_[i].setInitVelocity();
  }
}

void flock::moveFlock(float d_s, float d, float s, float a, float c,
                      std::vector<sf::Vector2f> &posFlock,
                      std::vector<sf::Vector2f> &vFlock) {
  sf::Vector2f vel = {0.f, 0.f};
  for (size_t i = 0; i < flock_.size(); i++) {
    vel = veloxBoid(i, d_s, d, s, a, c, posFlock, vFlock);
    if (vel.x < 50.f && vel.x > -50.f && vel.y < 50.f && vel.y > -50.f) {
      flock_[i].moveBoid(vel);
    } 
  }
}

/*void flock::rotateFlock(std::vector<sf::Vector2f> &vBoidsPrev) {
  for(size_t i=0; i<flock_.size(); i++){


    flock_[i].rotate(angle);
  }
}*/

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