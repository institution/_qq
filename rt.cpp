#include "rt.hpp"

using namespace std;



Real INF = std::numeric_limits<Real>::infinity();
Real EPSILON = std::numeric_limits<Real>::epsilon();
Real EPS = std::numeric_limits<Real>::epsilon();








void fintersect_plane(Real &f, Point<> &c, Vector<> &a, Vector<> &b, Point<> &p, Vector<> &d) {
	Vector<> cp;
	sub(cp, c, p);
	
	Bivect<> P;
	out(P, a, b);
	
	Volume<> I(1);
	
	Vector<> n;
	left(n, P, I);
	
	Real L, M;
	inn(L, cp, n);
	inn(M, d, n);
		
	//printf("MI, LI = %f, %f\n", M.I, L.I);
	
	if (M == 0.0) {
		if (L = 0.0) {
			f = 0.0;
		}
		else {
			f = INF;
			return;
		}
	}
	else {
		f = L/M;		
	}
	
}


void Parallelogram::fintersect(Real &f, Ray &y, Real max_f) {
	Vector<> &d = y.dir();
	
	Vector<> cp;
	sub(cp, _pos, y.pos());
	
	Bivect<> P;
	out(P, _a, _b);
	
	Volume<> I(1);
	Vector<> n;
	left(n, P, I);
	
	Real L, M;
	inn(L, cp, n);
	inn(M, y.dir(), n);
		
	//printf("MI, LI = %f, %f\n", M.I, L.I);
	
	if (M == 0.0) {
		if (L = 0.0) {
			f = 0.0;
		}
		else {
			f = INF;
			return;
		}
	}
	else {
		f = L/M;		
	}
	
	
	Vector<> x;
	mul(x, y.dir(), f);
	sub(x, x, cp);
	// x = f*d - cp
			
	Vector<> aP;
	Real L1, M1;
	left(aP, _a, P);
	inn(L1, x, aP);
	//printf("x %f %f %f\n", x.x, x.y, x.z);
	
	inn(M1, _b, aP);
	
	if (abs(L1/M1) <= 1) {
		
	}
	else {
		//printf("aaa %f\n", L/M);
		f = INF;
		return;
	}
	
	Vector<> bP;
	Real L2, M2;
	left(bP, _b, P);
	inn(L2, x, bP);
	inn(M2, _a, bP);
	if (abs(L2/M2) <= 1) {
		
	}
	else {
		//printf("bbb");
		f = INF;
		return;
	}
		
	
	
}

void Parallelogram::normal(Vector<> &n, Point<> &p) {
	Bivect<> ab;
	Volume<> t;
	t.I = 1.0;
	out(ab, _a, _b);
	left(n, ab, t);
	normalize(n, n);
}




void Sphere::normal(Vector<> &n, Point<> &p) {
	sub(n, p, this->center());
	normalize(n, n); 
}

void normal(Vector<> &n, Point<> &p, Elem &s) {
	s.normal(n, p);
	
	
}

void AABB::fintersect(Real &f, Ray &y, Real max_f) {
	fintersect_aabb(f, y, r, center);	
}

void AABB::normal(Vector<> &n, Point<> &p) {
	
	sub(n, p, center);
	
	//cout << '&' << n << endl;
	//cout << '&' << r << endl;
	
	
	//Real l = 0.0;
	for (int i=0; i<3; ++i) {
		if (abs(n[i]) >= (r[i] - 0.0001)) {
			//l += n[i];
		} else {
			n[i] = 0.0;
		}
	}
	
	//div(n, n, sqrt(l));
	
	normalize(n, n);
	//cout << n << endl;
	
}

void vdir(Vector<> &n, const Point<> &p, const Vector<> &aa, const Vector<> &bb) {
	
	for (int i=0; i<3; ++i) {
		
		if (p[i] >= aa[i] - 0.001) {
			n[i] = 1.0;
		}
		else if (p[i] <= bb[i] + 0.001) {
			n[i] = -1.0;
		}
		else {
			n[i] = 0.0;
		}
		
	}
		
}

/* 
    nref -- index of next cell intersected by ray starting from cref
	grid -- Grid 
	cref -- cell index, Vector<>3<int>
	ray -- Ray(pos, dir)
*/
/*
void next_ref(Vector<>& nref, const Grid &grid, const Vector<> &cref, const Ray &ray) {
	
	Vector<> aa, bb;
	
	vmul(aa, grid.cdim, cref);
	add(bb, aa, grid.cdim);
	
	Real f;
	
	foutintersect_aabb(f, aa, bb, ray);
	
	f * ray.dir() + ray.pos();

	
}*/

bool first(Point<int>& iter, const Grid &g, const Ray &ray) {
	
	Point<> p;
	Real f1, f2;
	fintersect2_aabb(f1, f2, g.aabb(), ray);
	
	if (f1 < INF) {
		
		point_on_ray(p, ray, f1);
		
		for(int i=0; i<3; ++i) {
			iter[i] = (int)(p[i] / g.cdim()[i]);
		}
		
		return 1;
	}
	else {
		return 0;
	}	
}

bool next(Point<int>& iter, const Grid &g, const Ray &ray) {
	
	Point<> a,b;
	for(int i=0; i<3; ++i) {
		a[i] = (Real)iter[i] * g.cdim()[i];
		b[i] = a[i] + g.cdim()[i];
	}
	
	Real f1, f2;
	
	//fintersect2_aabb(f1, f2, Aabb(a,b), ray);
	
	if (f2 < INF) {
		
		//vdir()
		
		//iter
		
		
		return 1;
	}
	else {
		return 0;
	}
	
}







void fintersect_aabb(Real &f, const Ray &y, const Vector<> &r, const Point<> &c) {
	// assert y._dir is normalized
	
	Real min_f = 0.0;
	const Vector<> &v = y._dir;
	
	Vector<> cp;
	sub(cp, c, y._pos);	
	
	Real max_a = -INF, min_b = INF;
	Real a, b;
	Real ri, cpi, vvi;	
	
	for (int i = 0; i < 3; ++i) {
		
		ri = r[i];
		cpi = cp[i];
		vvi = (Real)(1.0)/v[i];
				
		if (vvi < 0)
	    {
			b = (cpi - ri)*vvi;
			a = (cpi + ri)*vvi;
		}
		else // if (vvi > 0) 
		{
			a = (cpi - ri)*vvi;
			b = (cpi + ri)*vvi;
		}
				
		if (a > max_a) {
			max_a = a;
		}
		
		if (b < min_b) {
			min_b = b;
		}
		
	}

	//std::cout << "max_a=" << max_a << std::endl;
	//std::cout << "vd=" << vd << std::endl;

	if ((max_a > min_f) && (max_a <= min_b)) {
		f = max_a;		
	} else {
		f = INF;
	}

}



void Sphere::fintersect(Real &f, Ray &y, Real max_f) {

	Vector<> cp;
	sub(cp, c, y.pos());
	
	Real cp2;
	mul2(cp2, cp);
	
	/*if (cp2 > max_f*max_f) {
		f = INF;
		return;
	}*/	
	
	Real icpd;
	inn(icpd, cp, y.dir());
	
	Real delta = r2 - cp2 + icpd*icpd;

	if (delta < 0) {
		f = INF;
	}
	else {
		f = icpd - sqrt(delta);
	}
}

/*
void Sphere::fintersect(Real &f, Ray &y) {

	Vector<> cp;
	sub(cp, this->center(), y.pos());
	
	Real icpd;
	inn(icpd, cp, y.dir());
	
	Real cp2;
	mul2(cp2, cp);
	
	Real delta = this->radius2() - cp2 + icpd*icpd;

	if (delta < 0) {
		f = INF;
	}
	else {
		f = icpd - sqrt(delta);
	}
}*/


void point_on_ray(Point<> &p, const Ray &y, const Real f) {
	mul(p, y.dir(), f);
	add(p, p, y.pos());
}





void find_intersect(Real &f, Elem* &e, Ray &y, Grid &gr, Elem *skip) {
	Real f1;
	Elem* c;	
	
	e = nullptr;
	f = INF;
	
	auto itr = gr.iter_along_ray(y);
		
	while (c = itr.next())
	{
		if (c != skip) {
			
			c->fintersect(f1, y, f);
			
			if (EPSILON < f1 && f1 < f) {
				f = f1;
				e = c;
			}
		}
	}	
	
}

Point<> light(-700.0, 1000.0, 400.0);
cre

void trace(Color &rcol, Ray &y, Grid &gr) {
	Real f;
	Elem* e1;
	
	find_intersect(f, e1, y, gr, nullptr);
	
	if (f == INF) {
		mov(rcol, blue);
	}
	else {
		Vector<> n;
		Ray shadow;
	
		Elem &s = *e1;
	
		// contact point
		point_on_ray(shadow.pos(), y, f);
		
		// dir
		sub(shadow.dir(), light, shadow.pos());
		normalize(shadow.dir(), shadow.dir());
				
		// normalna sfery w punkcie styku
		normal(n, shadow.pos(), s);
		
		// natezenie
		Real e;
		inn(e, n, shadow.dir());
		
		
		if (e <= 0.0) {
			mov(rcol, black);
		}
		else {
			Real f2; 
			Elem * e2;
			//trace(shadow_col, shadow, objs);
			find_intersect(f2, e2, shadow, gr, e1);
			
			if (f2 < INF) {
				mov(rcol, black);
			}
			else{
				
				// shader
				mul(rcol, s.color(), e);
				
				// object color
				//Color &sphere_col = red;
				//scale(rcol, rcol, sphere_col);		
			}
		}		
	} 

}

/*
void render() {
	
	uint width = 400, height = 400; 
	byte maxval = 255;
	
	printf("P6 %d %d %d\n", width, height, maxval);
	
	
	Elems xs;
	
	
	//objs.resize(9);
	
		
	Real a=2.0, b=1.5, c=1.0, t=2.8;
	
	
	Sphere  * s = NULL;
	
	s = new Sphere();
	s->center(10.0, a+b+b+c-t-1.0, 0).radius(c).fr();
	xs.push_back(unique_ptr<Elem>(s));
	
	
	s = new Sphere();
	(*s).center(10.0, a+b-t-0.5, 0).radius(b).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(10.0, 0-t, 0).radius(a).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(10.0, a+b-t, +0.9*b).radius(.6).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(10.0, a+b-t, -0.9*b).radius(.6).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(9.06, a+b+b+c-t-1.1, 0).radius(.15).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere(); 
	(*s).center(9.15, a+b+b+c-t-0.8, +0.4).radius(.1).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(9.15, a+b+b+c-t-0.8, -0.4).radius(.1).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(10, -50000-t-a+1, 0).radius(50000).fr();
	xs.push_back(ElemPtr(s));
	
	s = NULL;
	
	Parallelogram *p = new Parallelogram();
	(*p).pos(10, -t, 3.5).a(0,1,0).b(0,0,1);
	xs.push_back(ElemPtr(p));
	p = NULL;
	
	
	//Color col(64,64,64);
	//s.color = &col;
	
	Point<> cam_pos(0,0.1,0);
	Vector<> cam_dir(1,-0.1,-0.1);
	//normalize(cam_dir, cam_dir);
	
	Real scr_width = 1, scr_HPPeight = 1;
	Real hheight = height/2.0;
	Real hwidth = width/2.0;
	
	//Point<> light(-20,50,35);

	int j = height;
	int i;
	while (j > 0) {
		j -= 2;
		
		i = 0;
		while (i < width) {
			 
			Real x = 1; // scr_dist
			Real y = j * scr_HPPeight/height - scr_HPPeight/2;
			Real z = i * scr_width/width - scr_width/2;
			
			x = width; // scr_dist
			y = j - hheight;
			z = i - hwidth;
									
			Ray ray;
			ray.dir(x,y,z).pos(cam_pos);
			normalize(ray.dir(), ray.dir());
				
			Color rcol;
			trace(rcol, ray, xs);
			putcolor(rcol);

			putcolor(black);
			i += 2;
		}
		
		i = 0;		
		while (i < width) {
			putcolor(black);
			i += 1;
		}
	}
	
	
	xs.clear();
	
}

*/
