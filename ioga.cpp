#include "ioga.hpp"

ostream &operator<<(ostream &o, const Vector<> &v) {
	o << "Vector<>(" << v.e1 << ',' << v.e2 << ',' << v.e3 << ')';
	return o;
}


ostream &operator<<(ostream &o, const Bivect<> &r) {
	o << "Bivect<>(" << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}

ostream &operator<<(ostream &o, const Rotor<> &r) {
	o << "Rotor<>(" << r._1 << ',' << r.e12 << ',' << r.e13 << ',' << r.e23 << ')';
	return o;
}
