#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "flock.hpp"

TEST_CASE("testing mathematicalfunctions") {
  SUBCASE("calculateMean") {
    std::vector<float> test = {0.0f, 49.5f, 37.0f, 12.0f, 7.0f, 23.2f};
    CHECK(calculateMean(test, test.size()) == doctest::Approx(21.45));
    std::vector<float> test2 = {0.8f, 49.5f, 31.6f, 19.0f, 3.4f, 25.1f, 0.f};
    CHECK(calculateMean(test2, test2.size()) == doctest::Approx(18.4857));
    std::vector<float> test3 = {0.8f, 49.5f, -31.6f, 19.0f, 3.4f, -25.1f, 0.f};
    CHECK(calculateMean(test3, test3.size()) == doctest::Approx(2.28571));
  }

  SUBCASE("vecModDistance") {
    std::vector<sf::Vector2f> test1 = {
        {132.4f, 576.2f}, {41.8f, 16.1f}, {500.f, 300.f}};
    std::vector<float> result = {0.f, 567.38f, 459.8f};
    CHECK(vecModDistance(0, test1).size() == result.size());
    for (size_t i = 0; i < result.size(); i++) {
      CHECK(vecModDistance(0, test1)[i] == doctest::Approx(result[i]));
    }
  }

  SUBCASE("vecModVelox") {
    std::vector<sf::Vector2f> test = {
        {302.f, 45.f}, {753.f, 812.f}, {8.f, 35.f}};
    std::vector<float> result = {305.334f, 1107.41f, 35.9026f};
    std::vector<sf::Vector2f> test1 = {
        {302.f, -45.f}, {-753.f, 812.f}, {8.f, -35.f}};
    CHECK(vecModVelox(test).size() == result.size());
    for (size_t i = 0; i < result.size(); i++) {
      CHECK(vecModVelox(test)[i] == doctest::Approx(result[i]));
      CHECK(vecModVelox(test1)[i] == doctest::Approx(result[i]));
    }
  }

  SUBCASE("calculateStdDeviation") {
    std::vector<float> test3 = {10.f, 12.f, 23.f, 23.f, 16.f, 29.f, 3.f};
    CHECK(calculateStdDeviation(test3) == doctest::Approx(8.32993f));
    test3 = {5.f, 5.f, 5.f, 5.f};
    CHECK(calculateStdDeviation(test3) == doctest::Approx(0.f));
  }

  SUBCASE("stringMeanDistance") {
    std::vector<sf::Vector2f> test4 = {
        {153.4f, 2.5f}, {876.2f, 358.f}, {500.3f, 300.4f}, {23.5f, 789.1f}};
    CHECK(stringMeanDistance(test4) == "680 +/- 202");
  }
}
TEST_CASE("Testing velocity functions") {
  SUBCASE("cohesion") {
    std::vector<sf::Vector2f> test = {
        {123.f, 10.f}, {646.f, 351.6f}, {967.4f, 30.f}};
    sf::Vector2f boid = {500.f, 300.f};
    sf::Vector2f result = {0.788f, -1.69467f};
    CHECK(cohesion(0.01f, test, boid).x == doctest::Approx(result.x));
    CHECK(cohesion(0.01f, test, boid).y == doctest::Approx(result.y));
    std::vector<sf::Vector2f> test2 = {
        {-2.f, -2.f}, {646.f, 351.6f}, {967.4f, 30.f}};
    sf::Vector2f boid2 = {500.f, 300.f};
    sf::Vector2f result2 = {0.371334f, -1.73467f};
    CHECK(cohesion(0.01f, test2, boid2).x == doctest::Approx(result2.x));
    CHECK(cohesion(0.01f, test2, boid2).y == doctest::Approx(result2.y));
  }

  SUBCASE("alline") {
    std::vector<sf::Vector2f> test = {
        {23.f, 29.f}, {1.8f, -45.f}, {-34.f, -6.76f}};
    sf::Vector2f vBoid = {43.f, 17.f};
    sf::Vector2f result = {-0.460667f, -0.245867f};
    CHECK(alline(0.01f, test, vBoid).x == doctest::Approx(result.x));
    CHECK(alline(0.01f, test, vBoid).y == doctest::Approx(result.y));

    std::vector<sf::Vector2f> test1 = {
        {23.f, 29.f}, {-1000.f, -1000.f}, {34.f, -6.76f}};
    sf::Vector2f vBoid1 = {43.f, 17.f};
    sf::Vector2f result1 = {-3.57333f, -3.4292f};
    CHECK(alline(0.01f, test1, vBoid1).x == doctest::Approx(result1.x));
    CHECK(alline(0.01f, test1, vBoid1).y == doctest::Approx(result1.y));

    std::vector<sf::Vector2f> test2 = {
        {23.f, 29.f}, {-48.f, -6.76f}, {-1000.f, -1000.f}};
    sf::Vector2f vBoid2 = {43.f, 17.f};
    sf::Vector2f result2 = {-3.84667f, -3.4292f};
    CHECK(alline(0.01f, test2, vBoid2).x == doctest::Approx(result2.x));
    CHECK(alline(0.01f, test2, vBoid2).y == doctest::Approx(result2.y));

    std::vector<sf::Vector2f> test3 = {
        {23.f, 29.f}, {23.f, 29.f}, {23.f, 29.f}};
    sf::Vector2f vBoid3 = {23.f, 29.f};
    sf::Vector2f result3 = {0.f, 0.f};
    CHECK(alline(0.01f, test3, vBoid3).x == doctest::Approx(result3.x));
    CHECK(alline(0.01f, test3, vBoid3).y == doctest::Approx(result3.y));
  }

  SUBCASE("separation") {
    std::vector<sf::Vector2f> test = {
        {232.f, 2.f}, {673.f, 445.f}, {304.f, 560.76f}};
    sf::Vector2f boid = test[0];
    sf::Vector2f result = {0.000f, 0.000f};
    CHECK(separation(50.f, 0.5f, test, boid).x == doctest::Approx(result.x));
    CHECK(separation(50.f, 0.5f, test, boid).y == doctest::Approx(result.y));

    std::vector<sf::Vector2f> test1 = {
        {242.f, 10.f}, {260.f, 20.f}, {274.f, 28.f}};
    sf::Vector2f boid1 = test1[1];
    sf::Vector2f result1 = {2.f, 1.f};
    CHECK(separation(30.f, 0.5f, test1, boid1).x == doctest::Approx(result1.x));
    CHECK(separation(30.f, 0.5f, test1, boid1).y == doctest::Approx(result1.y));
  }

  SUBCASE("veloxBoid") {
    std::vector<sf::Vector2f> posTest = {
        {100.f, 100.f}, {110.f, 100.f}, {120.f, 125.f}};
    std::vector<sf::Vector2f> velTest = {
        {10.f, 10.f}, {5.f, -12.f}, {34.f, 22.f}};
    sf::Vector2f P1{0.f, 0.f};
    std::array<sf::Vector2f, 4> posObstacle{P1};
    sf::Vector2f RESULT = {5.035f, -11.9645f};
    CHECK(veloxBoid(1, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest, velTest,
                    posObstacle)
              .x == doctest::Approx(RESULT.x));
    CHECK(veloxBoid(1, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest, velTest,
                    posObstacle)
              .y == doctest::Approx(RESULT.y));

    std::vector<sf::Vector2f> posTest1 = {
        {100.f, 100.f}, {510.f, 100.f}, {10.f, 425.f}};
    std::vector<sf::Vector2f> velTest1 = {
        {10.f, 10.f}, {5.f, -12.f}, {34.f, 22.f}};
    sf::Vector2f RESULT1 = {5.f, -12.f};
    CHECK(veloxBoid(1, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest1,
                    velTest1, posObstacle)
              .x == doctest::Approx(RESULT1.x));
    CHECK(veloxBoid(1, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest1,
                    velTest1, posObstacle)
              .y == doctest::Approx(RESULT1.y));

    std::vector<sf::Vector2f> posTest2 = {{100.f, 100.f}};
    std::vector<sf::Vector2f> velTest2 = {{10.f, 10.f}};
    sf::Vector2f RESULT2 = {10.f, 10.f};
    CHECK(veloxBoid(0, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest2,
                    velTest2, posObstacle)
              .x == doctest::Approx(RESULT2.x));
    CHECK(veloxBoid(0, 15.f, 100.f, 0.0018f, 0.0010f, 0.0006f, posTest2,
                    velTest2, posObstacle)
              .y == doctest::Approx(RESULT2.y));
  }
}
TEST_CASE("flock") {
  SUBCASE("constructor") {
    flock f(10);
    CHECK(f.getPositionFlock().size() == 10);
  }
  SUBCASE("setFlockSize") {
    flock f(5);
    f.setFlockSize(15);
    CHECK(f.size() == 15);
    f.setFlockSize(7);
    CHECK(f.size() == 7);
  }
  SUBCASE("getPositionFlock") {
    flock f(12);
    CHECK(f.getPositionFlock().size() == 12);
  }
  SUBCASE("collision") {
    flock f(1);
    auto pos = f.getPositionFlock();
    pos[0] = {1005.f, 610.f};
    f.collision();
    auto newPos = f.getPositionFlock();
    CHECK(newPos[0].x < 1000.f);
    CHECK(newPos[0].y < 600.f);
  }
  SUBCASE("moveFlock") {
    flock f(3);
    auto pos = f.getPositionFlock();
    auto prev = pos;
    std::array<sf::Vector2f, 4> obs = {};
    auto vel = f.getVelocityFlock();
    f.moveFlock(15.f, 100.f, 0.1f, 0.01f, 0.01f, pos, vel, obs);
    auto newPos = f.getPositionFlock();
    CHECK(newPos.size() == pos.size());
  }
}
