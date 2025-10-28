#include "flock.hpp"

// bisogna creare l'altra finestra in cui mettiamo la
// possibilità di variare i parametri e poi si può
// fare la velocità
void flock::moveFlock(float d_s,float d, float s, float a, float c,
                 std::vector<sf::Vector2f> &vBoids) {
  for (auto b:flock_)
  {  
    int i=0;
  b.moveBoid();

  veloxBoid(i,d_s,d,s,a,c, getPositionBoids() ,getvelocityBoids() );

  i++;
}
}

 std::vector<sf::Vector2f> flock::getPositionBoids() {
   std::vector<sf::Vector2f> posBoids={{}};
   for (auto i: flock_)
   {
    posBoids.push_back(i.getpositionb());
   }
   return posBoids;

}

std::vector<sf::Vector2f> flock::getvelocityBoids() {
    std::vector<sf::Vector2f> velocityBoids={{}};
    for (auto i: flock_)
    {
      
    }
    
return ; 
}

void flock::renderWindow() {
  // crea le finestre
  sf::RenderWindow window(sf::VideoMode({800, 600}),
                          "simulation of a flock of boids");
  sf::RenderWindow optionsWindow(sf::VideoMode({200, 600}), "options window");
}

void flock::updateWindow() { // mettere?
}
void flock::drawBoids(sf::RenderWindow &window) {
  // disegnare tutti i boids
  window.draw(flock_[1]); // problema perchè non può disegnare i "boids" credo
                          // perchè non sono shapes
}

void flock::display() {}

