// geometric algebra
#ifndef GA_H
#define GA_H

#include <cmath>

#include "defs.h"

//#include "smmintrin.h"

//----------------------------------------------------------------------

inline void mov(Real &res, const Real a) {
	res = a;
}

inline void inn(Real &res, const Real a, const Real b) {
	res = a * b;
}


inline void mul2(Real &r, const Real a) {
	inn(r, a, a);
}

//void mov(Real &res, double a) {
//	res = (Real)a;
//}

//void mov(Real &res, int a) {
//	res = (Real)a;
//}

inline void mul(Real &res, const Real a, const Real f) {
	res = a * f;	
}

//----------------------------------------------------------------------
struct Vector {
	union {
		struct {Real x, y, z;};
		struct {Real e1, e2, e3;};
		struct {Real r, g, b;};
	};
	
	Vector() {  x = y = z = 0; }
	Vector(Real xx, Real yy, Real zz) { x = xx; y = yy; z = zz; }
	
};

inline void mov(Vector &a, const Real x, const Real y, const Real z) {
	a.x = x; a.y = y; a.z = z;
}

inline void mov(Vector &res, const Vector& a) {
	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
}

inline void inn(Real &res, const Vector& a, const Vector& b) {
	res = a.x * b.x + a.y * b.y + a.z * b.z;
	//res = _mm_cvtss_f32(
	//	_mm_dp_ps(a.m, b.m, 0xFF)
	//);
	//t.v = __builtin_ia32_mulps(a.v, b.v);
}
  
inline void sub(Vector &res, const Vector &a, const Vector &b) {
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
}

inline void add(Vector &res, const Vector &a, const Vector &b) {
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
}

inline void mul(Vector &res, const Vector& a, const Real f) {
	res.x = a.x*f;
	res.y = a.y*f;
	res.z = a.z*f;
}

inline void mul(Vector &res, const Real f, const Vector& a) {
	res.x = f*a.x;
	res.y = f*a.y;
	res.z = f*a.z;
}


inline void mul2(Real &r, const Vector &a) {
	inn(r, a, a);
}

inline void div(Vector &res, const Vector& a, const Real f) {
	res.x = a.x/f;
	res.y = a.y/f;
	res.z = a.z/f;
}

inline void normalize(Vector &res, const Vector& a) {
	Real m;
	mul2(m, a);
	div(res, a, (Real)sqrt(m));	
}

inline void rev(Vector &r, const Vector &a) {
	mov(r, a);
}


//void weight(Real &res, Vector& a) {
//	Real m2;
//	inn(m2, a, a);
//	res = sqrt(m2);
//}


inline bool eq(const Vector &p, const Real x, const Real y, const Real z) {
	return p.x == x && p.y == y && p.z == z;
}


//----------------------------------------------------------------------

struct Bivect {
	union {
		struct {
			Real xy, xz, yz;
		};
		struct {
			Real e12, e13, e23;
		};
	};
	
	Bivect() { xy = yz = xz = 0; }
	
	Bivect(Real e12_, Real e13_, Real e23_) { e12=e12_; e13=e13_; e23=e23_; }
};

inline void left(Vector& r, const Vector& a, const Bivect& P) {
	r.e1 = - a.e3 * P.e13 - a.e2 * P.e12;
	r.e2 =   a.e1 * P.e12 - a.e3 * P.e23;
	r.e3 =   a.e1 * P.e13 + a.e2 * P.e23;
}


inline void mul2(Real &r, const Bivect &a) {
	r = a.xy * a.xy + a.xz * a.xz + a.yz * a.yz;
}


inline void mov(Bivect &r, const Bivect &a) {
	
	r.xy = a.xy;
	r.xz = a.xz;
	r.yz = a.yz;
}


inline void div(Bivect &r, const Bivect &a, const Real f) {
	
	r.xy = a.xy/f;
	r.xz = a.xz/f;
	r.yz = a.yz/f;
}

inline void normalize(Bivect &res, const Bivect& a) {
	Real m;
	mul2(m, a);
	div(res, a, (Real)sqrt(m));	
}

inline void mul(Bivect &r, const Bivect &a, const Real f) {
	r.e12 = a.e12 * f;
	r.e13 = a.e13 * f;
	r.e23 = a.e23 * f;
}

inline void rev(Bivect &ab, const Bivect &uv) {
	mul(ab, uv, (Real)(-1));
}


inline void out(Bivect &ab, const Vector &a, const Vector &b) {
	ab.xy = -a.y*b.x +a.x*b.y;
	ab.yz = -a.z*b.y +a.y*b.z;
	ab.xz = -a.z*b.x +a.x*b.z;
}

inline void inn(Real &res, const Bivect& a, const Bivect& b) {
	res = - a.xy * b.xy - a.xz * b.xz - a.yz * b.yz;
}



//----------------------------------------------------------------------

struct Volume {
	union {
		Real e123;
		Real I;
	};
	
	Volume() { e123 = 0; }	
	Volume(Real II) { I = II; }	
	
};


inline void mul2(Real &r, Volume &t) {
	r = - t.I * t.I;
}

inline void out(Volume &t, Bivect &a, Vector &b) {
	t.I = a.e23 * b.e1 - a.e13 * b.e2 + a.e12 * b.e3;
}

inline void out(Volume &t, Vector &b, Bivect &a) {
	t.I = a.e23 * b.e1 - a.e13 * b.e2 + a.e12 * b.e3;
}

inline void left(Vector &r, Bivect &b, Volume &t) {
	r.e1 = -b.e23 * t.I;
	r.e2 =  b.e13 * t.I;
	r.e3 = -b.e12 * t.I;	
}

//void div(Real &r, Volume &t, Volume &g) {
//	r = t.I / g.I;
//}

inline void mul(Real &r, Volume &t, Volume &g) {
	r = - t.I * g.I;
}


//----------------------------------------------------------------------

struct Rotor {
	union{
		struct{
			Real _1, e12, e13, e23;
		};
		//Real f[4];
	};
	
	
	Rotor() { _1 = 1; e12 = e13 = e23 = 0; }	
	
};

void rotor(Rotor &r, const Bivect &nplane, Real angle);

inline void normalize(Rotor &r, const Rotor &t) {
	Real l = sqrt(t.e12*t.e12 + t.e13*t.e13 + t.e23*t.e23 + t._1*t._1);
	r._1 = t._1/l;
	r.e12 = t.e12/l;
	r.e13 = t.e13/l;
	r.e23 = t.e23/l;
	
}

inline void mul(Rotor &r, const Bivect &a, const Bivect &b) {
	
	r.e12 = a.e23 * b.e13 - a.e13 * b.e23;
	r.e13 = a.e12 * b.e23 - a.e23 * b.e12;
	r.e23 = a.e13 * b.e12 - a.e12 * b.e13;
	
	r._1 = - a.e12 * b.e12 - a.e13 * b.e13 - a.e23 * b.e23;
		
}

inline void mov(Rotor &r, const Rotor &t) {
	r._1 = t._1;
	r.e12 = t.e12;
	r.e13 = t.e13;
	r.e23 = t.e23;
}

inline void mul(Rotor &r, const Rotor &a, const Rotor &b) {
	Rotor rr;
	
	rr._1 = a._1*b._1 - a.e12*b.e12 - a.e13*b.e13 - a.e23*b.e23;
	
	rr.e12 = a._1*b.e12 + a.e12*b._1 - a.e13*b.e23 + a.e23*b.e13;
	rr.e13 = a._1*b.e13 + a.e12*b.e23 + a.e13*b._1 - a.e23*b.e12;
	rr.e23 = a._1*b.e23 - a.e12*b.e13 + a.e13*b.e12 + a.e23*b._1;
	
	mov(r, rr);
}

void rotate(Vector &w, const Rotor &r, const Vector &a);

void rotate(Bivect &w, const Rotor &r, const Bivect &a);


typedef Vector Point;
typedef Vector Vec;




#endif

