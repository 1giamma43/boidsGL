#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "velox.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
// #include "doctest.h"
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
// posso mettere quella roba delle posizioni toro etc dentro quel for  cambiare
// il vecModDistanze dicendogli qual è la vera distanza e per la velocità cambio
// il segno così dovrebbe amdare verso l'esterno
std::vector<sf::Vector2f> veloxBoid(float d_s, float d, float s, float a,
                                    float c,
                                    std::vector<sf::Vector2f> &posBoids,
                                    std::vector<sf::Vector2f> &vBoids) {
  std::vector<sf::Vector2f> vectorVel;
  for (long unsigned int k = 0; k < posBoids.size(); k++) {
    std::vector<sf::Vector2f> nearBoids, nearVelocity;
    std::vector<float> vecModDistanze =
        vecModDistance(k, posBoids, posBoids[k]);

    for (long unsigned int i = 0; i < posBoids.size(); i++) {
      if (vecModDistanze[i] < d) {
        nearBoids.push_back(posBoids[i]);
        nearVelocity.push_back(vBoids[i]);
      }
    }
    if (nearBoids.empty()) {
      nearBoids.push_back({0.f, 0.f});
      nearVelocity.push_back({0.f, 0.f});
    }

    // computo la velocità del boid k come somma vettoriale delle 4 componenti
    vectorVel.push_back(
        {vBoids[k].x + separazione(d_s, s, nearBoids, posBoids[k]).x +
             allineamento(a, nearVelocity, vBoids[k]).x +
             coesione(c, nearBoids, posBoids[k]).x,
         vBoids[k].y + separazione(d_s, s, nearBoids, posBoids[k]).y +
             allineamento(a, nearVelocity, vBoids[k]).y +
             coesione(c, nearBoids, posBoids[k]).y});
  }
  return vectorVel;
}

sf::Vector2f separazione(float d_s, float s,
                         std::vector<sf::Vector2f> &nearBoids,
                         sf::Vector2f &posBoid_1) {
  if (s < 0) {
    throw std::runtime_error(
        "Errore: il parametro s dev'essere maggiore o uguale di 0");
  }

  // creo un vettore con la somma delle posizioni dei boids con distanza minore
  // di d_s
  float distance = 0;
  sf::Vector2f vSeparation = {0.f, 0.f};
  int i = 0;
  for (auto &j : nearBoids) {

    distance = sqrt(powf(vecDistance(nearBoids, posBoid_1)[i].x, 2) +
                    powf(vecDistance(nearBoids, posBoid_1)[i].y, 2));
    if (distance < d_s) {
      vSeparation.x += (j.x - posBoid_1.x);
      vSeparation.y += (j.y - posBoid_1.y);
    }
    i++;
  }

  // calcolo la velocità di separazione
  vSeparation.x = -s * vSeparation.x;
  vSeparation.y = -s * vSeparation.y;

  return vSeparation;
}

sf::Vector2f allineamento(float a, std::vector<sf::Vector2f> &vBoids,
                          sf::Vector2f &vBoid_1) {
  if (a < 0 || a > 1) {
    throw std::runtime_error("Errore: il parametro a dev'essere maggiore o "
                             "uguale di 0 e minore di 1");
  }

  // calcola la media delle velocità dei boids
  sf::Vector2f meanVel = {0.0f, 0.0f};
  meanVel =
      std::accumulate(vBoids.begin(), vBoids.end(), meanVel,
                      [](sf::Vector2f acc, sf::Vector2f &vBoids) {
                        return sf::Vector2f{acc.x + vBoids.x, acc.y + vBoids.y};
                      });
  // calcola la velocità di allineamento
  sf::Vector2f vAllineamento = {a * ((meanVel.x / vBoids.size()) - vBoid_1.x),
                                a * ((meanVel.y / vBoids.size()) - vBoid_1.y)};
  return vAllineamento;
}

sf::Vector2f coesione(float c, std::vector<sf::Vector2f> &nearBoids,
                      sf::Vector2f &posBoid_1) {
  // calcola il centro di massa dei boids vicini

  sf::Vector2f CM = {};
  CM = std::accumulate(nearBoids.begin(), nearBoids.end(), CM,
                       [](sf::Vector2f acc, sf::Vector2f &nearBoids) {
                         return sf::Vector2f{acc.x + nearBoids.x,
                                             acc.y + nearBoids.y};
                       });
  sf::Vector2f vCoesione = {c * ((CM.x / nearBoids.size()) - posBoid_1.x),
                            c * ((CM.y / nearBoids.size()) - posBoid_1.y)};
  return vCoesione;
}

////////////////////////////////////////////////////////////////////////

std::vector<sf::Vector2f> vecDistance(std::vector<sf::Vector2f> &nearBoids,
                                      sf::Vector2f &posBoid_1) {
  // crea un vettore con le distanze tra i boids j e il boid 1
  std::vector<sf::Vector2f> nearBoids2;
  for (auto &j : nearBoids) {
    nearBoids2.push_back({j.x - posBoid_1.x, j.y - posBoid_1.y});
  }
  return nearBoids2;
}

std::vector<float> vecModDistance(int k, std::vector<sf::Vector2f> &posBoids,
                                  sf::Vector2f &posBoid_1) {
  std::vector<float> vecModDistanze;
  for (size_t k = 0; k < posBoids.size(); k++) {
    // questa matrice è simmetrica quindi si può evitare di calcolare due volte
    // lo stesso valore
    for (long unsigned int i = 0; i < posBoids.size(); i++) {
      if (i == k) {
        continue;
      }
      float distance = sqrt(powf(vecDistance(posBoids, posBoids[k])[i].x, 2) +
                            powf(vecDistance(posBoids, posBoids[k])[i].y, 2));
      vecModDistanze.push_back(distance);
    }
  }
  return vecModDistanze;
}

std::vector<float> vecModVelox(std::vector<sf::Vector2f> &velocityVector) {
  std::vector<float> VEC;
  // cambiato for normale con questo for qua
  for (auto &j : velocityVector) {
    VEC.push_back(sqrt(powf(j.x, 2) + powf(j.y, 2)));
  }
  return VEC;
}

float calculateMean(std::vector<float> &vecMod) {
  float mean = std::accumulate(vecMod.begin(), vecMod.end(), 0.0f);
  return mean / vecMod.size();
}

float calculateStdDeviation(std::vector<float> &vector) {
  float mu = calculateMean(vector);
  // cambiato la stddev fatta con il for con questa fatta con accumulate
  float sigma = std::accumulate(
      vector.begin(), vector.end(), 0.f,
      [mu](float acc, float a) { return acc + powf(a - mu, 2); });
  return sqrt(sigma / vector.size());
}

// BISOGNA RIFARE TUTTI I TEST
/*
TEST_CASE("velocità") {
  SUBCASE("separazione") {
    array2 v1 = {2, 3};
    std::vector<array2> m1 = {{4, 3}, {7, 2}, {5, 4}};
    array2 arr1 = {10, 0};
    CHECK(separazione(1, v1, m1)[0] - arr1[0] < 0.00001);
    CHECK(separazione(1, v1, m1)[1] - arr1[1] < 0.00001);
    CHECK(separazione(0, v1, m1) == array2{0, 0});
  }
  SUBCASE("allineamento") {
    array2 v1 = {1, 4};
    std::vector<array2> m1 = {{3, 2}, {6, 7}, {8, 1}};
    array2 x = {-2.33333, 0.333333};
    CHECK(allineamento(0.5, v1, m1)[0] - x[0] < 0.00001);
    CHECK(allineamento(0.5, v1, m1)[1] - x[1] < 0.00001);
  }
  SUBCASE("coesione") {
    std::vector<array2> m1 = {{1., 4.}, {3., 2.}, {6., 7.}, {8., 1.}};
    array2 x = {4.66666667, 2.333333}; // calcolarli i nuovi; forse sono uguali
    CHECK(coesione(0, 1, m1)[0] - x[0] < 0.00001);
    CHECK(coesione(0, 1, m1)[1] - x[1] < 0.00001);
  }
}*/