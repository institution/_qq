#include "test.h"

Real EPS = std::numeric_limits<Real>::epsilon();

void test_rotate() {
	
	Rotor r;
	rotor(r, Bivect(1,0,0), M_PI/2.0);
	
	Vector v(1,0,0);
		
	rotate(v, r, v);
	
	assert(v.x == 0.0f);
	assert(abs(v.y - 1.0) < EPS);
	assert(v.z == 0.0f);
}


void test_fintersect_plane() {
	
	Real f = -123;
	
	Point c(1,1,-1); Vector a(2,0,0); Vector b(0,2,0);
	Point p(0,0,-5); Vector d(0,0,1);
	
	fintersect_plane(f, 
		c, a, b, 
		p, d
	);
	
	assert(f == 4.0);
}

void test_parallelogram() {

	Parallelogram p;
	p.a(-2,1,0).b(0,0,1).pos(1,2,0);
	
	Ray y;
	y.pos(0,0,0).dir(1,2,0);
	
	Real f;
	p.fintersect(f, y);

	printf("%f\n", f);
	assert(f == 1.0);
}

void test_parallelogram2() {

	Parallelogram p;
	p.a(2,0,0).b(0,2,0).pos(-1,-1,0);
	
	Ray y;
	y.pos(0,0,5).dir(0,0,-1);
	
	Real f;
	p.fintersect(f, y);

	printf("%f\n", f);
	assert(f == 5.0);
}

void test_fintersect() {
	
	// f = -(p-c)|d / dd +- sqrt(((p-c)^d)**2 + dd rr) / dd
	// f = (c-p)|inv(d) +- sqrt( ((c-p)^inv(d))**2 + rr inv(d)inv(d) )
	
	Sphere s;
	s.center(2,4,0).radius(sqrt(5));
	
	Ray y;
	y.pos(-2,-3,0).dir(1,3,0);
	
	Real f1, f2;
	fintersect(f1, f2, y, s);

	printf("f1 f2 = %f %f\n", f1, f2);
			
	assert(f1 < INF);
	assert(f1 == 2.0);
	assert(f2 < INF);
	assert(f2 == 3.0);
	
}

void test_inn(){
	Vector a, b;
	Real r;
	
	mov(a, 2,0,0);
	mov(b, 1,1,0);
	
	inn(r, a, b);
	
	assert(r == 2);
}

void test_out() {
	//Bivect ab;
	//Vector a(1,2,3), b(1,2,3);
	
	//out(ab, a, b);
	//assert(ab.xy == 0);
	//assert(ab.yz == 0);
	//assert(ab.xz == 0);
	
}

void test_normalize(){
	Vector a;
		
	mov(a, 1,2,3);
	
	normalize(a, a);
	
	//printf("a = %f %f %f\n", a.x, a.y, a.z);
	
	assert(abs(a.x - 0.267261) < 0.000001);
	assert(abs(a.y - 0.534522) < 0.000001);
	assert(abs(a.z - 0.801783) < 0.000001);
	
}

void test_normal() {
	Sphere s; 
	s.radius(0).center(1,0,0);
	
	Point p;
	mov(p, 3,1,0);
	
	Vector n;
	normal(n, p, s);
	
	//printf("n = %f %f %f\n", n.x, n.y, n.z);
	
	assert(abs(n.x - 0.894427) < 0.000001);
	assert(abs(n.y - 0.447213) < 0.000001);
	assert(abs(n.z - 0.000000) < 0.000001);
		
}


void test_point_on_ray() {
	Point p;
	
	Ray y;
	y.pos(2,0,0).dir(-1,0,0);
	
	point_on_ray(p, y, 5);
	
	assert( eq(p, -3,0,0) );

}

void test_find_intersect() {
	Real f; uint i; Ray y; Elems xs;
	
	xs.resize(2);
	xs[0].reset(new Sphere());
	xs[1].reset(new Sphere());
	
	((Sphere&)*xs[0]).center(+10, 0, 0).radius(1);
	((Sphere&)*xs[1]).center(-10, 0, 0).radius(1);
	
	y.pos(-8,0,0).dir(1,0,0);
	
	find_intersect(f, i, y, xs);
	
	printf("f i = %f %i\n", f, i);
	
	assert(f < INF);
	assert(f == 17.0);
	if (f < INF) assert(i == 0); // undefined when f == INF
	

}

#define TEST(F) printf("------------------------------- %s \n", #F); F(); printf("OK\n")
	
byte do_test = 0;


void test(){
	TEST(test_rotate);
	TEST(test_fintersect_plane);
	TEST(test_parallelogram);
	TEST(test_parallelogram2);
	TEST(test_fintersect);
	TEST(test_out);
	TEST(test_inn);
	TEST(test_normalize);
	TEST(test_normal);
	TEST(test_point_on_ray);
	TEST(test_find_intersect);
}

int main(){
	test();
	return 0;
}
