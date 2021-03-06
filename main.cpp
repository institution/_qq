#include <iostream>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <SDL/SDL.h>

#include "ga.hpp"

#include "rt.hpp"

#include "cam.hpp"

using namespace std;

namespace pt = boost::posix_time;

pt::ptime t_start = pt::microsec_clock::local_time(); 


uint width = 500, height = 500; 

#define BPP 4
#define DEPTH 32


double rand1() {
	return (((double)std::rand()) / RAND_MAX);
}

double rand2(float a, float b) {
	return (((double)std::rand()) / RAND_MAX) * (b-a) + a;
}





void create_world(Grid &gr, int n) {

	
	
	Sphere  * s = nullptr;
	
	/*
	  
	Real a=2.0, b=1.5, c=1.0, t=2.8;
	 
	s = new Sphere();
	s->center(10.0, a+b+b+c-t-1.0, 0).radius(c).fr();
	mov(s->col, white);
	xs.push_back(ElemPtr(s));
	
	
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
	mov(s->col, red);
	(*s).center(9.06, a+b+b+c-t-1.1, 0).radius(.15).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere(); 
	mov(s->col, black);
	(*s).center(9.15, a+b+b+c-t-0.8, +0.4).radius(.1).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	mov(s->col, black);
	(*s).center(9.15, a+b+b+c-t-0.8, -0.4).radius(.1).fr();
	xs.push_back(ElemPtr(s));
	
	s = new Sphere();
	(*s).center(10, -50000-t-a+1, 0).radius(50000).fr();
	xs.push_back(ElemPtr(s));
	*/
	/*
	for (int i=0; i<100; ++i) {
		s = new Sphere();
		(*s).center(
			10 + rand1()*100.0, 
			10 + rand1()*100.0, 
			10 + rand1()*100.0
		).radius(2).fr();
		xs.push_back(ElemPtr(s));
	}
	*/
	s = NULL;
	
	/*Parallelogram *p = new Parallelogram();
	(*p).pos(10, -t, 3.5).a(0,1,0).b(0,0,1);
	xs.push_back(ElemPtr(p));
	p = NULL;*/

	
	
	AABB *aabb = nullptr;
	
	//aabb = new AABB(Vector<>(2,2,2), Point<>(10,-t,6));
	//xs.push_back(ElemPtr(aabb));
	
	Vector<> l = gr.ab().a();
	Vector<> u = gr.ab().b();
	
	for (int i=0; i < n; ++i) {
		
		Point<> pos(
			rand2(l[0], u[0]), 
			rand2(l[1], u[1]), 
			rand2(l[2], u[2])
		);
		
		aabb = new AABB(
			Vector<>(1,1,1),
			pos
		);
		
		
		Vector<int> rr = gr.index_of(pos);
		Elems& xs = gr.get(rr);
				
		xs.push_back(ElemPtr(aabb));
	}
	
	aabb = NULL;
	
	
}




void putcolor(ostream &out, Color &c) {
	out.put((byte)(c.r*255.0));
	out.put((byte)(c.g*255.0));
	out.put((byte)(c.b*255.0));	
}


void render_ppm(ostream &out, Cam &c, Grid &gr) {
	
	uint width = 600, height = 600; 
	uint maxval = 255;
	
	out << "P6" << " " 
	    << width << " "
	    << height << " "
	    << 255 << endl;
	
	Color rcol;
	int j = height;
	int i;
	while (j > 0) {
		j -= 1;
		
		i = 0;
		while (i < width) {
				
			c.render_pixel(rcol, i, j, gr);	
			putcolor(out, rcol);

			//putcolor(black);
			i += 1;
		}
		
		/*
		i = 0;		
		while (i < width) {
			putcolor(black);
			i += 1;
		}
		*/
	}
}


double get_time() {
	pt::ptime now = pt::microsec_clock::local_time();
	pt::time_duration diff = now - t_start;
	return diff.total_milliseconds() / 1000.0;
}

int main_ppm(int argc, char* argv[]) {
	auto gr = Grid::box_res(
		Aabb(Vector<>(0,0,0), Vector<>(100,100,100)), 
		Vector<>(10,10,10)
	);
	
	create_world(gr, 100);
	
	
	
	
	
	Real fov_side = 45.0, fov_down=45.0;
	
	Cam c(width, height, fov_side, fov_down);	
	mov(c.pos, 0,0.1,0);
	rotor(c.rot, Bivect<>(0,1,0), (Real)(30.0 * (M_PI/180.0)));
	
	
	float t = get_time();
	
	render_ppm(cout, c, gr);
	
	cerr << "render time: " <<  get_time() - t << endl;

}


void setpixel(SDL_Surface *screen, int x, int y, const Color &c)
{
	Uint8 r = c.r*255.0;
	Uint8 g = c.g*255.0;
	Uint8 b = c.b*255.0;
	
    Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( screen->format, r, g, b );
  
    pixmem32 = (Uint32*) screen->pixels  + ((screen->h - y) * screen->w) + x;
    *pixmem32 = colour;
}



void render_sdl(SDL_Surface *screen, Cam &c, Grid &gr) {
	
	
	if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) {
			return;
		}
    }

	
	Color rcol;
	
	int x, y;
	
	y = screen->h;
	while(y > 0) 
    {
		y -= 1;
		
        //ytimesw = y*screen->pitch/BPP;
        x = 0;
        while(x < screen->w) 
        {
			
			c.render_pixel(rcol, x, y, gr);	
			
			setpixel(screen, x, y, rcol);
	
			x += 1;
        }
    }
    
	
    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  
    SDL_Flip(screen); 
    
    
}


string get_filename(const string& name, const string& ext){
	string fn;
	
	for (int i=0; i<100; ++i) {
		fn = name + to_string(i) + ext;
		
	    ifstream testfile(fn);
		
		if (!testfile.good())
		{
			return fn;
		}
		
	}
	
	return "";  
}

void take_screenshoot(Cam &c, Grid &gr) {
	string s = get_filename("a", ".ppm");
	if (!s.empty()) {
		ofstream of(s);
		render_ppm(of, c, gr);
		of.close();
		cerr << "screenshoot saved to " << s << " ";
	}
	else 
		cerr << "cant take screenshoot; no filename avaible" << endl;
}


int main()
{
	
	Grid gr = Grid::box_res(
		Aabb(Vector<>(0,0,0), Vector<>(100,100,100)), 
		Vector<>(4,4,4)
	);
	
	create_world(gr, 20);
	
	cout << "create world ok..." << endl;

	GridIter it(gr);
	Elem *x;
	while (x = it.next()) {
		cout << x->color() << endl;
	}
	
	cout << "listing ok..." << endl;
	
	
	Real fov_side = 45.0, fov_down=45.0;
	
	Cam c(width, height, fov_side, fov_down);	
	mov(c.pos, 0,0.1,0);
	rotor(c.rot, Bivect<>(0,1,0), (Real)(30.0*(M_PI/180)));
	

    SDL_Surface *screen;
    SDL_Event event;
  
    int keypress = 0;
    int h=0; 
  
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(width, height, DEPTH, SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }
  
	SDL_WM_SetCaption("Simple Window", "Simple Window");
  
	int licz = 0;
	double ttime = 0, stime = 0, dtime = 0;
	
	double take_screenshoot_timeout = 0.0;
	
	int numkeys;
	Uint8 *keys = SDL_GetKeyState(&numkeys);

    while(!keypress) 
    {
		if (take_screenshoot_timeout >= 1.0) 
		{			
			take_screenshoot(c, gr);			
		}
		
		
		
		stime = get_time();

		render_sdl(screen, c, gr);

		licz += 1;
		dtime = get_time() - stime;
		ttime += dtime; 
		
		if (take_screenshoot_timeout > 0.0)
			take_screenshoot_timeout -= dtime;

		if (!(licz % 50)) {
			cerr << "fps: " << (licz/ttime) << endl;
			ttime = 0;
			licz = 0;
		}

		Real speed = 8.0;

		Vector<> tmp;
		if (keys[SDLK_a]) {
			c.local(tmp, Vector<>(0,0,-speed * dtime));
			c.move(tmp);
		}
		
		if (keys[SDLK_d]) {
			c.local(tmp, Vector<>(0,0,speed * dtime));
			c.move(tmp);
		}
		
		if (keys[SDLK_w]) {
			c.local(tmp, Vector<>(speed* dtime,0,0));
			c.move(tmp);
		}
		
		if (keys[SDLK_s]) {
			c.local(tmp, Vector<>(-speed * dtime,0,0));
			c.move(tmp);
		}
		
		Rotor<> rr;
		
		if (keys[SDLK_LEFT]) {
			rotor(rr, Bivect<>(0,1,0), -5 * (M_PI/180));
			c.rotate(rr);
		}
		
		if (keys[SDLK_RIGHT]) {
			rotor(rr, Bivect<>(0,1,0), 5 * (M_PI/180));
			c.rotate(rr);
		}
		
		
		Bivect<> bb;
		
		
		if (keys[SDLK_UP]) {
			mov(bb, c.local(Bivect<>(1,0,0)));
			normalize(bb, bb);
			
			rotor(rr, bb, 5 * (M_PI/180));
			c.rotate(rr);
		}
		
		if (keys[SDLK_DOWN]) {
			mov(bb, c.local(Bivect<>(1,0,0)));
			normalize(bb, bb);
			
			rotor(rr, bb, -5 * (M_PI/180));
			c.rotate(rr);
		}
		
		
		
		while(SDL_PollEvent(&event)) 
		{      
			switch (event.type) 
			{
				case SDL_QUIT:
					keypress = 1;
					break;

				case SDL_MOUSEMOTION:
					
					rotor(rr, Bivect<>(0,1,0), event.motion.xrel * (M_PI/180));
					c.rotate(rr);
					
					
					mov(bb, c.local(Bivect<>(1,0,0)));
					normalize(bb, bb);
					
					rotor(rr, bb, -event.motion.yrel * (M_PI/180));
					c.rotate(rr);
					
					break;
					
				case SDL_KEYDOWN:
					// SDL_KEYUP
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						keypress = 1;
					}
					
					if (event.key.keysym.sym == SDLK_F5) {
						take_screenshoot_timeout = 1.0;						
					}
				
			}	
		}
	}
	
    

    SDL_Quit();
  	

    return 0;
}






