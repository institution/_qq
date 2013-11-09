// intersection algorithms
#include "intersect.hpp"

using namespace std;



// find intersection points beetween ray and aabb if any
void fintersect2_aabb(Real &f1, Real &f2, const Aabb &ab, const Ray &ray) {
	
	Point<> aap;
	sub(aap, ab.a(), ray.pos());
	
	Point<> bbp;
	sub(bbp, ab.b(), ray.pos());
	
	Real max_a = -INF, min_b = INF;
	Real vvi, a, b;
	
	
	for (int i = 0; i < 3; ++i) {
		
		vvi = (Real)(1.0) / ray._dir[i];
		
		if (vvi < 0)
	    {
			b = aap[i] * vvi;
			a = bbp[i] * vvi;
		}
		else // if (vvi > 0) 
		{
			a = aap[i] * vvi;
			b = bbp[i] * vvi;
		}
				
		if (a > max_a) {
			max_a = a;
		}
		
		if (b < min_b) {
			min_b = b;
		}
				
	}

	if (max_a <= min_b) {
		f1 = max_a;
		f2 = min_b;		
	} else {
		f1 = f2 = INF;
	}	
}



