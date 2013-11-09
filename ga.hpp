// geometric algebra
#ifndef GA_HPP
#define GA_HPP

#include <cmath>
#include <cassert>

#include "defs.hpp"

//#include "smmintrin.hpp"

// scalar --------------------------------------------------------------

template <class R>
inline void mov(R &res, const R a) {
	res = a;
}

template <class R>
inline void inn(R &res, const R a, const R b) {
	res = a * b;
}

template <class R>
inline void mul2(R &r, const R a) {
	inn(r, a, a);
}

template <class R>
inline void mul(R &res, const R a, const R b) {
	res = a * b;	
}

// Vector<R> --------------------------------------------------------------


//Vector<Real>(const Vector<int> v) const {
//	rs[0] = v[0]; rs[1] = v[1]; rs[2] = v[2]; 
//}
	

template <class R = float>
class Vector {
	public:
	
	union {
		struct {R x, y, z;};
		struct {R e1, e2, e3;};
		struct {R r, g, b;};
		R rs[3];
	};
	
	inline Vector<R>() {}
	inline Vector<R>(R xx, R yy, R zz) { 
		rs[0] = xx; rs[1] = yy; rs[2] = zz; 
	}	

	
	
	//inline R x() { return rs[0]; }
	//inline R y() { return rs[0]; }
	//inline R z() { return rs[0]; }
	
	inline R &operator[](int i) {
		assert(0 <= i);	assert(i < 3);
		return this->rs[i];
	}
	
	inline const R &operator[](int i) const {
		assert(0 <= i); assert(i < 3);
		return this->rs[i];
	}
	
	//template<class V>
	//inline operator V() { 
	//	return V(rs[0], rs[1], rs[2]); 
	//}

	
};

template<class R = Real>
using Point = Vector<Real>;



template<typename R>
inline Vector<R> operator-(const Vector<R>& a, const Vector<R>& b) {
	Vector<R> c;
	for (int i=0; i<3; ++i) {
		c[i] = a[i] - b[i];
	}
	return c;
}

template<typename R>
inline Real max(const Vector<R>& v) {
	Real r = v[0];
	for (int i=1; i<3; ++i) {
		if (v[i] > r) r = v[i];
	}
	return r;	
}

template<typename R>
inline Real min(const Vector<R>& v) {
	Real r = v[0];
	for (int i=1; i<3; ++i) {
		if (v[i] < r) r = v[i];
	}
	return r;
}


template<typename R>
inline void mov(Vector<R> &a, const Real x, const Real y, const Real z) {
	a.x = x; a.y = y; a.z = z;
}

template<typename R>
inline void mov(Vector<R> &res, const Vector<R>& a) {
	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
}

template<typename R>
inline void inn(Real &res, const Vector<R>& a, const Vector<R>& b) {
	res = a.x * b.x + a.y * b.y + a.z * b.z;
	//res = _mm_cvtss_f32(
	//	_mm_dp_ps(a.m, b.m, 0xFF)
	//);
	//t.v = __builtin_ia32_mulps(a.v, b.v);
}
template<typename R>
inline void sub(Vector<R> &res, const Vector<R> &a, const Vector<R> &b) {
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
}
template<typename R>
inline void add(Vector<R> &res, const Vector<R> &a, const Vector<R> &b) {
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
}
template<typename R>
inline void mul(Vector<R> &res, const Vector<R>& a, const Real f) {
	res.x = a.x*f;
	res.y = a.y*f;
	res.z = a.z*f;
}
template<typename R>
inline void mul(Vector<R> &res, const Real f, const Vector<R>& a) {
	res.x = f*a.x;
	res.y = f*a.y;
	res.z = f*a.z;
}
template<typename R>
inline void vmul(Vector<R> &c, const Vector<R>& a, const Vector<R>& b) {
	c.x = a.x*b.x;
	c.y = a.y*b.y;
	c.z = a.z*b.z;
}

template<typename R>
inline void mul2(Real &r, const Vector<R> &a) {
	inn(r, a, a);
}
template<typename R>
inline void div(Vector<R> &res, const Vector<R>& a, const Real f) {
	res.x = a.x/f;
	res.y = a.y/f;
	res.z = a.z/f;
}

template<typename R>
inline void vdiv(Vector<R> &c, const Vector<R>& a, const Vector<R>& b) {
	c.x = a.x/b.x;
	c.y = a.y/b.y;
	c.z = a.z/b.z;
}

template<typename R>
inline void normalize(Vector<R> &res, const Vector<R>& a) {
	Real m;
	mul2(m, a);
	div(res, a, (Real)sqrt(m));	
}
template<typename R>
inline void rev(Vector<R> &r, const Vector<R> &a) {
	mov(r, a);
}


//void weight(Real &res, Vector<R>& a) {
//	Real m2;
//	inn(m2, a, a);
//	res = sqrt(m2);
//}

template<typename R>
inline bool eq(const Vector<R> &p, const Real x, const Real y, const Real z) {
	return p.x == x && p.y == y && p.z == z;
}

template<typename R>
inline bool vle(const Vector<R> &a, const Vector<R> &b) {
	return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

template<typename R>
inline bool vlt(const Vector<R> &a, const Vector<R> &b) {
	return a.x < b.x && a.y < b.y && a.z < b.z;
}

//----------------------------------------------------------------------
template<typename R = float>
class Bivect {
public:

	union {
		struct {
			R xy, xz, yz;
		};
		struct {
			R e12, e13, e23;
		};
	};
	
	Bivect<R>() { xy = yz = xz = 0; }
	
	Bivect<R>(R e12_, R e13_, R e23_) { e12=e12_; e13=e13_; e23=e23_; }
};

template <class R>
inline void left(Vector<R>& r, const Vector<R>& a, const Bivect<R>& P) {
	r.e1 = - a.e3 * P.e13 - a.e2 * P.e12;
	r.e2 =   a.e1 * P.e12 - a.e3 * P.e23;
	r.e3 =   a.e1 * P.e13 + a.e2 * P.e23;
}

template <class R>
inline void mul2(Real &r, const Bivect<R> &a) {
	r = a.xy * a.xy + a.xz * a.xz + a.yz * a.yz;
}

template <class R>
inline void mov(Bivect<R> &r, const Bivect<R> &a) {
	
	r.xy = a.xy;
	r.xz = a.xz;
	r.yz = a.yz;
}

template <class R>
inline void div(Bivect<R> &r, const Bivect<R> &a, const Real f) {
	
	r.xy = a.xy/f;
	r.xz = a.xz/f;
	r.yz = a.yz/f;
}
template <class R>
inline void normalize(Bivect<R> &res, const Bivect<R>& a) {
	Real m;
	mul2(m, a);
	div(res, a, (Real)sqrt(m));	
}
template <class R>
inline void mul(Bivect<R> &r, const Bivect<R> &a, const Real f) {
	r.e12 = a.e12 * f;
	r.e13 = a.e13 * f;
	r.e23 = a.e23 * f;
}
template <class R>
inline void rev(Bivect<R> &ab, const Bivect<R> &uv) {
	mul(ab, uv, (Real)(-1));
}

template <class R>
inline void out(Bivect<R> &ab, const Vector<R> &a, const Vector<R> &b) {
	ab.xy = -a.y*b.x +a.x*b.y;
	ab.yz = -a.z*b.y +a.y*b.z;
	ab.xz = -a.z*b.x +a.x*b.z;
}
template <class R>
inline void inn(Real &res, const Bivect<R>& a, const Bivect<R>& b) {
	res = - a.xy * b.xy - a.xz * b.xz - a.yz * b.yz;
}



//----------------------------------------------------------------------
template <class R = Real>
struct Volume {
	union {
		R e123;
		R I;
	};
	
	Volume<R>() { e123 = 0; }	
	Volume<R>(R II) { I = II; }	
	
};

template <class R>
inline void mul2(Real &r, Volume<R> &t) {
	r = - t.I * t.I;
}
template <class R>
inline void out(Volume<R> &t, Bivect<R> &a, Vector<R> &b) {
	t.I = a.e23 * b.e1 - a.e13 * b.e2 + a.e12 * b.e3;
}
template <class R>
inline void out(Volume<R> &t, Vector<R> &b, Bivect<R> &a) {
	t.I = a.e23 * b.e1 - a.e13 * b.e2 + a.e12 * b.e3;
}
template <class R>
inline void left(Vector<R> &r, Bivect<R> &b, Volume<R> &t) {
	r.e1 = -b.e23 * t.I;
	r.e2 =  b.e13 * t.I;
	r.e3 = -b.e12 * t.I;	
}

//void div(Real &r, Volume<R> &t, Volume<R> &g) {
//	r = t.I / g.I;
//}
template <class R>
inline void mul(Real &r, Volume<R> &t, Volume<R> &g) {
	r = - t.I * g.I;
}


//----------------------------------------------------------------------
template <class R = float>
struct Rotor {
	union{
		struct{
			R _1, e12, e13, e23;
		};
		//Real f[4];
	};
	
	
	Rotor<R>() { _1 = 1; e12 = e13 = e23 = 0; }	
	
};

template <class R>
void rotor(Rotor<R> &r, const Bivect<R> &nplane, R angle);

template <class R>
inline void rotor(Rotor<R> &r, const Bivect<R> &nplane, double angle) {
	rotor<Real>(r, nplane, (Real) angle);
}


template <class R>
inline void normalize(Rotor<R> &r, const Rotor<R> &t) {
	Real l = sqrt(t.e12*t.e12 + t.e13*t.e13 + t.e23*t.e23 + t._1*t._1);
	r._1 = t._1/l;
	r.e12 = t.e12/l;
	r.e13 = t.e13/l;
	r.e23 = t.e23/l;
	
}
template <class R>
inline void mul(Rotor<R> &r, const Bivect<R> &a, const Bivect<R> &b) {
	
	r.e12 = a.e23 * b.e13 - a.e13 * b.e23;
	r.e13 = a.e12 * b.e23 - a.e23 * b.e12;
	r.e23 = a.e13 * b.e12 - a.e12 * b.e13;
	
	r._1 = - a.e12 * b.e12 - a.e13 * b.e13 - a.e23 * b.e23;
		
}
template <class R>
inline void mov(Rotor<R> &r, const Rotor<R> &t) {
	r._1 = t._1;
	r.e12 = t.e12;
	r.e13 = t.e13;
	r.e23 = t.e23;
}
template <class R>
inline void mul(Rotor<R> &r, const Rotor<R> &a, const Rotor<R> &b) {
	Rotor<R> rr;
	
	rr._1 = a._1*b._1 - a.e12*b.e12 - a.e13*b.e13 - a.e23*b.e23;
	
	rr.e12 = a._1*b.e12 + a.e12*b._1 - a.e13*b.e23 + a.e23*b.e13;
	rr.e13 = a._1*b.e13 + a.e12*b.e23 + a.e13*b._1 - a.e23*b.e12;
	rr.e23 = a._1*b.e23 - a.e12*b.e13 + a.e13*b.e12 + a.e23*b._1;
	
	mov(r, rr);
}
template <class R>
void rotate(Vector<R> &w, const Rotor<R> &r, const Vector<R> &a);

template <class R>
void rotate(Bivect<R> &w, const Rotor<R> &r, const Bivect<R> &a);





template<typename R>
using Point = Vector<Real>;

typedef Vector<Real> Vec;
typedef Vector<int> IVec;



template <class R>
void rotor(Rotor<R> &r, const Bivect<R> &nplane, const R angle) {
	
	Real nsha = - sin(angle/2.0);   // neg sin half-angle
	r.e12 = nplane.e12 * nsha;
	r.e13 = nplane.e13 * nsha;
	r.e23 = nplane.e23 * nsha;
	
	r._1 = cos(angle/2.0);
}

template <class R>
void rotate(Vector<R> &w, const Rotor<R> &r, const Vector<R> &a) {

	Real x = a.x, y = a.y, z = a.z;

	Real c = r._1, s1 = r.e12, s2 = r.e13, s3 = r.e23;

	Real cx = c*x, cy = c*y, cz = c*z;

	Real s1x = s1*x, s1y = s1*y, s1z = s1*z;
	Real s2x = s2*x, s2y = s2*y, s2z = s2*z;
	Real s3x = s3*x, s3y = s3*y, s3z = s3*z;

	w.e1 = c*(cx + s1y + s2z) + s1*(cy - s1x + s3z) - s2*(-cz + s2x + s3y) + s3*(s1z - s2y + s3x);
	w.e2 = c*(cy - s1x + s3z) - s1*(cx + s1y + s2z) - s2*(s1z - s2y + s3x) - s3*(-cz + s2x + s3y);
	w.e3 = -c*(-cz + s2x + s3y) + s1*(s1z - s2y + s3x) - s2*(cx + s1y + s2z) - s3*(cy - s1x + s3z);
}

template <class R>
void rotate(Bivect<R> &w, const Rotor<R> &a, const Bivect<R> &b) {

	Real a0b12 = a._1*b.e12;
	Real a0b13 = a._1*b.e13;
	Real a0b23 = a._1*b.e23;
	
	Real a12b12 = a.e12*b.e12;
	Real a13b12 = a.e13*b.e12;
	Real a23b12 = a.e23*b.e12;
	
	Real a12b13 = a.e12*b.e13;
	Real a13b13 = a.e13*b.e13;
	Real a23b13 = a.e23*b.e13;
	
	Real a12b23 = a.e12*b.e23;
	Real a13b23 = a.e13*b.e23;
	Real a23b23 = a.e23*b.e23;
	
	w.e12 = a._1*(a0b12 - a13b23 + a23b13) + a.e12*(a12b12 + a13b13 + a23b23) - a.e13*(a0b23 - a12b13 + a13b12) + a.e23*(a0b13 + a12b23 - a23b12);
	w.e13 = a._1*(a0b13 + a12b23 - a23b12) + a.e12*(a0b23 - a12b13 + a13b12) + a.e13*(a12b12 + a13b13 + a23b23) - a.e23*(a0b12 - a13b23 + a23b13);
	w.e23 = a._1*(a0b23 - a12b13 + a13b12) - a.e12*(a0b13 + a12b23 - a23b12) + a.e13*(a0b12 - a13b23 + a23b13) + a.e23*(a12b12 + a13b13 + a23b23);

}


#endif


