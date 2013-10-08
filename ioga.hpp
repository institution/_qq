// i/o for ga objects
#ifndef IOGA_HPP
#define IOGA_HPP

#include <iostream>
#include "ga.hpp"

using namespace std;

ostream &operator<<(ostream &o, const Vector<> &v);
ostream &operator<<(ostream &o, const Bivect<> &r);
ostream &operator<<(ostream &o, const Rotor<> &r);


#endif

