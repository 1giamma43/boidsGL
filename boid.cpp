#include "boid.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <random>

boids::~boids() { delete[] &boid_1_; }

void boids::eraseBoid() { boids::~boids(); }

void boids::moveBoid() {
  // dà al boid una velocità casuale entro il range di -5.f e 5.f sulla x e
  // sulla y
  float q = static_cast<float>(rand() % 10 - 5.f);
  // per calcolare la velocità del boid ogni secondo ho bisogno della velocità
  // del boid il secondo precedente, se non impiega troppa memoria posso farlo
  // anche mezzo secondo prima o anche meno, usare la libreria chrono non so come...
  boid_1_.move({q + veloxBoid(k, d_s, d, s, a, c, ), q});
}

const sf::Vector2f boids::getpositionb() { return boid_1_.getPosition(); }
void boids::getdistance() {}