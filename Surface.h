#ifndef SURFACE_H
#define SURFACE_H

#include <cmath>
#include <iostream>
#include <Eigen/Dense>

// base class for all surfaces
class Surface{
public:
	Surface();
	Surface(Eigen::Vector3d);
	virtual ~Surface();
	virtual double hit(Eigen::Vector3d, Eigen::Vector3d) = 0;
	Eigen::Vector3d getFill();
protected:
	Eigen::Vector3d fill;
};
#endif
