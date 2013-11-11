#include "grid.hpp"

IterElem<IterCellAlongRay> Grid::iter_along_ray(Ray & y){
	return IterElem<IterCellAlongRay>(IterCellAlongRay(*this, y));	
}


IterElem<IterCell> Grid::iter_all(){
	return IterElem<IterCell>(IterCell(*this));	
}