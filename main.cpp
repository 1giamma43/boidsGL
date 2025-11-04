// #include "flock.hpp"
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

int main() {

  sf::RenderWindow window(sf::VideoMode({1200, 600}),
                          "simulation of a flock of boids");
  window.setPosition({300, 200});
  window.setFramerateLimit(40);

  //////////////////////////////////////////////////////
  sf::Font font;
  font.loadFromFile("roboto/Roboto-Light.ttf");
  ///////////////////////////////////////////////////

  sf::RectangleShape sfondo({400.f, 600.f});
  sfondo.setFillColor(sf::Color(0, 0, 0));
  sfondo.setPosition(800.f, 0.f);

  sf::RectangleShape modNBoids({300.f, 40.f});
  modNBoids.setFillColor(sf::Color(250, 200, 150));
  modNBoids.setPosition(850.f, 0.f);
  sf::Text usersText;
  usersText.setFont(font);
  usersText.setString("Modify number of boids--->");
  usersText.setPosition(860.f, 10.f);
  usersText.setCharacterSize(17);
  usersText.setFillColor(sf::Color::Black);
  sf::Text usersNumText;
  usersNumText.setFont(font);
  int numBoids = 0;
  usersNumText.setPosition(1080.f, 10.f);
  usersNumText.setCharacterSize(17);
  usersNumText.setFillColor(sf::Color::Black);

  sf::RectangleShape dParam({300.f, 40.f});
  dParam.setFillColor(sf::Color(250, 200, 150));
  dParam.setPosition(850.f, 50.f);
  sf::Text usersText2;
  usersText2.setFont(font);
  usersText2.setString("Modify parameter d------>");
  usersText2.setPosition(860.f, 60.f);
  usersText2.setCharacterSize(17);
  usersText2.setFillColor(sf::Color::Black);
  sf::Text usersNumText2;
  usersNumText2.setFont(font);
  float dPar = 0.f;
  usersNumText2.setPosition(1080.f, 60.f);
  usersNumText2.setCharacterSize(17);
  usersNumText2.setFillColor(sf::Color::Black);

  sf::RectangleShape d_sParam({300.f, 40.f});
  d_sParam.setFillColor(sf::Color(250, 200, 150));
  d_sParam.setPosition(850.f, 100.f);
  sf::Text usersText3;
  usersText3.setFont(font);
  usersText3.setString("Modify parameter d_s---->");
  usersText3.setPosition(860.f, 110.f);
  usersText3.setCharacterSize(17);
  usersText3.setFillColor(sf::Color::Black);
  sf::Text usersNumText3;
  usersNumText3.setFont(font);
  float d_sPar = 0.f;
  usersNumText3.setPosition(1080.f, 110.f);
  usersNumText3.setCharacterSize(17);
  usersNumText3.setFillColor(sf::Color::Black);

   sf::RectangleShape sParam({300.f, 40.f});
  sParam.setFillColor(sf::Color(250, 200, 150));
  sParam.setPosition(850.f, 150.f);
  sf::Text usersText4;
  usersText4.setFont(font);
  usersText4.setString("Modify parameter s------>");
  usersText4.setPosition(860.f, 160.f);
  usersText4.setCharacterSize(17);
  usersText4.setFillColor(sf::Color::Black);
  sf::Text usersNumText4;
  usersNumText4.setFont(font);
  float sPar = 0.f;
  usersNumText4.setPosition(1080.f, 160.f);
  usersNumText4.setCharacterSize(17);
  usersNumText4.setFillColor(sf::Color::Black);

 sf::RectangleShape aParam({300.f, 40.f});
  aParam.setFillColor(sf::Color(250, 200, 150));
  aParam.setPosition(850.f, 200.f);
  sf::Text usersText5;
  usersText5.setFont(font);
  usersText5.setString("Modify parameter a------>");
  usersText5.setPosition(860.f, 210.f);
  usersText5.setCharacterSize(17);
  usersText5.setFillColor(sf::Color::Black);
  sf::Text usersNumText5;
  usersNumText5.setFont(font);
  float aPar = 0.f;
  usersNumText5.setPosition(1080.f, 210.f);
  usersNumText5.setCharacterSize(17);
  usersNumText5.setFillColor(sf::Color::Black);

  sf::RectangleShape cParam({300.f, 40.f});
  cParam.setFillColor(sf::Color(250, 200, 150));
  cParam.setPosition(850.f, 250.f);
  sf::Text usersText6;
  usersText6.setFont(font);
  usersText6.setString("Modify parameter c------>");
  usersText6.setPosition(860.f, 260.f);
  usersText6.setCharacterSize(17);
  usersText6.setFillColor(sf::Color::Black);
  sf::Text usersNumText6;
  usersNumText6.setFont(font);
  float cPar = 0.f;
  usersNumText6.setPosition(1080.f, 260.f);
  usersNumText6.setCharacterSize(17);
  usersNumText6.setFillColor(sf::Color::Black);
  
  while (window.isOpen()) {
    sf::Event event;
    int i = 0;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window.close();
      }
      //serve cambiare il getposition con la posizione rispetto alla finestra non allo schermo intero
      if (sf::Mouse::getPosition().x >= 850 &&
          sf::Mouse::getPosition().x <= 1150 &&
          sf::Mouse::getPosition().y >= 0 &&
          sf::Mouse::getPosition().y <= 40 &&
          event.type == sf::Mouse::isButtonPressed(sf::Mouse::Left) &&// sserve altro
          numBoids >= 0 && numBoids <= 30) {                        
        if (event.key.code == sf::Keyboard::Up) {
        numBoids += 1;
        usersNumText.setString(std::to_string(numBoids));
      }
      
      if (event.key.code == sf::Keyboard::Down && numBoids > 0) {
        numBoids -= 1;
        usersNumText.setString(std::to_string(numBoids));
      }
    }}

    /* flock stormo(numBoids);

     stormo.moveFlock(i , d_s, d, s, a,
                      c, flock::getvelocityBoids()); // bene ora bisogna fare in
     modo che ogni mezzo
                            // secondo calcoli la velocità



     // collisione con lati del window
     if (convex.getPosition().x > 800.f) {
       convex.setPosition(0.f, convex.getPosition().y);
     }
     if (convex.getPosition().y > 600.f) {
       convex.setPosition(convex.getPosition().x, 0.f);
     }
     if (convex.getPosition().y < 0.f) {
       convex.setPosition(convex.getPosition().x, 600.f);
     }
     if (convex.getPosition().x < 0.f) {
       convex.setPosition(800.f, convex.getPosition().y);
     }
 */

    i++;
    window.clear(sf::Color(0, 226, 238));
    window.draw(sfondo);
    window.draw(modNBoids);
    window.draw(usersText);
    window.draw(usersNumText);
    window.draw(dParam);
    window.draw(usersText2);
    window.draw(usersNumText2);
    window.draw(d_sParam);
    window.draw(usersText3);
    window.draw(usersNumText3);
     window.draw(sParam);
    window.draw(usersText4);
    window.draw(usersNumText4);
     window.draw(aParam);
    window.draw(usersText5);
    window.draw(usersNumText5);
      window.draw(cParam);
    window.draw(usersText6);
    window.draw(usersNumText6);
    window.display();
    
  }
  return 0;
}