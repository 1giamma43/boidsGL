#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "velox.hpp"

TEST_CASE("testing velocity functions") {
  SUBCASE("calculateMean") {
    std::vector<float> test = {0.0f, 49.5f, 37.0f, 12.0f, 7.0f, 23.2f};
    CHECK(calculateMean(test) - 21.45 < 0.0001);
    test = {0.8f, 49.5f, 31.6f, 19.0f, 3.4f, 25.1f};
    CHECK(calculateMean(test)-21.566<0.001);
  }
  SUBCASE("vecDistance"){
    std::vector<sf::Vector2f> test={{305.9f,23.2f},{934.1f,479.7f},{45.5f,589.3f}};
    sf::Vector2f test2={864.8f,18.f};
    std::vector<sf::Vector2f> result = {{-558.9f,5.2f},{69.3f,461.7f},{-819.3,571.3}};
    CHECK(vecDistance(test,test2).size()==result.size());
    for (size_t i = 0; i < result.size(); i++) {
      CHECK(vecDistance(test,test2)[i].x - result[i].x < 0.001);
      CHECK(vecDistance(test,test2)[i].y - result[i].y < 0.001);
    }
  }
}