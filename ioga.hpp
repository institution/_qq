// i/o for ga objects
#ifndef IOGA_HPP
#define IOGA_HPP

#include <iostream>
#include "ga.hpp"

using namespace std;

template <class R>
ostream &operator<<(ostream &o, const Vector<R> &v) {
	o << "Vector(" << v.e1 << ',' << v.e2 << ',' << v.e3 << ')';
	return o;
}


template <class R>
ostream &operator<<(ostream &o, const Bivect<R> &r) {
	o << "Bivect(" << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}

template <class R>
ostream &operator<<(ostream &o, const Rotor<R> &r) {
	o << "Rotor(" << r._1 << ',' << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}



#endif

