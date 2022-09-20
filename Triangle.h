#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Surface.h"

class Triangle: public Surface {
public:
	Triangle();
	Triangle(Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d);
	~Triangle();
	virtual double hit(Eigen::Vector3d, Eigen::Vector3d);
	Eigen::Vector3d getPoint(int);
private:
	Eigen::Vector3d p0;
	Eigen::Vector3d p1;
	Eigen::Vector3d p2;
};
#endif
