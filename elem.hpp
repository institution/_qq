// element
#ifndef ELEM_HPP
#define ELEM_HPP

#include <vector>
#include <memory>
#include <string>

#include "ray.hpp"
#include "color.hpp"


class Elem {
	public:
	virtual void fintersect(Real &f, Ray &y, Real max_f) = 0;
	virtual void normal(Vector<> &n, Point<> &p) = 0;
	virtual Color& color() = 0;
};

typedef std::shared_ptr<Elem> ElemPtr;
typedef std::vector<ElemPtr> Elems;

#endif
