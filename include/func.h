#ifndef FUNC_H
#define FUNC_H

#include "Point.h"
#include <cmath>

constexpr double L = M_PI;

void euler_mid(Point&, double);
void acceleration(const Point&, Point&, const Point&, double);
void run(const char*, const char*, double, unsigned, unsigned);
double kinetic_energy(const Point*, double, unsigned);
double potential_energy(const Point*, double, unsigned);

#endif //FUNC_H
