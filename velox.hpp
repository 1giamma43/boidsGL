#ifndef VELOX_HPP
#define VELOX_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <vector>

using array2 = std::array<double, 2>;

array2 separazione(double s, array2 posBoid, std::vector<array2> posAltri);
array2 allineamento(double a, array2 vBoid, std::vector<array2> vAltri);
array2 coesione(double c, array2 posBoid, std::vector<array2> posAltri);
array2 veloxBoid(double d, double s, double a, double c, array2 &posBoid,
                 array2 &vBoid, std::vector<array2> &posAltri,
                 std::vector<array2> &vAltri);

#endif