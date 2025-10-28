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
array2 veloxBoid(float k, float d_s, float d, float s, float a, float c,
                 array2 &vBoid_1, std::vector<array2> &posBoids,
                 std::vector<array2> &vBoids) {

  std::vector<float> vecModDistanze = {};
  for (long unsigned int i = 0; i < posBoids.size(); i++) {
    if (i = k) {
      continue;
    }
    vecModDistanze.push_back(sqrt(powf(vecDistance(k, posBoids)[i][0], 2) +
                                  powf(vecDistance(k, posBoids)[i][1], 2)));
  }
  std::vector<array2> nearBoids = {{}};
  std::vector<array2> nearVel = {{}};
  for (auto i : vecModDistanze) {
    if (i = k) // non sono sicuro sia giustissimo
    {
      continue;
    }
    if (vecModDistanze[i] < d) {
      nearBoids.push_back(posBoids[i]);
      nearVel.push_back(vBoids[i]);
    }
  }
  array2 velox = {vBoid_1[0] + separazione(d_s, s, nearBoids, posBoids[k])[0] +
                      allineamento(a, nearVel, vBoids[k])[0] +
                      coesione(c, nearBoids, posBoids[k])[0],
                  vBoid_1[1] + separazione(d_s, s, nearBoids, posBoids[k])[1] +
                      allineamento(a, nearVel, vBoids[k])[1] +
                      coesione(c, nearBoids, posBoids[k])[1]};

  /*             if (std::find_if(it, vecModDistanze.end(),
    std::less<float>{}(d, *it)) != vecModDistanze.end()) {}*/
  return velox;
}

array2 separazione(float d_s, float s, std::vector<array2> &nearBoids,
                   array2 &posBoid_1) {
  if (s < 0) {
    throw std::runtime_error(
        "Errore: il parametro s dev'essere maggiore o uguale di 0");
  }
  float vecdist = 0;
  array2 vSeparation = {0, 0};
  for (long unsigned int j = 0; j < nearBoids.size(); j++) {

    vecdist = sqrt(powf(vecDistance(nearBoids, posBoid_1)[j][0], 2) +
                   powf(vecDistance(nearBoids, posBoid_1)[j][1], 2));
    if (fabs(vecdist) > d_s) {
      continue;
    }
    vSeparation[0] += nearBoids[j][0];
    vSeparation[1] += nearBoids[j][1];
  }
  vSeparation[0] = -s * vSeparation[0];
  vSeparation[1] = -s * vSeparation[1];

  return vSeparation;
}

array2 allineamento(float a, std::vector<array2> &nearVel, array2 &vBoid_1) {
  if (a < 0 || a > 1) {
    throw std::runtime_error("Errore: il parametro a dev'essere maggiore o "
                             "uguale di 0 e minore di 1");
  }
  array2 meanVel = {0, 0};
  for (long unsigned int i = 0; i < nearVel.size(); i++) {

    meanVel[0] += nearVel[i][0];
    meanVel[1] += nearVel[i][1];
  }
  meanVel = {meanVel[0] / nearVel.size(), meanVel[1] / nearVel.size()};
  array2 vAllineamento = {0, 0};

  vAllineamento[0] = a * (meanVel[0] - vBoid_1[0]) / (nearVel.size());
  vAllineamento[1] = a * (meanVel[1] - vBoid_1[1]) / (nearVel.size());
  return vAllineamento;
}

array2 coesione(float c, std::vector<array2> &nearBoids, array2 &posBoid_1) {
  array2 CM;
  for (long unsigned int j = 0; j < nearBoids.size(); j++) {

    CM[0] += nearBoids[j][0];
    CM[1] += nearBoids[j][1];
  }
  CM = {CM[0] / nearBoids.size(), CM[1] / nearBoids.size()};
  array2 vCoesione = {c * (CM[0] - posBoid_1[0]), c * (CM[1] - posBoid_1[1])};
  return vCoesione;
}

////////////////////////////////////////////////////////////////////////
std::vector<array2> vecDistance(int k, std::vector<array2> &posBoids) {
  for (long unsigned int j = 0; j < posBoids.size(); j++) {
    if (k == j) {
      continue;
    }

    posBoids[j][0] = posBoids[k][0] - posBoids[j][0];
    posBoids[j][1] = posBoids[k][1] - posBoids[j][1];
  }
  return posBoids;
}

std::vector<array2> vecDistance(std::vector<array2> &nearBoids,
                                array2 &posBoid_1) {
  for (long unsigned int j = 0; j < nearBoids.size(); j++) {

    nearBoids[j][0] = posBoid_1[0] - nearBoids[j][0];
    nearBoids[j][1] = posBoid_1[1] - nearBoids[j][1];
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
