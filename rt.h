// ray tracer
#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <vector>
#include <limits>
#include <memory>

#include "ga.h"
#include "defs.h"
#include "elem.h"
#include "color.h"
#include "ray.h"

extern Real INF;


class Sphere: public Elem {
	public:
	// geometry
	Vector c;  // center
	Real r, r2;  // radius
	
	Color col;
	
	public:
	
	Sphere() { col = white; }
	
	Sphere(Point &pos, Real radius) {
		col = white;
		
		c = pos;
		r = radius;
		fr();
	}
	
	// getters
	Vector& center() { return c; }	
	Real& radius() { return r; }	
	
	Real radius2() { return r2; }	
	
	// setters
	Sphere& center(Real x, Real y, Real z) { mov(c, x,y,z); return *this; }
	Sphere& radius(Real rr) { mov(r, rr); return *this; }
	
	void fr() {
		r2 = r*r;
	}
	
	void fintersect(Real &f, Ray &y);
	void normal(Vector &n, Point &p);
	virtual Color& color() { return col; }	
		
	// material
	
	// lightscr
		
	// pochlanianie
	// kolor powierzchni
	// kolor swiatla
	// wsp odbicia
	// wsp zagiecia
	//reflect
	//refract
	//emission
	
};


class CSphere: public Sphere {
	public:
	
	Color col;
	
	
	
	CSphere() { col = blue; }
	
	virtual Color& color() { return col; }	

};




class Parallelogram: public Elem {
	
	// geometry
	Vector _a, _b;
	Point _pos;
	
	public:
	// getters
	Vector& pos() { return _pos; }	
	
	// setters
	Parallelogram& pos(Real x, Real y, Real z) { mov(_pos, x,y,z); return *this; }
	Parallelogram& a(Real x, Real y, Real z) { mov(_a, x,y,z); return *this; }
	Parallelogram& b(Real x, Real y, Real z) { mov(_b, x,y,z); return *this; }
	
		
	void fintersect(Real &f, Ray &y);
	void normal(Vector &n, Point &p);		
	Color& color() { return cyan; }	

};

void fintersect_plane(Real &f, Point &c, Vector &a, Vector &b, Point &p, Vector &d);
void fintersect(Real &f1, Real &f2, Ray &y, Sphere &s);
void normal(Vector &n, Point &p, Elem &s);
void point_on_ray(Point &p, Ray &y, Real f);
void find_intersect(Real &f, uint &ii, Ray &y, Elems &xs);






void trace(Color &rcol, Ray &y, Elems &xs);


#endif
