#include "boid.hpp"
#include <algorithm>
#include <cmath>
#include <functional>


array2 veloxboid(double d, double s, double a, double c, array2 posBoid,
                 array2 vBoid, std::vector<array2> posAltri,
                 std::vector<array2> vAltri) {
  std::vector<array2> vecDistanze;
  std::vector<double> vModDistanze;
  for (size_t i = 0; i < posAltri.size(); i++) {
    vecDistanze[i][0] =
        posBoid[0] -
        posAltri[i][0]; // forse non andrà perchè il vector è stato creato vuoto
                        // e per riempirlo si usa push_back
    vecDistanze[i][1] = posBoid[1] - posAltri[i][1];
    vModDistanze.push_back(
        sqrt(powf(vecDistanze[i][0], 2) + powf(vecDistanze[i][1], 2)));
  }
  auto it =vModDistanze.begin();
 
  if (std::find_if(it, vModDistanze.end(), std::less<double>{}(d,*it) ) ==
      vModDistanze.end()) {
    array2 velox;
    velox[0] = vBoid[0] + separazione(s, posBoid, posAltri)[0] +
               allineamento(a, vBoid, vAltri)[0] +
               coesione(c, posBoid, posAltri)[0];
    velox[1] = vBoid[1] + separazione(s, posBoid, posAltri)[1] +
               allineamento(a, vBoid, vAltri)[1] +
               coesione(c, posBoid, posAltri)[1];
  };
}
