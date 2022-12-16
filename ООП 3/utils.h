#pragma once
#include <fstream> 

struct point_t;

void reloadStream(std::istream& stream);
void failEnter(std::istream& stream);
void failEnterForComposite(std::istream& stream);
void cleanValue(double& x, int k);
bool getDouble(std::istream& stream, double& x);
bool getPoint(std::istream& stream, point_t& x);