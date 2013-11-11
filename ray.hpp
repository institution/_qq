// ray
#ifndef RAY_HPP
#define RAY_HPP

#include "ga.hpp"

class Ray {
	public:
	
	Vector<> _dir;  // dir -- not necessarily normalized
	Point<> _pos;   // pos -- ray source
	
	Ray() {}
	Ray(Vector<> dir_, Point<> pos_) { _dir = dir_; _pos = pos_; }
	
	public:
	// getters	
	Vector<>& dir() { return _dir; }
	Point<>& pos() { return _pos; }
	
	const Vector<>& dir() const { return _dir; }
	const Point<>& pos() const { return _pos; }
	
	// setters
	Ray& dir(const Vector<> &d) { 
		mov(_dir, d); return *this; 
	}
	
	Ray& pos(const Point<> &p) { 
		mov(_pos, p); return *this; 
	}

	Ray& dir(Real x, Real y, Real z) { 
		mov(_dir, x,y,z); return *this; 
	}
	
	Ray& pos(Real x, Real y, Real z) { 
		mov(_pos, x,y,z); return *this; 
	}
	
	Point<> point_at(const Real f) const {
		Point<> p;
		mul(p, this->dir(), f);
		add(p, p, this->pos());
		return p;
	}
	
	// freezers
	Ray& normalize() {		
		::normalize(_dir, _dir); return *this; 
	}
	
};




#endif
