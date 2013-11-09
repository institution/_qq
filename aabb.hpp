// axis aligned bounding box
#ifndef AABB_HPPPP
#define AABB_HPPPP

#include "ga.hpp"


class Aabb {
	Point<> _a;
	Point<> _b;
	
public:
	Aabb() {}

	Aabb(const Point<> &llo, const Point<> &uup) {
		lower(llo);
		upper(uup);
	}

	// getters	
	inline Point<>& a() { return _a; }
	inline Point<>& b() { return _b; }
	inline const Point<>& a() const { return _a; }
	inline const Point<>& b() const { return _b; }
	
	// setters
	inline Aabb& a(const Point<> &aa) { 
		mov(_a, aa); return *this;
	}
	inline Aabb& b(const Point<> &bb) { 
		mov(_b, bb); return *this;
	}
	
	// new interface
	inline Point<>& lower() { return _a; }
	inline Point<>& upper() { return _b; }
	inline const Point<>& lower() const { return _a; }
	inline const Point<>& upper() const { return _b; }
	
	inline Aabb& lower(const Point<> &aa) { 
		mov(_a, aa); return *this;
	}
	inline Aabb& upper(const Point<> &bb) { 
		mov(_b, bb); return *this;
	}

};



#endif
