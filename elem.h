// element
#ifndef ELEM_H
#define ELEM_H

#include <vector>
#include <memory>

#include "ray.h"
#include "color.h"


class Elem {
	public:
	virtual void fintersect(Real &f, Ray &y) = 0;
	virtual void normal(Vector &n, Point &p) = 0;
	virtual Color& color() = 0;
	
};

typedef std::unique_ptr<Elem> ElemPtr;
typedef std::vector<ElemPtr> Elems;

#endif
