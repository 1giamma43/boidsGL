#include "boid.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <chrono>


boids::boids() {boid_1_.setPointCount(4); 
    boid_1_.setPoint(0, {0.f, 0.f});
    boid_1_.setPoint(1, {60.f, 20.f});
    boid_1_.setPoint(2, {40.f, 30.f});
    boid_1_.setPoint(3, {30.f, 50.f});
    boid_1_.setFillColor(sf::Color(204, 77, 5));
    boid_1_.setPosition(rand() % 800, rand() % 600);
    boid_1_.scale(0.4f,0.4f);  
    
  }

void boids::drawBoid(sf::RenderWindow &window) { window.draw(boid_1_); }

// elimina un boid
void boids::eraseBoid() { boids::~boids(); }

//muove un boid
void boids::moveBoid() {
  // dà al boid una velocità casuale entro il range di -5.f e 5.f sulla x e
  // sulla y
  
  // per calcolare la velocità del boid ogni secondo ho bisogno della velocità
  // del boid il secondo precedente, se non impiega troppa memoria posso farlo
  // anche mezzo secondo prima o anche meno, usare la libreria chrono non so come...
  boid_1_.move({horizontalV, verticalV});
  
}

// restituisce la posizione del boid
 sf::Vector2f boids::getpositionb() {
  sf::Vector2f position=boid_1_.getPosition();
  return position; } 

  // restituisce la distanza tra i boids 
void boids::getdistance() {}

void boids::setPositionBoid(float x, float y) {
  boid_1_.setPosition({x, y});
}