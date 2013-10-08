// camera
#ifndef CAM_HPP
#define CAM_HPP

#include "ga.hpp"
#include "ray.hpp"
#include "elem.hpp"
#include "rt.hpp"



class Cam{
	public:
	Point<> pos;
	Rotor<> rot;
	Vector<> dir;
	
	uint width, height; 
	
	Real scr_dist, fov_side, fov_down;
	Real hheight, hwidth;
	
	
	Cam(int width_, int height_, float fov_side_=89.0, float fov_up_=60.0, float fov_down_=75.0) {
		
		fov_side = fov_side_ * M_PI/180.0;
		fov_down = fov_down_ * M_PI/180.0;
		
		width = width_;
		height = height_;
		
		hwidth = width*0.5; 
		hheight = height*0.5; 
		
		// tan(fov_side) = scr_HPPalf_width / scr_dist;
		// assume scr_HPPalf_width = h_width_pix
		scr_dist = hwidth / tan(fov_side);
		
		
		mov(pos, 0.0, 0.0, 0.0);
		mov(dir, 1.0, 0.0, 0.0);
		
		//normalize(cam_dir, cam_dir);
		
		
	}
	
	inline void local(Vector<> &r, const Vector<> &b) {
		::rotate(r, this->rot, b);
	}
	
	inline Bivect<> local(const Bivect<> &b) {
		Bivect<> r;
		::rotate(r, this->rot, b);
		return r;
	}
	
	
	inline void move(const Vector<> &v) {
		
		add(this->pos, this->pos, v);
	}	
	
	inline void rotate(const Rotor<> &r) {
		mul(this->rot, r, this->rot);
		
	}
	
	void render_pixel(Color &col, int i, int j, Elems &xs);
};


#endif
