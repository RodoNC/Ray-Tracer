#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.h"

class Sphere: public Surface {
public:
	Sphere();
	Sphere(Eigen::Vector3d, double);
	~Sphere();
	virtual double hit(Eigen::Vector3d, Eigen::Vector3d);
	Eigen::Vector3d getCenter();
	double getRadius();
private:
	double dist(Eigen::Vector3d);
	Eigen::Vector3d center;
	double radius;
};
#endif
