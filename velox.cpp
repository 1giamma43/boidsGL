#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "velox.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "doctest.h"
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

//  riguardare e cercare di capire come cambiare i vari for in algoritmi
//  io credo che i vector qui potrebbero essere cambiati in array perchè tanto
//  all'interno della funzione non cambiano size però non so se ha senso e se si
//  può fare
sf::Vector2f veloxBoid(float k, float d_s, float d, float s, float a, float c,
                       std::vector<sf::Vector2f> &posBoids,
                       std::vector<sf::Vector2f> &vBoids) {

  std::vector<float> vecModDistanze = {};
  for (long unsigned int i = 0; i < posBoids.size(); i++) {
    if (i = k) {
      continue;
    }
    vecModDistanze.push_back(sqrt(powf(vecDistance(k, posBoids)[i].x, 2) +
                                  powf(vecDistance(k, posBoids)[i].y, 2)));
  }
  std::vector<sf::Vector2f> nearBoids = {{}};
  std::vector<sf::Vector2f> nearVel = {{}};

  for (long unsigned int i = 0; i < posBoids.size(); i++) {

    if (vecModDistanze[i] < d) {
      nearBoids.push_back(posBoids[i]);
      nearVel.push_back(vBoids[i]);
    }
  }
  sf::Vector2f velox = {
      vBoids[k].x + separazione(d_s, s, nearBoids, posBoids[k]).x +
          allineamento(a, nearVel, vBoids[k]).x +
          coesione(c, nearBoids, posBoids[k]).x,
      vBoids[k].y + separazione(d_s, s, nearBoids, posBoids[k]).y +
          allineamento(a, nearVel, vBoids[k]).y +
          coesione(c, nearBoids, posBoids[k]).y};
  return velox;
}

sf::Vector2f separazione(float d_s, float s,
                         std::vector<sf::Vector2f> &nearBoids,
                         sf::Vector2f &posBoid_1) {
  if (s < 0) {
    throw std::runtime_error(
        "Errore: il parametro s dev'essere maggiore o uguale di 0");
  }
  float vecdist = 0;
  sf::Vector2f vSeparation = {0, 0};

  for (auto j : nearBoids) {
    int i;
    vecdist = sqrt(powf(vecDistance(nearBoids, posBoid_1)[i].x, 2) +
                   powf(vecDistance(nearBoids, posBoid_1)[i].y, 2));
    if (fabs(vecdist) > d_s) {
      continue;
    }
    vSeparation.x += j.x;
    vSeparation.y += j.y;
    i++;
  }
  vSeparation.x = -s * vSeparation.x;
  vSeparation.y = -s * vSeparation.y;

  return vSeparation;
}

sf::Vector2f allineamento(float a, std::vector<sf::Vector2f> &nearVel,
                          sf::Vector2f &vBoid_1) {
  if (a < 0 || a > 1) {
    throw std::runtime_error("Errore: il parametro a dev'essere maggiore o "
                             "uguale di 0 e minore di 1");
  }
  sf::Vector2f meanVel = {0, 0};
  for (auto j : nearVel) {

    meanVel.x += j.y;
    meanVel.y += j.y;
  }
  meanVel = {meanVel.x / nearVel.size(), meanVel.y / nearVel.size()};
  sf::Vector2f vAllineamento = {0, 0};

  vAllineamento.x = a * (meanVel.x - vBoid_1.x) / (nearVel.size());
  vAllineamento.y = a * (meanVel.y - vBoid_1.y) / (nearVel.size());
  return vAllineamento;
}

sf::Vector2f coesione(float c, std::vector<sf::Vector2f> &nearBoids,
                      sf::Vector2f &posBoid_1) {
  sf::Vector2f CM;
  for (auto j : nearBoids) {

    CM.x += j.x;
    CM.y += j.y;
  }
  CM = {CM.x / nearBoids.size(), CM.y / nearBoids.size()};
  sf::Vector2f vCoesione = {c * (CM.x - posBoid_1.x), c * (CM.y - posBoid_1.y)};
  return vCoesione;
}

////////////////////////////////////////////////////////////////////////
std::vector<sf::Vector2f> vecDistance(int k,
                                      std::vector<sf::Vector2f> &posBoids) {
  for (auto j : posBoids) {

    j.x = posBoids[k].x - j.x;
    j.y = posBoids[k].y - j.y;
  }
  return posBoids;
}

std::vector<sf::Vector2f> vecDistance(std::vector<sf::Vector2f> &nearBoids,
                                      sf::Vector2f &posBoid_1) {
  for (auto j : nearBoids) {

    j.x = posBoid_1.x - j.x;
    j.y = posBoid_1.y - j.y;
  }
  return nearBoids;
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
