// grid
#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <vector>
#include <limits>
#include <memory>
#include <string>

#include "ga.hpp"
#include "ioga.hpp"
#include "defs.hpp"
#include "elem.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "aabb.hpp"
#include "intersect.hpp"

extern Real INF;


class Grid {
	vector<Elems> _space;
	
	Aabb _ab;        // bound
	Vector<> _res;   // resolution
	Vector<> _cdim;
	Vector<> _bidx;  // base index
		
public:
	Grid() {}
	
	
	// getters
	inline const Aabb& ab() const { return _ab; }	
	inline const Aabb& aabb() const { return _ab; }	
	inline const Vector<>& res() const { return _res; }
	inline const Vector<>& cdim() const { return _cdim; }
	inline const vector<Elems>& cells() const { return _space; }
	inline vector<Elems>& cells() { return _space; }
	
	// setters
	inline Grid& ab_res(const Aabb& ab, const Vector<>& res) {
		_ab = ab;
		_res = res;
		vdiv(_cdim, ab.b() - ab.a(), res);
		
		assert(vlt(ab.a(), ab.b()));
		
		vdiv(_bidx, ab.a(), _cdim);
		
		
		_space.resize(res[0]*res[1]*res[2]);
		return *this;
	}
	inline Grid& res_ab(const Vector<>& res, const Aabb& ab) {
		return ab_res(ab, res);
	}
		
	
	Elems& get(const Vector<int>& ref) {
		
		assert(vle(Vector<int>(0,0,0), ref));
		assert(vlt(ref, Vector<int>(_res[0], _res[1], _res[2])));
		
		int ind = ref[0] + ref[1]*_res[0] + ref[2]*_res[0]*_res[1];
		
		assert(ind < _space.size());
		
		return _space[ind];
	}
	
	void add(Vector<> &p, Elem *e) {
		Elems& es = get(index_of(p));
		es.push_back(ElemPtr(e));
	}
	
	Vector<int> index_of(const Vector<>& p) {
		Vector<> ref;		
		vdiv(ref, p, _cdim);
		sub(ref, ref, _bidx);		
		return Vector<int>(ref[0], ref[1], ref[2]);
	}
	
	Aabb get_cell_aabb(cellind) {
		Vector<> low, upp;
		
		mul(low, _cdim, cellind);
		add(low, low, _ab.lower());
		add(upp, low, _cdim);
		
		return Aabb(low, upp);
	}
	
	bool is_bound(const Vector<int>& ind) {
		
		if (!vle(Vector<int>(0,0,0), ind))
			return false;
		
		if (!vlt(ref, Vector<int>(_res[0], _res[1], _res[2])))
			return false
		
		return true;
	}
	
	
		
	~Grid() {
		for (int i=0; i<_space.size(); ++i) {
			_space[i].clear();
		}
	}
	

	
};





class IterCell{
	Grid& grid_;
	int indcell_;
	
public:
	IterElem(Grid& gr): _gr(gr) {
		seek();
	}
	
	void seek() {
		indcell_ = 0; 		
	}
	
	
	Elem* next() {
		// return next (not yet returned) element in grid in undefined order
		
		auto& cellss = grid_.cells();
			
		// iter over cells
		while (_ic < cs.size()) 
		{				
			// iter over elements
			while (_ie < cs[_ic].size()) {
				auto ind_elem = _ie;
				++_ie;  // modify state before return
				// yield
				return cs[_ic][ind_elem].get();
			}
							
			_ie = 0;
			++_ic;
		}
				
		return nullptr;		
	}
	
	
};

class IterElem {
	Grid& _gr;
	int _ic, _ie;
	
public:
	IterElem(Grid& gr): _gr(gr) {
		seek();
	}
	
	void seek() {
		_ic = 0; 
		_ie = 0;
	}
	
	
	Elem* next() {
		// return next (not yet returned) element in grid in undefined order
		
		auto& cs = _gr.cells();
			
		// iter over cells
		while (_ic < cs.size()) 
		{				
			// iter over elements
			while (_ie < cs[_ic].size()) {
				auto ind_elem = _ie;
				++_ie;  // modify state before return
				// yield
				return cs[_ic][ind_elem].get();
			}
							
			_ie = 0;
			++_ic;
		}
				
		return nullptr;		
	}
	
	
};


class IterCellAlongRay {
	// refs
	const Ray  &ray_ ;  // ray ref
	const Grid &grid_;  // grid ref
	
	// state
	Vector<int> cellind_;
	bool cellind_valid_   
	Real minf_, maxf_;

	
public:
	IterCellAlongRay(Grid &grid, Ray &ray): grid_(grid), ray_(ray) {
		seek();
	}
	
	void seek() {
		minf_ = -INF; // may be inside, if outside then 0 is enougth
		maxf_ = +INF;
		
		// first cell
		fintersect2_aabb(f1, f2, grid_.aabb(), ray_);
		
		if (f2 < INF) {
			Point<> p;
			point_on_ray(p, ray_, f1 + 0.01);
			
			Point<int> cellind = grid_.index_of(p);	
			
			cell_ = &grid_.get(cellind);
		}
		else {
			// outside
			cell_ = nullptr;
		}
	}
	
	
	Elem* next() {
		// return next cell along ray
		Elems * curr = cell_;
		
		
		// first cell
		fintersect2_aabb(f1, f2, grid_.get_cell_aabb(cellind), ray_);
		
		if (f2 < INF) {
			Point<> p;
			point_on_ray(p, ray_, f1 + 0.01);
			
			Point<int> cellind = grid_.index_of(p);	
			
			cell_ = &grid_.get(cellind);
		}
		else {
			// outside
			cell_ = nullptr;
		}
	}
	
	
};



#endif
