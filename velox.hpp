#ifndef VELOX_HPP
#define VELOX_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <vector>

std::vector<sf::Vector2f> vecDistance(int k,
                                      std::vector<sf::Vector2f> &posBoids);
std::vector<sf::Vector2f> vecDistance(std::vector<sf::Vector2f> &nearBoids,
                                      sf::Vector2f &posBoid_1);
////////////////////////////////////////////////////

sf::Vector2f separazione(float d_s, float s,
                         std::vector<sf::Vector2f> &nearBoids,
                         sf::Vector2f &posBoid_1);
sf::Vector2f allineamento(float a, std::vector<sf::Vector2f> &vBoids,
                          sf::Vector2f &vBoid_1);
sf::Vector2f coesione(float c, std::vector<sf::Vector2f> &nearBoids,
                      sf::Vector2f &posBoid_1);
sf::Vector2f veloxBoid(int k, float d_s, float d, float s, float a, float c,
                       std::vector<sf::Vector2f> &posBoids,
                       std::vector<sf::Vector2f> &vBoids);

#endif