// ray tracer
#ifndef RT_HPP
#define RT_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <vector>
#include <limits>
#include <memory>
#include <string>

#include "ga.hpp"
#include "ioga.hpp"
#include "defs.hpp"
#include "elem.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "aabb.hpp"
#include "grid.hpp"
#include "intersect.hpp"


extern Real INF;




void inc_gref(Vector<> &ref, Grid &g, Ray &y);


class Sphere: public Elem {
	public:
	// geometry
	Vector<> c;  // center
	Real r, r2;  // radius
	
	Color col;
	
	public:
	
	Sphere() { col = white; }
	
	Sphere(Point<> &pos, Real radius) {
		c = pos;
		r = radius;
		r2 = r*r;
		
		col = white;
	}
	
	// getters
	Vector<>& center() { return c; }	
	Real& radius() { return r; }	
	
	Real radius2() { return r2; }	
	
	// setters
	Sphere& center(Real x, Real y, Real z) { mov(c, x,y,z); return *this; }
	Sphere& radius(Real rr) { mov(r, rr); return *this; }
	
	void fr() {
		r2 = r*r;
	}
	
	void fintersect(Real &f, Ray &y, Real max_f);
	void normal(Vector<> &n, Point<> &p);
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
	Vector<> _a, _b;
	Point<> _pos;
	
	public:
	// getters
	Vector<>& pos() { return _pos; }	
	
	// setters
	Parallelogram& pos(Real x, Real y, Real z) { mov(_pos, x,y,z); return *this; }
	Parallelogram& a(Real x, Real y, Real z) { mov(_a, x,y,z); return *this; }
	Parallelogram& b(Real x, Real y, Real z) { mov(_b, x,y,z); return *this; }
	
		
	void fintersect(Real &f, Ray &y, Real max_f);
	void normal(Vector<> &n, Point<> &p);		
	Color& color() { return cyan; }	

};




class AABB: public Elem {
	
	// geometry
	Vector<> r;
	Point<> center;
	
	public:
	
	AABB() {}
	
	AABB(const Vector<> &r, const Point<> &center) {
		mov(this->r, r);
		mov(this->center, center);
	}
		
	void fintersect(Real &f, Ray &y, Real max_f);
	void normal(Vector<> &n, Point<> &p);		
	Color& color() { return yellow; }	
	
	

};


void fintersect_plane(Real &f, Point<> &c, Vector<> &a, Vector<> &b, Point<> &p, Vector<> &d);
void fintersect(Real &f1, Real &f2, Ray &y, Sphere &s);
void normal(Vector<> &n, Point<> &p, Elem &s);
void point_on_ray(Point<> &p, const Ray &y, const Real f);
void find_intersect(Real &f, Elem* &e, Ray &y, Grid &gr, Elem *skip);

void fintersect_aabb(Real &f, const Ray &y, const Point<> &c, const Vector<> &r);


void trace(Color &rcol, Ray &y, Grid &gr);


extern Real EPS;











#endif
