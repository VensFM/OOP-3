#pragma once
#include <fstream> 

struct point_t;

void fixString(std::string& str);
void reloadStream(std::istream& stream);
void failEnter(std::istream& stream);
void failEnterForComposite(std::istream& stream);
void cleanValue(double& x);
bool getDouble(std::istream& stream, double& x);
bool getPoint(std::istream& stream, point_t& x);