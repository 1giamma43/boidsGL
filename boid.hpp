#ifndef BOID_HPP
#define BOID_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "velox.hpp"
#include <SFML/Graphics/Texture.hpp>

class boids {
  sf::ConvexShape boid_1_;

public:
  boids(sf::ConvexShape convex) : boid_1_{convex} { // crea un oggetto boids
    sf::ConvexShape convex(
        4); // biogna avere un qualcosa per selezionare quanti convex creare+
            // vorrei poterlo scegliere tramite un aggeggio nel window
    convex.setPoint(0, {0.f, 0.f});
    convex.setPoint(1, {60.f, 20.f});
    convex.setPoint(2, {40.f, 30.f});
    convex.setPoint(3, {30.f, 50.f});
    convex.setFillColor(sf::Color(204, 77, 5));
    convex.setPosition(rand() % 800, rand() % 600);
  };
  ~boids();
  
  void eraseBoid();
  void moveBoid();
  sf::Vector2f getpositionb();
  void getdistance(); // serve?
};
#endif