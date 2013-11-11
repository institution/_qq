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





class IterCellAlongRay;
class IterCell;

template <class C> class IterElem;

class Grid {
	vector<Elems> _space;
	
	Aabb _ab;        // bound
	Vector<> _res;   // resolution
	Vector<> _cdim;
	Vector<> _bidx;  // base index
		
public:
	Grid() {}
	
	Grid(const Aabb& box, const Vector<>& res) {
		ab_res(box, res);
	}
	
	static Grid box_res(const Aabb& box, const Vector<>& res) {
		return Grid(box, res);
	}
	
	// getters
	
	// axis-aligned bounding box
	inline const Aabb& ab() const { return _ab; }	
	inline const Aabb& aabb() const { return _ab; }	
	inline const Aabb& box() const { return _ab; }
	
	// resolution
	inline const Vector<>& res() const { return _res; }
	
	// cell dimension
	inline const Vector<>& cdim() const { return _cdim; }
	
	// cells array
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
	
	Vector<int> index_of(const Vector<>& p) const {
		Vector<> ref;		
		vdiv(ref, p, _cdim);
		sub(ref, ref, _bidx);		
		return Vector<int>(floor(ref[0]), floor(ref[1]), floor(ref[2]));
	}
	
	Aabb get_cell_aabb(Vector<int> cellind) {
		Vector<> low, upp;
		
		vmul(low, _cdim, Vector<float>(cellind));
		::add(low, low, _ab.lower());
		::add(upp, low, _cdim);
		
		return Aabb(low, upp);
	}
	
	bool is_bound(const Vector<int>& ind) const {
		
		if (!vle(Vector<int>(0,0,0), ind))
			return false;
		
		if (!vlt(ind, Vector<int>(_res[0], _res[1], _res[2])))
			return false;
		
		return true;
	}
	
	
		
	~Grid() {
		for (int i=0; i<_space.size(); ++i) {
			_space[i].clear();
		}
	}
	
	// iterators
	IterElem<IterCellAlongRay> iter_along_ray(Ray & y);
	IterElem<IterCell> iter_all();
	
};



class IterCell{
	Grid& grid_;
	int indcell_;
	
public:
	IterCell(Grid& gr): grid_(gr), indcell_(0) {
		
	}
		
	typedef Elems* type;
	
	Elems* next() {
		// return next (not yet returned) cell in grid in undefined order
		auto& cs = grid_.cells();
			
		// iter over cells
		while (indcell_ < cs.size()) 
		{				
			return &cs[indcell_++];			
		}
				
		return nullptr;		
	}
	
	
};



class IterCellAlongRay {
	// refs
	Ray  &ray_ ;  // ray ref
	Grid &grid_;  // grid ref
	
	// state
	Vector<int> cellind_;
	bool cellind_valid_;   
	Real minf_, maxf_;

	
public:
	
	IterCellAlongRay(Grid &grid, Ray &ray): grid_(grid), ray_(ray) {

		// find first cell ind
		Real f1, f2;
		fintersect2_aabb(f1, f2, grid_.aabb(), ray_);
		
		if (f2 < INF) {
			auto f = (0 < f1) ? f1 : (Real)0;
			auto p = ray_.point_at(f + 0.01);			
			cellind_ = grid_.index_of(p);			
		}
		else {
			cellind_ = Vector<int>(-1, -1,-1);
		}
	}
	
	typedef Elems * type;
	
	Elems * next() {
		// return next cell along ray
		Elems * ret;
		
		if (grid_.is_bound(cellind_)) {
			// ret val
			ret = &grid_.get(cellind_);
			
			// alter state
			auto cbox = grid_.get_cell_aabb(cellind_);
						
			Real f1, f2;
			fintersect2_aabb(f1, f2, cbox, ray_);

			if (f2 < INF) {

				auto p = ray_.point_at(f2 + 0.01);
				
				auto new_cellind = grid_.index_of(p);	
				
				assert(!eq(new_cellind, cellind_));
				cellind_ = new_cellind;
			}
			else {
				cellind_ = Vector<int>(-1,-1,-1);
			}

		}
		else {
			ret = nullptr;			
		}
		
		return ret;
	}	
	
};



template <class C>
class IterElem {
	C icells_;
	int indelem_;
	Elems* currcell_;

public:

	IterElem(C icells): icells_(icells) {
		indelem_ = 0;
		currcell_ = icells_.next();
	}

	typedef Elem* type;

	Elem* next() {
		// return next (not yet returned) element in grid in undefined order

		// iter over cells
		while (currcell_) {

			// iter over elements
			while (indelem_ < currcell_->size()) {
				return ((*currcell_)[indelem_++]).get();
			}

			indelem_ = 0;			
			currcell_ = icells_.next();
		}

		return nullptr;
	}


};






// old iter
class GridIter {
	IterCell icells_;
	int indelem_;
	Elems* currcell_;
	
public:
	
	GridIter(Grid& gr): icells_(gr) {
		indelem_ = 0;
		currcell_ = icells_.next();
	}
	
	typedef Elem* type;
	
	Elem* next() {
		// return next (not yet returned) element in grid in undefined order
			
		// iter over cells
		while (currcell_) {
		
			// iter over elements
			while (indelem_ < currcell_->size()) {
				return ((*currcell_)[indelem_++]).get();
			}
			
			indelem_ = 0;			
			currcell_ = icells_.next();
		}
				
		return nullptr;
	}
	
	
};


#endif
