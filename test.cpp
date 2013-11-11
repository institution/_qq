#include "test.hpp"

extern Real EPS; // = std::numeric_limits<Real>::epsilon();

void test_fintersect2_aabb() {

	Real f1, f2;
	
	fintersect2_aabb(f1, f2,
		Aabb().a(Point<>(-1,-1,-1)).b(Point<>(1,1,1)),
		Ray().pos(Point<>(2,2,2)).dir(Vector<>(-1,-1,-1)).normalize()
	);
	
	
	cout << f1 << '|' << sqrt(3.0f) << endl;
	cout << f2 << '|' << sqrt(27.0f) << endl;
	
	assert(abs(f1 - sqrt(3.0f)) < 0.000001);
	assert(abs(f2 - sqrt(27.0f))  < 0.000001);
}



void test_fintersect_aabb() {
	Real f = -123;
	
	fintersect_aabb(f, 
		Ray().dir(Vector<>(-1,0,0)).pos(Point<>(10,0.4,0.2)), 
		Vector<>(1,1,1),
		Point<>(1,0,0)
	);	
	
	cout <<  f << endl;
	assert(f == 8.0);
	
	
	fintersect_aabb(f, 
		Ray(Vector<>(-1.0/sqrt(2.0),-1.0/sqrt(2.0),0), Point<>(2,1,0)), 
		Vector<>(1,1,1),
		Point<>(0,0,0)
	);	
	
	cout << f << '|' << sqrt(2.0) << endl;
	assert(abs(f - sqrt(2.0)) < EPS);
		
}


void test_fintersect_aabb_miss() {
	
	Real f = -123;
	
	fintersect_aabb(f, 
		Ray(Vector<>(-1,0,0), Point<>(10,1.1,0.2)), 
		Vector<>(1,1,1),
		Point<>(1,0,0)
	);	
	
	cout <<  f << endl;
	assert(f == INF);
		
}

void test_rotate() {
	
	Rotor<> r;
	rotor(r, Bivect<>(1,0,0), M_PI/2.0);
	
	Vector<> v(1,0,0);
		
	rotate(v, r, v);
	
	assert(v.x == 0.0f);
	assert(abs(v.y - 1.0) < EPS);
	assert(v.z == 0.0f);
}


void test_fintersect_plane() {
	
	Real f = -123;
	
	Point<> c(1,1,-1); Vector<> a(2,0,0); Vector<> b(0,2,0);
	Point<> p(0,0,-5); Vector<> d(0,0,1);
	
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
	p.fintersect(f, y, 0.0);

	printf("%f\n", f);
	assert(f == 1.0);
}

void test_parallelogram2() {

	Parallelogram p;
	p.a(2,0,0).b(0,2,0).pos(-1,-1,0);
	
	Ray y;
	y.pos(0,0,5).dir(0,0,-1);
	
	Real f;
	p.fintersect(f, y, 0.0);

	printf("%f\n", f);
	assert(f == 5.0);
}

/*
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
	
}*/

void test_inn(){
	Vector<> a, b;
	Real r;
	
	mov(a, 2,0,0);
	mov(b, 1,1,0);
	
	inn(r, a, b);
	
	assert(r == 2);
}

void test_out() {
	//Bivect<> ab;
	//Vector<> a(1,2,3), b(1,2,3);
	
	//out(ab, a, b);
	//assert(ab.xy == 0);
	//assert(ab.yz == 0);
	//assert(ab.xz == 0);
	
}

void test_normalize(){
	Vector<> a;
		
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
	
	Point<> p;
	mov(p, 3,1,0);
	
	Vector<> n;
	normal(n, p, s);
	
	//printf("n = %f %f %f\n", n.x, n.y, n.z);
	
	assert(abs(n.x - 0.894427) < 0.000001);
	assert(abs(n.y - 0.447213) < 0.000001);
	assert(abs(n.z - 0.000000) < 0.000001);
		
}


void test_point_on_ray() {
	Point<> p;
	
	Ray y;
	y.pos(2,0,0).dir(-1,0,0);
	
	point_on_ray(p, y, 5);
	
	assert( eq(p, -3,0,0) );

}

void test_grid_index_of() {
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Vector<int> k;
	k = gr.index_of(Vector<>(-10,0,0));
	
	cout << k << endl;
	assert(eq(Vector<int>(0,1,1), k));
}

// regression
void test_grid_index_of_2() {
	
	Grid gr = Grid::box_res(
		Aabb(Vector<>(0,0,0), Vector<>(100,100,100)),
		Vector<>(10,10,10)
	);
	
	Vector<int> k;
	k = gr.index_of(Vector<>(0.00789726619, 0.105758078, -0.00211606687));
	
	cout << k << endl;
	assert(eq(Vector<int>(0,0,-1), k));
	
}



void test_grid_iter() {
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Vector<> x1(-7, -6, -9);
	Elem* e1 = new Sphere(x1, 2.2);
	gr.add(x1, e1);
	
	Vector<> x2(7, 6, 9);
	Elem* e2 = new Sphere(x2, 2.2);
	gr.add(x2, e2);
	
	
	GridIter it(gr);
	
	auto e = it.next();
		
	cout << "e1=" << e1 << endl;
	cout << "e=" << e << endl;
	assert(e1 == e);
	
	e = it.next();
		
	cout << "e2=" << e2 << endl;
	cout << "e=" << e << endl;
	assert(e2 == e);
	
}

void test_grid_iter_along_ray_no_hit()
{
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Ray ray;
	ray.dir(Vector<>(1,0,0)).pos(Vector<>(-20, 5, 5));
	
	auto it = gr.iter_along_ray(ray);
	auto e = it.next();			
	assert(e == nullptr);	
}


void test_grid_iter_along_ray_border_away()
{
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Ray ray;
	ray.dir(Vector<>(0,1,0)).pos(Vector<>(10,9,10));
	
	auto it = gr.iter_along_ray(ray);
	auto e = it.next();			
	assert(e == nullptr);	
}

void test_grid_iter_along_ray_total_miss_grid()
{
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Ray ray;
	ray.dir(Vector<>(1,0,0)).pos(Vector<>(20, 50, 60));
	
	auto it = gr.iter_along_ray(ray);
	auto e = it.next();			
	assert(e == nullptr);	
}

void test_grid_iter_along_ray()
{
	
	Grid gr;
	gr.ab_res(
		Aabb().a(Vector<>(-10,-10,-10)).b(Vector<>(10,10,10)),
		Vector<>(2,2,2)
	);
	
	Vector<> x1(-7, -6, -9);
	Elem* e1 = new Sphere(x1, 2.2);
	gr.add(x1, e1);
	
	Vector<> x2(7, 9, 9);
	Elem* e2 = new Sphere(x2, 2.2);
	gr.add(x2, e2);
	
	
	Ray ray;
	ray.dir(Vector<>(1,0,0)).pos(Vector<>(-20, 5, 5));
	
	auto it = gr.iter_along_ray(ray);
	
	auto e = it.next();
		
	cout << "e2=" << e2 << endl;
	cout << "e=" << e << endl;
	assert(e2 == e);

	e = it.next();
			
	assert(e == nullptr);
	
}







void test_find_intersect() {
	Real f; int i; Ray y; 
	Elems xs;
	
	Grid gr;
	gr.ab_res(
		Aabb(
			Point<>(-10,-10,-10), 
			Point<>(10,10,10)
		),
		Vector<>(2,2,2)
	);
	
	Vector<> x1(+7, 0, 0);
	Vector<> x2(-7, 0, 0);
	Elem* e1 = new Sphere(x1, 1);
	Elem* e2 = new Sphere(x2, 1);
	gr.add(x1, e1);
	gr.add(x2, e2);
	
	y.pos(-1,0,0).dir(1,0,0);
	
	Elem *e = nullptr;

	find_intersect(f, e, y, gr, nullptr);
	
	
	// printf("f i = %f %i\n", f, i);
	cout << "f=" << f << endl;
	cout << "e1=" << e1 << endl;
	cout << "e2=" << e2 << endl;
	cout << "e=" << e << endl;
	
	assert(f < INF);
	assert(f == 7.0);
	
	assert(e1 == e);
	
	
	
}

#define TEST(F) printf("------------------------------- %s \n", #F); F(); printf("OK\n")
	

void test()
{	
	TEST(test_grid_index_of);
	TEST(test_grid_index_of_2);
	TEST(test_grid_iter);
	TEST(test_grid_iter_along_ray);
	TEST(test_grid_iter_along_ray_no_hit);
	TEST(test_grid_iter_along_ray_border_away);
	TEST(test_grid_iter_along_ray_total_miss_grid);	
	TEST(test_fintersect2_aabb);
	TEST(test_fintersect_aabb_miss);
	TEST(test_fintersect_aabb);
	TEST(test_rotate);
	TEST(test_fintersect_plane);
	TEST(test_parallelogram);
	TEST(test_parallelogram2);
	//TEST(test_fintersect);
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
