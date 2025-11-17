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
  assert(numBoids >= 0 && numBoids <= 30);
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
  sf::Vector2f vel={0.f,0.f};
  for (size_t i = 0; i < flock_.size(); i++) {
    vel=veloxBoid(i, d_s, d, s, a, c, posFlock, vFlock);
    if (vel.x<50.f && vel.x>-50.f && vel.y<50.f && vel.y>-50.f)
    {
       flock_[i].moveBoid(
        vel);
    }   
  }
}

/*void flock::rotateFlock(std::vector<sf::Vector2f> &vBoidsPrev) {
  for(size_t i=0; i<flock_.size(); i++){
   
    
    flock_[i].rotate(angle);
  }
}*/

void flock::collision() { // forse è meglio togliere any_of e fare tutto con un
                          // solo ciclo
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().x > 800.f; })) {
    for (auto &b : flock_) {
      if (b.getpositionb().x > 800.f) {
        b.setPositionBoid(0.f, b.getpositionb().y);
      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().x < 0.f; })) {
    for (auto &b : flock_) {
      if (b.getpositionb().x < 0.f) {
        b.setPositionBoid(800.f, b.getpositionb().y);
      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().y > 600.f; })) {
    for (auto &b : flock_) {
      if (b.getpositionb().y > 600.f) {
        b.setPositionBoid(b.getpositionb().x, 0.f);
      }
    }
  }
  if (std::any_of(flock_.begin(), flock_.end(),
                  [](boids &boid) { return boid.getpositionb().y < 0.f; })) {
    for (auto &b : flock_) {
      if (b.getpositionb().y < 0.f) {
        b.setPositionBoid(b.getpositionb().x, 600.f);
      }
    }
  }
}