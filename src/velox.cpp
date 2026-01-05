#include "velox.hpp"
#include <iostream>

const sf::Vector2f veloxBoid(const int k, const float d_s, const float d,
                             const float s, const float a, const float c,
                             std::vector<sf::Vector2f> &posBoids,
                             std::vector<sf::Vector2f> &vBoids,
                             std::array<sf::Vector2f, 4> &posObstacle) {
  if (d < 0.0f || d > 250.f) {
    throw std::runtime_error(
        "Errore: il parametro d dev'essere maggiore o uguale a 0 e minore o "
        "uguale a 250");
  }
  if (d_s >= d || d_s < 0.0f) {
    throw std::runtime_error(
        "Errore: il parametro d_s dev'essere minore di d e maggiore a 0");
  }

  sf::Vector2f vel = {};
  // verifica degli oggetti vicini
  const std::vector<float> distances = vecModDistance(k, posBoids);
  std::vector<sf::Vector2f> nearBoids = isLessThan(distances, d, k, posBoids);
  std::vector<sf::Vector2f> nearVelocity = isLessThan(distances, d, k, vBoids);
  const std::vector<float> obsDistances =
      vecModDistance(posBoids[k], posObstacle);
  std::vector<sf::Vector2f> nearObs =
      isLessThan(obsDistances, d_s, -1, posObstacle);
  // se il boid non ha nè ostacoli nè altri boids vicini la velocità finale sarà
  // nulla
  if (nearBoids.empty() && nearObs.empty()) {
    return {vBoids[k].x, vBoids[k].y};
  }

  const sf::Vector2f sep = separation(d_s, s, nearBoids, posBoids[k]);
  const sf::Vector2f all = alline(a, nearVelocity, vBoids[k]);
  const sf::Vector2f coe = cohesion(c, nearBoids, posBoids[k]);
  const sf::Vector2f sepObs = separation(d_s, s, nearObs, posBoids[k]);
  // computo la velocità del boid k come somma vettoriale delle 5 componenti
  vel = {vBoids[k].x + sep.x + all.x + coe.x + sepObs.x,
         vBoids[k].y + sep.y + all.y + coe.y + sepObs.y};

  return vel;
}

const sf::Vector2f separation(float const d_s, const float s,
                              const std::vector<sf::Vector2f> &nearPosBoids,
                              const sf::Vector2f &posBoid_k) {
  if (s < 0) {
    throw std::runtime_error(
        "Errore: il parametro s dev'essere maggiore o uguale a 0");
  }
  if (nearPosBoids.empty())
    return {0.f, 0.f};

  // creo un vettore con la somma delle posizioni dei boids con distanza minore
  // di d_s
  sf::Vector2f vSeparation = {0.0f, 0.0f};
  const std::vector<float> distances = vecModDistance(posBoid_k, nearPosBoids);
  for (long unsigned int i = 0; i < distances.size(); i++) {
    if (distances[i] < d_s) {
      vSeparation.x += (nearPosBoids[i].x - posBoid_k.x);
      vSeparation.y += (nearPosBoids[i].y - posBoid_k.y);
    }
  }
  vSeparation = {-s * vSeparation.x, -s * vSeparation.y};
  return vSeparation;
}

const sf::Vector2f alline(const float a, std::vector<sf::Vector2f> &vBoids,
                          const sf::Vector2f &vBoid_k) {
  if (a < 0 || a > 1) {
    throw std::runtime_error("Errore: il parametro a dev'essere maggiore o "
                             "uguale a 0 e minore a 1");
  }
  // calcola la media delle velocità dei boids
  sf::Vector2f meanVel =
      std::accumulate(vBoids.begin(), vBoids.end(), sf::Vector2f{0.f, 0.f},
                      [](sf::Vector2f acc, sf::Vector2f &vBoids) {
                        return sf::Vector2f{acc.x + vBoids.x, acc.y + vBoids.y};
                      });

  sf::Vector2f vAllineamento = {a * ((meanVel.x / vBoids.size()) - vBoid_k.x),
                                a * ((meanVel.y / vBoids.size()) - vBoid_k.y)};
  return vAllineamento;
}

const sf::Vector2f cohesion(const float c,
                            std::vector<sf::Vector2f> &nearPosBoids,
                            const sf::Vector2f &posBoid_k) {
  if (c < 0) {
    throw std::runtime_error(
        "Errore: il parametro c dev'essere maggiore o uguale a 0 ");
  }
  sf::Vector2f CM = std::accumulate(
      nearPosBoids.begin(), nearPosBoids.end(), sf::Vector2f{0.f, 0.f},
      [](sf::Vector2f acc, sf::Vector2f &nearBoids) {
        return sf::Vector2f{acc.x + nearBoids.x, acc.y + nearBoids.y};
      });
  CM = {c * ((CM.x / nearPosBoids.size()) - posBoid_k.x),
        c * ((CM.y / nearPosBoids.size()) - posBoid_k.y)};
  return CM;
}

////////////////////////////////////////////////////////////////////////

const std::vector<float>
vecModDistance(const int k, std::vector<sf::Vector2f> const &posBoids) {
  std::vector<float> vecModDistance;
  std::vector<sf::Vector2f> v;
  for (auto &j : posBoids) {
    v.push_back({j.x - posBoids[k].x, j.y - posBoids[k].y});
  }
  for (long unsigned int i = 0; i < v.size(); i++) {
    float distance = std::hypot(v[i].x, v[i].y);
    vecModDistance.push_back(distance);
  }

  return vecModDistance;
}

const std::string
stringMeanDistance(std::vector<sf::Vector2f> const &positionBoids) {
  std::vector<float> rowMean;
  std::vector<float> standardDev;
  for (size_t j = 0; j < positionBoids.size(); j++) {
    const std::vector<float> distances = vecModDistance(j, positionBoids);

    rowMean.push_back(calculateMean(distances, distances.size() - 1));
    for (size_t i = j; i < positionBoids.size(); i++) {
      if (distances[i] != 0.f) {
        standardDev.push_back(distances[i]);
      }
    }
  }
  const float mean = calculateMean(rowMean, rowMean.size());
  std::string result =
      std::to_string(std::llroundf(mean)) + " +/- " +
      std::to_string(std::llroundf(calculateStdDeviation(standardDev)));
  return result;
}

const std::vector<float>
vecModVelox(std::vector<sf::Vector2f> const &velocityVector) {
  std::vector<float> VEC;

  for (auto &j : velocityVector) {
    VEC.push_back(std::hypot(j.x, j.y));
  }
  return VEC;
}
const std::string
stringMeanVelox(std::vector<sf::Vector2f> const &velocityVecFlock) {
  const std::vector<float> vecModuli = vecModVelox(velocityVecFlock);
  const std::string result =
      std::to_string(
          std::llroundf(calculateMean(vecModuli, vecModuli.size()))) +
      " +/- " + std::to_string(std::llroundf(calculateStdDeviation(vecModuli)));
  return result;
}

const float calculateMean(std::vector<float> const &vector, const int size) {
  float mean = std::accumulate(vector.begin(), vector.end(), 0.0f);
  return mean / (size);
}

const float calculateStdDeviation(std::vector<float> const &vector) {
  const float mu = calculateMean(vector, vector.size());
  float sigma = std::accumulate(
      vector.begin(), vector.end(), 0.f,
      [&mu](float acc, float a) { return acc + powf(a - mu, 2); });
  return sqrt(sigma / vector.size());
}