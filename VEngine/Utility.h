#ifndef UTILITY_H
#define UTILITY_H

#include <boost\foreach.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <boost\lexical_cast.hpp>

#define vDebug std::cout
#define vMin(a,b) ((a < b) ? a : b )
#define vMax(a,b) ((a > b) ? a : b )
#define vContains(val, min, max) ((val >= min) && (val <= max))



void vWarning(const std::string&);

#define vError vWarning

template<typename T>
T StringTo(std::string val) { return boost::lexical_cast<T>(val); }
inline std::string ConvertToString(double val) { return boost::lexical_cast<std::string>(val); }

std::vector<char> FileToBuffer(const std::string filename);

const std::string SCRIPTS("Scripts/");
const std::string IMAGES("Images/");
const std::string SOUNDS("Sounds/");

struct ColRow 
{ 
	ColRow(size_t _col  = 0, size_t _row = 0): col(_col), row(_row) {} 
	size_t col, row; 
};

ColRow GetColRow(size_t cols, size_t id);
#endif