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

#include "ga.hpp"
#include "ioga.hpp"
#include "defs.hpp"
#include "elem.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "aabb.hpp"

extern Real INF;




class Grid {
	vector<Elems> _space;
	
	Aabb _ab;
	Vector<> _res; // log2(res)
	Vector<> _cdim;
		
public:
	Grid() {}
	
	
	// getters
	inline const Aabb& ab() const { return _ab; }	
	inline const Aabb& aabb() const { return _ab; }	
	inline const Vector<>& res() const { return _res; }
	inline const Vector<>& cdim() const { return _cdim; }
	
	// setters
	inline Grid& ab_res(const Aabb& ab, const Vector<>& res) {
		_ab = ab;
		_res = res;
		vdiv(_cdim, ab.b() - ab.a(), res);		
		_space.resize(res[0]*res[1]*res[2]);
		return *this;
	}
	inline Grid& res_ab(const Vector<>& res, const Aabb& ab) {
		return ab_res(ab, res);
	}
	
	
	/*
	Elems& get(Vector<> &ref) {
		
		assert(vle(ref, res));
		
		return sp[int(ref.x) + int(ref.y)*rx + int(ref.z)*rx*ry];
	}
	
	//void add(Vector<> &ref, Elem *e) {
	//	get(ref).push_back(ElemPtr(e));
	//}
	
	void insert(Elem *e, Vector<> &p) {
		Vector<> ref;
		
		vdiv(ref, p, cell_dim);
		
		get(ref).push_back(ElemPtr(e));
	}
	*/
	
	~Grid() {
		for (int i=0; i<_space.size(); ++i) {
			_space[i].clear();
		}
	}
	

	
};






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
void find_intersect(Real &f, int &ii, Ray &y, Elems &xs, int skip);

void fintersect_aabb(Real &f, const Ray &y, const Point<> &c, const Vector<> &r);


void fintersect2_aabb(Real &f1, Real &f2, const Aabb &ab, const Ray &ray);

void trace(Color &rcol, Ray &y, Elems &xs);


extern Real EPS;











#endif
