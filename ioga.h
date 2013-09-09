// i/o for ga objects
#ifndef IOGA_H
#define IOGA_H

#include <iostream>
#include "ga.h"

using namespace std;

ostream &operator<<(ostream &o, const Vector &v) {
	o << "Vector(" << v.e1 << ',' << v.e2 << ',' << v.e3 << ')';
	return o;
}


ostream &operator<<(ostream &o, const Bivect &r) {
	o << "Bivect(" << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}

ostream &operator<<(ostream &o, const Rotor &r) {
	o << "Rotor(" << r._1 << ',' << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}

#endif

