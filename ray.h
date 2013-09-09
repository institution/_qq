// ray
#ifndef RAY_H
#define RAY_H

#include "ga.h"

class Ray {
	public:
	
	Vector _dir;  // dir -- not necessarily normalized
	Point _pos;   // pos -- ray source
	
	Ray() {}
	Ray(Vector dir_, Point pos_) { _dir = dir_; _pos = pos_; }
	
	public:
	// getters	
	Vector& dir() { return _dir; }
	Point& pos() { return _pos; }
	
	// setters
	Ray& dir(Vector &d) { 
		mov(_dir, d); return *this; 
	}
	
	Ray& pos(Point &p) { 
		mov(_pos, p); return *this; 
	}

	Ray& dir(Real x, Real y, Real z) { 
		mov(_dir, x,y,z); return *this; 
	}
	
	Ray& pos(Real x, Real y, Real z) { 
		mov(_pos, x,y,z); return *this; 
	}
	
};


#endif
