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

//using array2 = const sf::Vector2f;

class array2{
std::array<float,2> p;
public:
array2(const sf::Vector2f sdx){
  p[0]=sdx.x;
  p[1]=sdx.y;
}
};
//ho bisogno di capire come fare accettare alle funzioni l'input di tipo array2 anche se le funzioni accettano const sf::vector2f
std::vector<array2> vecDistance(int k,std::vector<array2> &posBoids);
std::vector<array2> vecDistance(std::vector<array2> &nearBoids, array2 &posBoid_1);
////////////////////////////////////////////////////

array2 separazione(float d_s,float s,std::vector<array2> &nearBoids, array2 &posBoid_1);
array2 allineamento(float a,  std::vector<array2> &vBoids, array2 &vBoid_1);
array2 coesione(float c, std::vector<array2> &nearBoids,array2 &posBoid_1);
array2 veloxBoid(float k,float d_s,float d, float s, float a, float c,
                 array2 &vBoid, std::vector<array2> &posBoids,
                 std::vector<array2> &vBoids);

#endif