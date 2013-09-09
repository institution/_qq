// geometric algebra
#include "ga.h"

void rotor(Rotor &r, const Bivect &nplane, const Real angle) {
	
	Real nsha = - sin(angle/2.0);   // neg sin half-angle
	r.e12 = nplane.e12 * nsha;
	r.e13 = nplane.e13 * nsha;
	r.e23 = nplane.e23 * nsha;
	
	r._1 = cos(angle/2.0);
}


void rotate(Vector &w, const Rotor &r, const Vector &a) {

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

void rotate(Bivect &w, const Rotor &a, const Bivect &b) {

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
