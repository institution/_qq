// intersection algorithms
#ifndef INTERSECT_HPP
#define INTERSECT_HPP

#include <iostream>
#include <cmath>
#include <cassert>

#include "ga.hpp"
#include "ray.hpp"
#include "aabb.hpp"

extern Real INF;


void fintersect2_aabb(Real &f1, Real &f2, Aabb const& ab, Ray const& ray);

		
#endif
