#include "cam.h"


void Cam::render_pixel(Color &col, int i, int j, Elems &xs) {
	
	/*
	Real hor_angle = (i - hwidth) * fov_side/hwidth;
	Real ver_angle = (j - hheight) * fov_down/hheight;
	
	Rotor hor_r, ver_r;
	rotor(hor_r, Bivect(0,1,0), hor_angle);
	rotor(ver_r, Bivect(1,0,0), ver_angle);
	
	Vector rd;
	mov(rd, dir);
	::rotate(rd, hor_r, rd);
	::rotate(rd, ver_r, rd);
	::rotate(rd, rot, rd);
	*/
	
	//Rotor r;
	//mul(r, ver_r, hor_r);
	//::rotate(rd, r, dir);
		
	
	Vector rd(
		scr_dist, 
		j - hheight, 
		i - hwidth
	);
	normalize(rd, rd);
	::rotate(rd, rot, rd);
	
							
	Ray ray;
	ray.dir(rd.x,rd.y,rd.z).pos(pos);
			
	trace(col, ray, xs);
	
}

