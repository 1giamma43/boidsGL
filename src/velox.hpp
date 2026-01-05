#ifndef VELOX_HPP
#define VELOX_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <array>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>

const std::vector<float>
vecModDistance(const int k, std::vector<sf::Vector2f> const &posBoids);
const std::vector<float>
vecModVelox(std::vector<sf::Vector2f> const &velocityVector);
const float calculateMean(std::vector<float> const &vector, const int size);
const float calculateStdDeviation(std::vector<float> const &vector);
const std::string
stringMeanDistance(std::vector<sf::Vector2f> const &positionBoids);
const std::string
stringMeanVelox(std::vector<sf::Vector2f> const &velocityVecFlock);
////////////////////////////////////////////////////

const sf::Vector2f separation(const float d_s, const float s,
                              const std::vector<sf::Vector2f> &nearPosBoids,
                              const sf::Vector2f &posBoid_k);
const sf::Vector2f alline(const float a, std::vector<sf::Vector2f> &vBoids,
                          const sf::Vector2f &vBoid_k);
const sf::Vector2f cohesion(const float c,
                            std::vector<sf::Vector2f> &nearPosBoids,
                            const sf::Vector2f &posBoid_k);
const sf::Vector2f veloxBoid(const int k, const float d_s, const float d,
                             const float s, const float a, const float c,
                             std::vector<sf::Vector2f> &posBoids,
                             std::vector<sf::Vector2f> &vBoids,
                             std::array<sf::Vector2f, 4> &posObstacle);

template <typename T>
inline const std::vector<float> vecModDistance(sf::Vector2f const &posBoid_k,
                                               T const &posBoids) {
  std::vector<float> vecModDistanze;
  std::vector<sf::Vector2f> v;
  for (auto &b : posBoids) {
    v.push_back({b.x - posBoid_k.x, b.y - posBoid_k.y});
  }
  for (auto &i : v) {
    float distance = hypot(i.x, i.y);
    vecModDistanze.push_back(distance);
  }

  return vecModDistanze;
}
template <typename T>
inline std::vector<sf::Vector2f> isLessThan(const std::vector<float> distances,
                                            float par, int k, T &v) {
  std::vector<sf::Vector2f> vector;
  if (k == -1) {
    for (long unsigned int i = 0; i < distances.size(); i++) {
      if (distances[i] < par) {
        vector.push_back(v[i]);
      }
    }
  } else {
    for (long unsigned int i = 0; i < distances.size(); i++) {
      if (distances[i] < par && i != k) {
        vector.push_back(v[i]);
      }
    }
  }
  return vector;
}
#endif