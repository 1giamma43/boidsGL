#include <iostream>
#include "boid.cpp"

#include <string>
#include <numeric>
#include <vector>


int main() {

  sf::RenderWindow window(sf::VideoMode({800, 600}),
                          "simulation of a flock of boids");
  window.setFramerateLimit(40);
  sf::RenderWindow optionsWindow(sf::VideoMode({200,600}),"options window");
  

  sf::Font font;
  font.loadFromFile("roboto/Roboto-Light.ttf");
 ///////////////////////////////////////////////////

  sf::RectangleShape usersBars({200.f, 70.f});
  usersBars.setFillColor(sf::Color(100, 20, 180));

  sf::RectangleShape bohpar({8.f, 24.f});
  bohpar.setPosition(13.f, 10.f);
  bohpar.setFillColor(sf::Color(50, 30, 20));

  sf::RectangleShape nBoid({20.f, 12.f});
  nBoid.setPosition(13.f, 40.f);
  nBoid.setFillColor(sf::Color(5, 5, 5));
  nBoid.setOutlineColor(sf::Color(0, 0, 170));
  nBoid.setOutlineThickness(1.f);

  sf::ConvexShape convex(
      4); // biogna avere un qualcosa per selezionare quanti convex creare+
          // vorrei poterlo scegliere tramite un aggeggio nel window
  convex.setPoint(0, {0.f, 0.f});
  convex.setPoint(1, {60.f, 20.f});
  convex.setPoint(2, {40.f, 30.f});
  convex.setPoint(3, {30.f, 50.f});
  convex.setFillColor(sf::Color(204, 77, 5));
  convex.setPosition(200, 200);
  // convex.setOrigin({500,500});
std::vector<sf::ConvexShape> VecBoid;

 //METTO I PARAMETRI CHE SI INSERISCONO DAL TERMINALE PERò VORREI CAmbiare e farli inserire dal window 
double d,s,a,c;
std::cin>>d,s,a,c;



  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (event.type == event.MouseButtonPressed) { // non funzionaaa
      if (sf::Mouse::getPosition(window).x == bohpar.getPosition().x &&
          sf::Mouse::getPosition(window).y == bohpar.getPosition().y) {

        bohpar.move(sf::Mouse::getPosition(window).x, 10.f);
      }
    }

    if (event.type == event.MouseButtonPressed) {
      if (sf::Mouse::getPosition(window).x > 13.f &&
          sf::Mouse::getPosition(window).x < 33.f &&
          sf::Mouse::getPosition(window).y < 52.f &&
          sf::Mouse::getPosition(window).y > 40.f) {
        // deve scrivere il numero all'interno del rettangolo e poi vabbè
        // chiaramente modificare il numero di boids nello schermo
            

        sf::Text numEnt{"rco",font,20U};
        numEnt.setPosition({300.f, 500.f});
        window.draw(numEnt);
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add) )
    {
      sf::RectangleShape rect({50.f,60.f});
      rect.setPosition({400.f,400.f});
      window.draw(rect);
     VecBoid.push_back(convex);
    }
    
    convex.move(-10.f, -10.f); // qua bisogna mettere la veloxboid
    // convex.rotate(10.f);//fare una funziona che mi cambi l'angolo seguendo il
    // centro di massa
    convex.getPosition();
    //array2 i= veloxBoid(d,s,a,c,convex.getPosition(),);

    boids primo({convex.getPosition().x,convex.getPosition().y},{});//controlla che funzioni veramente


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

    window.clear(sf::Color(0,226, 238));
    optionsWindow.clear(sf::Color(255,255,255));
    window.draw(convex);
    window.draw(usersBars);
    window.draw(nBoid);
    window.draw(bohpar);
    optionsWindow.display();
    window.display();
  }
  return 0;
}