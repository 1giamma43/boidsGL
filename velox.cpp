#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "velox.hpp"
#include "doctest.h"
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
template <typename T>
// i boids sono vicini?
// forse per ridurre la memoria utilizzata
// al posto di double meglio usare float
array2 veloxBoid(T d, T s, T a, T c, array2 &posBoid,
                array2 &vBoid, std::vector<array2> &posAltri,
                std::vector<array2> &vAltri) {
  std::vector<array2> vecDistanze;
  std::vector<double> vModDistanze;
  for (size_t i = 0; i < posAltri.size(); i++) {
    vecDistanze[i][0] =
        posBoid[0] -
        posAltri[i][0]; // forse non andrà perchè il vector è stato creato vuoto
                        // e per riempirlo si usa push_back
    vecDistanze[i][1] = posBoid[1] - posAltri[i][1];
    vModDistanze.push_back(
        sqrt(powf(vecDistanze[i][0], 2) + powf(vecDistanze[i][1], 2)));
  }
  auto it = vModDistanze.begin();

  if (std::find_if(it, vModDistanze.end(), std::less<double>{}(d, *it)) !=
      vModDistanze.end()) {
    array2 velox;
    velox[0] = vBoid[0] + separazione(s, posBoid, posAltri)[0] +
               allineamento(a, vBoid, vAltri)[0] +
               coesione(c, posBoid, posAltri)[0];
    velox[1] = vBoid[1] + separazione(s, posBoid, posAltri)[1] +
               allineamento(a, vBoid, vAltri)[1] +
               coesione(c, posBoid, posAltri)[1];
               return velox;
  };
  return {1,1};
}
template <typename T>
array2 separazione(T s, array2 posBoid, std::vector<array2> posAltri) {
  if (s < 0) {
    throw std::runtime_error(
        "Errore: il parametro s dev'essere maggiore o uguale di 0");
  }
  
  for (long unsigned int j = 0; j < posAltri.size(); j++) {

    posAltri[j][0] = posBoid[0] - posAltri[j][0];
    posAltri[j][1] = posBoid[1] - posAltri[j][1];
  }
  array2 vSeparazione = {0, 0};

  for (long unsigned int i = 0; i < posAltri.size(); i++) {
    vSeparazione[0] += posAltri[i][0];
    vSeparazione[1] += posAltri[i][1];
  }
  vSeparazione[0] = -s * vSeparazione[0];
  vSeparazione[1] = -s * vSeparazione[1];

  return vSeparazione; 
}
template <typename T>
array2 allineamento(T a, array2 vBoid1, std::vector<array2> vAltri1) {
  if (a < 0 || a > 1) {
    throw std::runtime_error("Errore: il parametro a dev'essere maggiore o "
                             "uguale di 0 e minore di 1");
  }

  for (long unsigned int j = 0; j < vAltri1.size(); j++) {

    vAltri1[j][0] = vBoid1[0] - vAltri1[j][0];
    vAltri1[j][1] = vBoid1[1] - vAltri1[j][1];
  }

  array2 vAllineamento = {0, 0};

  for (long unsigned int i = 0; i < vAltri1.size(); i++) {
    vAllineamento[0] += vAltri1[i][0];
    vAllineamento[1] += vAltri1[i][1];
  }
  vAllineamento[0] = (a * vAllineamento[0]) / vAltri1.size();
  vAllineamento[1] = (a * vAllineamento[1]) / vAltri1.size();
  return vAllineamento;
}
template <typename T>
array2 coesione(T c, array2 posBoid, std::vector<array2> posAltri) {
  array2 CM;
  for (long unsigned int i = 0; i < posAltri.size(); i++) {
    CM[0] = posAltri[i][0] + CM[0];
    CM[1] = posAltri[i][1] + CM[1];
  }
  array2 vCoesione = {0.0, 0.0};
  vCoesione[0] = c * ((CM[0] / posAltri.size()) - posBoid[0]);
  vCoesione[1] = c * ((CM[1] / posAltri.size()) - posBoid[1]);
  return vCoesione;
}



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
    array2 v1 = {1., 4.};
    std::vector<array2> m1 = {{3., 2.}, {6., 7.}, {8., 1.}};
    array2 x = {4.66666667, 2.333333};
    CHECK(coesione(1, v1, m1)[0] - x[0] < 0.00001);
    CHECK(coesione(1, v1, m1)[1] - x[1] < 0.00001);
  }
}
