#ifndef BOID_HPP
#define BOID_HPP
#include "velox.cpp"

class boids {
  array2 pos_;
  array2 vel_;

public:
  boids(array2 x, array2 v) : pos_{x}, vel_{v} {}
  array2 veloxboid(double d, double s, double a, double c,
                                  array2 posBoid, array2 vBoid,
                                  std::vector<array2> posAltri,
                                  std::vector<array2> vAltri);

};
#endif