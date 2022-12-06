#pragma once

struct point_t
{
	point_t(): x(0.0), y(0.0) {}
	point_t(const double& x_, const double& y_) : x(x_), y(y_) {}
	point_t(const point_t& point) : x(point.x), y(point.y) {}

	double x;
	double y;
};

struct rectangle_t
{
	double width;
	double height;
	point_t pos;
};