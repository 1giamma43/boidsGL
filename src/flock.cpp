#include "flock.hpp"
#include <iostream>
#include <random>

flock::flock(const int numBoids) {
  assert(numBoids >= 0);
  for (size_t i = 0; i < numBoids; i++) {
    boid B;
    characterizationBoid(B);
    std::random_device rd;
    std::uniform_int_distribution dist(-30, 30);
    sf::Vector2f q{static_cast<float>(dist(rd)), static_cast<float>(dist(rd))};
    velocityFLock_.push_back(q);
    flock_.push_back(B);
  }
}

void flock::setFlockSize(const int numBoids) {
  assert(numBoids >= 0);
  if (numBoids != flock_.size()) {
    if (numBoids > flock_.size()) {
      while (flock_.size() < numBoids) {
        boid B;
        characterizationBoid(B);
        std::random_device rd;
        std::uniform_int_distribution dist(-30, 30);
        sf::Vector2f q{static_cast<float>(dist(rd)),
                       static_cast<float>(dist(rd))};
        velocityFLock_.push_back(q);
        flock_.push_back(B);
      }
    } else {
      while (numBoids < flock_.size()) {
        std::random_device rd;
        int q = flock_.size() - 1;
        std::uniform_int_distribution dist(0, q);
        int i = dist(rd);
        flock_.erase(flock_.begin() + i);
        velocityFLock_.erase(velocityFLock_.begin() + i);
        flock_.shrink_to_fit();
      }
    }
  }
}

void flock::drawFlock(sf::RenderWindow &window) {
  for (auto &j : flock_) {
    window.draw(j.boid);
  }
}

const std::vector<sf::Vector2f> flock::getPositionFlock() {
  std::vector<sf::Vector2f> posBoids;
  for (auto b : flock_) {
    posBoids.push_back(b.boid.getPosition());
  }
  return posBoids;
}
void flock::collision() {

  for (auto &b : flock_) {
    if (b.boid.getPosition().x > 1000.f) {
      float p = b.boid.getPosition().x - 1000.f;
      b.boid.setPosition(p, b.boid.getPosition().y);
    }
  }

  for (auto &b : flock_) {
    if (b.boid.getPosition().x < 0.f) {
      float p = 1000.f + b.boid.getPosition().x;
      b.boid.setPosition(p, b.boid.getPosition().y);
    }
  }

  for (auto &b : flock_) {
    if (b.boid.getPosition().y > 600.f) {
      float p = b.boid.getPosition().y - 600.f;
      b.boid.setPosition(b.boid.getPosition().x, p);
    }
  }

  for (auto &b : flock_) {
    if (b.boid.getPosition().y < 0.f) {
      float p = 600.f + b.boid.getPosition().y;
      b.boid.setPosition(b.boid.getPosition().x, p);
    }
  }
}
std::vector<sf::Vector2f> flock::getVelocityFlock() { return velocityFLock_; }

void flock::moveFlock(const float d_s, const float d, const float s,
                      const float a, const float c,
                      std::vector<sf::Vector2f> &posBoids,
                      std::vector<sf::Vector2f> &vBoids,
                      std::array<sf::Vector2f, 4> &posObstacle) {
  for (size_t i = 0; i < flock_.size(); i++) {
    sf::Vector2f v =
        veloxBoid(i, d_s, d, s, a, c, posBoids, vBoids, posObstacle);
    if (v.x < 50.f && v.x > -50.f && v.y < 50.f && v.y > -50.f) {
      velocityFLock_.push_back(v);
      flock_[i].boid.move(v);
    } else {
      velocityFLock_.push_back(vBoids[i]);
      flock_[i].boid.move(vBoids[i]);
    }
  }
}

void characterizationObs(obstacle &O) {
  O.circle_.setRadius(10.f);
  O.circle_.setOrigin(10.f, 10.f);
  O.circle_.setPosition(O.position_);
  O.circle_.setFillColor(sf::Color(0, 0, 0));
}

void drawObs(sf::RenderWindow &window, obstacle &O) {
  characterizationObs(O);
  window.draw(O.circle_);
}

void characterizationBoid(boid &u) {
  u.boid.setPointCount(3);
  u.boid.setPoint(0, {0.f, 0.f});
  u.boid.setPoint(1, {45.f, 20.f});
  u.boid.setPoint(2, {20.f, 50.f});
  u.boid.setFillColor(sf::Color(204, 77, 5));
  u.boid.setOrigin({7.5f, 6.25f});
  u.boid.scale(0.25f, 0.25f);
  std::random_device rd;
  std::uniform_int_distribution dist(0, 1000);
  std::uniform_int_distribution dist1(0, 600);
  const float p = dist(rd);
  const float q = dist1(rd);
  u.boid.setPosition({p, q});
}
