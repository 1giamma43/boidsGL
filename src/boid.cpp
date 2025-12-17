#include "boid.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>

boids::boids() {
  boid_1_.setPointCount(4);
  boid_1_.setPoint(0, {0.f, 0.f});
  boid_1_.setPoint(1, {60.f, 20.f});
  boid_1_.setPoint(2, {40.f, 30.f});
  boid_1_.setPoint(3, {30.f, 50.f});
  boid_1_.setFillColor(sf::Color(204, 77, 5));
  boid_1_.setOrigin({7.5f,6.25f});
  boid_1_.scale(0.25f, 0.25f);
  float p=rand()%1000;
  float q=rand()%600;
  boid_1_.setPosition({p,q});
  
  
  // posX_ = boid_1_.getPosition().x;
  // posY_ = boid_1_.getPosition().y;
}

void boids::moveBoid(sf::Vector2f &velox) { boid_1_.move(velox); }

float boids::getVelocity(sf::Vector2f &vectorVelocity) {
  float velocity = sqrt(powf(vectorVelocity.x, 2) + powf(vectorVelocity.y, 2));
  return velocity;
}

// restituisce la posizione del boid
sf::Vector2f boids::getpositionb() {
  sf::Vector2f position = boid_1_.getPosition();
  return position;
}

void boids::setPositionBoid(float x, float y) { boid_1_.setPosition({x, y}); }

void boids::drawBoid(sf::RenderWindow &window) { window.draw(boid_1_); }

/*void boids::updatePos(float deltaTime, int k, float d_s, float d, float s,
                      float a, float c, std::vector<sf::Vector2f> &posBoids,
                      std::vector<sf::Vector2f> &vBoids) {
  sf::Vector2f vel = veloxBoid(k, d_s, d, s, a, c, posBoids, vBoids);
  vel.x = vel.x / 100;
  vel.y = vel.y / 100;
  std::cout << "vel x: " << vel.x << " vel y: " << vel.y << "\n";
  if (vel.x < 100.f && vel.x > -100.f && vel.y < 100.f && vel.y > -100.f) {
    posX_ += boid_1_.getPosition().x +
             veloxBoid(k, d_s, d, s, a, c, posBoids, vBoids).x * deltaTime;
    posY_ += boid_1_.getPosition().y +
             veloxBoid(k, d_s, d, s, a, c, posBoids, vBoids).y * deltaTime;
    boid_1_.setPosition({posX_, posY_});
  }


}*/
