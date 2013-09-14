// i/o for ga objects
#ifndef IOGA_H
#define IOGA_H

#include <iostream>
#include "ga.h"

using namespace std;

ostream &operator<<(ostream &o, const Vector &v);
ostream &operator<<(ostream &o, const Bivect &r);
ostream &operator<<(ostream &o, const Rotor &r);


#endif

