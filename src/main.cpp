#include "options.hpp"
#include <iostream>

// COSE DA FARE:trovare s,a,c

int main() {

  sf::RenderWindow window(sf::VideoMode({1400, 600}),
                          "simulation of a flock of boids");
  window.setPosition({100, 100});
  window.setFramerateLimit(40);
  //////////////////////////////////////////////////////

  sf::Font font;
  sf::RectangleShape rectParam({400.f, 600.f});
  rectParam.setFillColor(sf::Color(0, 0, 0));
  rectParam.setPosition(1000.f, 0.f);

  sf::RectangleShape nBoidsRect({300.f, 40.f});
  sf::RectangleShape dRect({300.f, 40.f});
  sf::RectangleShape d_sRect({300.f, 40.f});
  sf::RectangleShape sRect({300.f, 40.f});
  sf::RectangleShape aRect({300.f, 40.f});
  sf::RectangleShape cRect({300.f, 40.f});
  sf::RectangleShape distanceRect({300.f, 40.f});
  sf::RectangleShape velocityRect({300.f, 40.f});

  sf::Text paramText1;
  sf::Text paramText2;
  sf::Text paramText3;
  sf::Text paramText4;
  sf::Text paramText5;
  sf::Text paramText6;
  sf::Text outputText1;
  sf::Text outputText2;

  sf::Text paramNumText1;
  sf::Text paramNumText2;
  sf::Text paramNumText3;
  sf::Text paramNumText4;
  sf::Text paramNumText5;
  sf::Text paramNumText6;
  sf::Text outputNumText1;
  sf::Text outputNumText2;

  std::string label1 = "Number of boids-------->";
  std::string label2 = "Modify parameter d----->";
  std::string label3 = "Modify parameter d_s--->";
  std::string label4 = "Modify parameter s----->";
  std::string label5 = "Modify parameter a----->";
  std::string label6 = "Modify parameter c----->";
  std::string OutLabel1 = "Mean distance x ------>";
  std::string OutLabel2 = "Mean velocity v ------>";
  std::string terminalText1 = "insert number of boids";
  std::string terminalText2 = "insert parameter d";
  std::string terminalText3 = "insert parameter d_s";
  std::string terminalText4 = "insert parameter s";
  std::string terminalText5 = "insert parameter a";
  std::string terminalText6 = "insert parameter c";

  const float positionRect1 = 0.f;
  const float positionRect2 = 50.f;
  const float positionRect3 = 100.f;
  const float positionRect4 = 150.f;
  const float positionRect5 = 200.f;
  const float positionRect6 = 250.f;
  const float positionRect7 = 500.f;
  const float positionRect8 = 550.f;

  int numBoids = 80;
  float dPar = 150.f;
  float d_sPar = 25.f;
  float sPar = 0.18f;
  float aPar = 0.5f;
  float cPar = 0.18f;
  float meanDistance = 0.f;
  float meanVelocity = 0.f;

  setParameters(window, nBoidsRect, paramText1, paramNumText1, font,
                positionRect1, label1, numBoids);
  setParameters(window, dRect, paramText2, paramNumText2, font, positionRect2,
                label2, dPar);
  setParameters(window, d_sRect, paramText3, paramNumText3, font, positionRect3,
                label3, d_sPar);
  setParameters(window, sRect, paramText4, paramNumText4, font, positionRect4,
                label4, sPar);
  setParameters(window, aRect, paramText5, paramNumText5, font, positionRect5,
                label5, aPar);
  setParameters(window, cRect, paramText6, paramNumText6, font, positionRect6,
                label6, cPar);
  setParameters(window, distanceRect, outputText1, outputNumText1, font,
                positionRect7, OutLabel1, meanDistance);
  setParameters(window, velocityRect, outputText2, outputNumText2, font,
                positionRect8, OutLabel2, meanVelocity);

  const sf::Vector2f P1{35.f, 50.f};
  const sf::Vector2f P2{400.f, 250.f};
  const sf::Vector2f P3{325.f, 490.f};
  const sf::Vector2f P4{830.f, 170.f};

  obs::obstacle O1, O2, O3, O4;

  O1.position_ = P1;
  O2.position_ = P2;
  O3.position_ = P3;
  O4.position_ = P4;
  std::array<sf::Vector2f, 4> posObstacle = {P1, P2, P3, P4};

  fl::flock flo(numBoids);
  flo.set_FlockSize(numBoids);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      numBoids = changeParameters<int>(event, window, nBoidsRect, numBoids,
                                       paramNumText1, terminalText1);

      d_sPar = changeParameters<float>(event, window, d_sRect, d_sPar,
                                       paramNumText3, terminalText3);
      dPar = changeParameters<float>(event, window, dRect, dPar, paramNumText2,
                                     terminalText2);
      sPar = changeParameters<float>(event, window, sRect, sPar, paramNumText4,
                                     terminalText4);
      aPar = changeParameters<float>(event, window, aRect, aPar, paramNumText5,
                                     terminalText5);
      cPar = changeParameters<float>(event, window, cRect, cPar, paramNumText6,
                                     terminalText6);
    }
    if (numBoids != flo.size()) {
      flo.set_FlockSize(numBoids);
    }
    std::vector<sf::Vector2f> posFlock = flo.getPositionFlock();
    std::vector<sf::Vector2f> velocityVecFlock = flo.getVelocityFlock();
    flo.moveFlock(d_sPar, dPar, sPar, aPar, cPar, posFlock, velocityVecFlock,
                  posObstacle);
    flo.collision();

    outputNumText1.setString(stringMeanDistance(posFlock));
    outputNumText2.setString(stringMeanVelox(velocityVecFlock));

    window.clear(sf::Color(0, 226, 208));
    window.draw(rectParam);
    draw(window, nBoidsRect, paramText1, paramNumText1);
    draw(window, dRect, paramText2, paramNumText2);
    draw(window, d_sRect, paramText3, paramNumText3);
    draw(window, sRect, paramText4, paramNumText4);
    draw(window, aRect, paramText5, paramNumText5);
    draw(window, cRect, paramText6, paramNumText6);
    draw(window, distanceRect, outputText1, outputNumText1);
    draw(window, velocityRect, outputText2, outputNumText2);
    draw_Obs(window, O1);
    draw_Obs(window, O2);
    draw_Obs(window, O3);
    draw_Obs(window, O4);
    flo.draw_Flock(window);
    window.display();
  }
  return 0;
}