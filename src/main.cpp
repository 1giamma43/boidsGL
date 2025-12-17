#include "options.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// COSE DA FARE:ottimizzare, i test per tutte le funzioni anche quelle non
// numeriche(non so come), inserire il parametro di distanza
// media tra i boids con deviazione standard, se riesco faccio
// il predatore (i boids applicano su di esso solo la separazione, mentre i
// predatori applicano solo la coesione con i boids ti direi) magari aggiungere
// qualche nuvola nello sfondo

int main() {

  sf::RenderWindow window(sf::VideoMode({1400, 600}),
                          "simulation of a flock of boids");
  window.setPosition({100, 100});
  window.setFramerateLimit(40);
  // come faccio ad aumentare la sua fluidità?
  //////////////////////////////////////////////////////

  sf::Font font;
  sf::RectangleShape sfondo({400.f, 600.f});
  sfondo.setFillColor(sf::Color(0, 0, 0));
  sfondo.setPosition(1000.f, 0.f);
  
  sf::Texture texture1,texture2;
  texture1.loadFromFile("nuvola.png");
  sf::Sprite cloud1,sun;
  cloud1.setTexture(texture1);
  cloud1.setPosition({20.f,30.f});
  cloud1.setScale({0.5f,0.5f});

  texture2.loadFromFile("sole.png");
  sun.setTexture(texture2);
  sun.setPosition({860.f,50.f});
  sun.setScale({0.08f,0.08f});

  sf::RectangleShape modNBoids({300.f, 40.f}), dParam({300.f, 40.f}),
      d_sParam({300.f, 40.f}), sParam({300.f, 40.f}), aParam({300.f, 40.f}),
      cParam({300.f, 40.f}), distanceParam({300.f, 40.f}),
      velocityParam({300.f, 40.f});

  sf::Text usersText, usersText2, usersText3, usersText4, usersText5,
      usersText6, outputText1, outputText2;
  sf::Text usersNumText, usersNumText2, usersNumText3, usersNumText4,
      usersNumText5, usersNumText6, outputNumText1, outputNumText2;

  std::string label = "Number of boids-------->",
              label2 = "Modify parameter d----->",
              label3 = "Modify parameter d_s--->",
              label4 = "Modify parameter s----->",
              label5 = "Modify parameter a----->",
              label6 = "Modify parameter c----->",
              OutLabel1 = "Mean distance x ------>",
              OutLabel2 = "Mean velocity v ------>";

  float y = 0.f, y2 = 50.f, y3 = 100.f, y4 = 150.f, y5 = 200.f, y6 = 250.f,
        y7 = 500.f, y8 = 550.f;

  int numBoids = 13;
  float dPar = 100.f, d_sPar = 20.f, sPar = 0.0018f, aPar = 0.001f, cPar = 0.0006f,
        meanDistance = 0.f, meanVelocity = 0.f;

  setParameters(window, modNBoids, usersText, usersNumText, font, y, label, numBoids);
  setParameters(window, dParam, usersText2, usersNumText2, font, y2, label2, dPar);
  setParameters(window, d_sParam, usersText3, usersNumText3, font, y3, label3, d_sPar);
  setParameters(window, sParam, usersText4, usersNumText4, font, y4, label4, sPar);
  setParameters(window, aParam, usersText5, usersNumText5, font, y5, label5, aPar);
  setParameters(window, cParam, usersText6, usersNumText6, font, y6, label6, cPar);
  setParameters(window, distanceParam, outputText1, outputNumText1, font, y7,
                OutLabel1, meanDistance);
  setParameters(window, velocityParam, outputText2, outputNumText2, font, y8,
                OutLabel2, meanVelocity);

  flock stormo;
  stormo.setFlockSize(numBoids);
  std::vector<sf::Vector2f> posFlock = {{}};

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      numBoids = insertParameters<int>(event, window, modNBoids, numBoids,
                                       usersNumText);
      stormo.setFlockSize(numBoids);

      d_sPar = insertParameters<float>(event, window, d_sParam, d_sPar,
                                       usersNumText3);
      // bisogna inserire la possibilità di scirvere la frase giusta e settare
      // il dominio dei numeri (tipo da uno a 30 per il numero di boids )
      dPar =
          insertParameters<float>(event, window, dParam, dPar, usersNumText2);
      sPar =
          insertParameters<float>(event, window, sParam, sPar, usersNumText4);
      aPar =
          insertParameters<float>(event, window, aParam, aPar, usersNumText5);
      cPar =
          insertParameters<float>(event, window, cParam, cPar, usersNumText6);
    }
    stormo.collision();
    std::vector<sf::Vector2f> prevPosFlock = posFlock;
    posFlock = stormo.getPositionFlock();
    std::vector<sf::Vector2f> velocityFlock =
        stormo.getVelocityFlock(posFlock, prevPosFlock);
    std::vector<sf::Vector2f> veloxboid =
        veloxBoid(d_sPar, dPar, sPar, aPar, cPar, posFlock, velocityFlock);
    /*// i boids si incastrano in alto a sinistra perchè la distanza
tecnicamente
    // è più di mille però noi vogliamo pensare lo spazio come toroidale quindi
    // in teoria dovremmo considerarli vicini... come si fa?
   // void Funzionediprova(){ forse è da mettere direttamente nella funzione
veloxboid

   for (size_t i = 0; i < stormo.size(); i++)
{
  for (size_t j = 0; j < stormo.size(); j++)
  {

  if (1000.f-(stormo[i].getpositionb().x -stormo[j].getpositionb().x)<dPar)
  {
    //devo dire che la loro distanza è 1000.f-(stormo[i].getpositionb().x
-stormo[j].getpositionb().x) però come faccio a dirgli verso dove ansare?
  }

}}
*/
    // per qualche motivo vanno tutti verso l'alto a sinistra

    stormo.moveFlock(veloxboid);
    std::vector<float> x = vecModVelox(veloxboid);
    outputNumText2.setString(std::to_string(std::llroundf(calculateMean(x))) + " +/- " +
                             std::to_string(std::llroundf(calculateStdDeviation(x))));
    // come faccio il round alla prima cifra dopo la virgola
    window.clear(sf::Color(0, 226, 208));
    window.draw(sfondo);
    draw(window, modNBoids, usersText, usersNumText);
    draw(window, dParam, usersText2, usersNumText2);
    draw(window, d_sParam, usersText3, usersNumText3);
    draw(window, sParam, usersText4, usersNumText4);
    draw(window, aParam, usersText5, usersNumText5);
    draw(window, cParam, usersText6, usersNumText6);
    draw(window, distanceParam, outputText1, outputNumText1);
    draw(window, velocityParam, outputText2, outputNumText2);
    window.draw(cloud1);
    window.draw(sun);
    stormo.drawFlock(window);
    window.display();
  }
  return 0;
}