#ifndef UTILITY_H
#define UTILITY_H

#include <boost\foreach.hpp>
//include <Box2D\Box2D.h>
#include <iostream>
#include <string>

// Golds
struct ColRow 
{ 
	ColRow(size_t _col  = 0, size_t _row = 0): col(_col), row(_row) {} 
	size_t col, row; 
};

#define vMin(a,b) ((a < b) ? a : b )
#define vMax(a,b) ((a > b) ? a : b )
#define vContains(val, min, max) ((val >= min) && (val <= max))

void vWarning(const std::string&);
ColRow GetColRow(size_t cols, size_t id);
#endif