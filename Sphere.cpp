#include "Sphere.h"

double Sphere::dist(Eigen::Vector3d v){
	return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
}


Sphere::Sphere(){
	center = {0,0,0};
	radius = 0;
}

Sphere::Sphere(Eigen::Vector3d c, double r){
	center = c;
	radius = r;
}

Sphere::~Sphere(){

}

double Sphere::hit(Eigen::Vector3d eye, Eigen::Vector3d dir){

	Eigen::Vector3d e_min_c = eye - center;
	
	Eigen::Vector3d d = dir.normalized();
	
	double descrim = 4 * (pow(d.dot(e_min_c), 2) - d.dot(d) * (e_min_c.dot(e_min_c) - pow(radius, 2)));
	if(descrim < 0) return 0;
	
	return 10;//(-d.dot(e_min_c) - std::sqrt(descrim)) / pow(d, 2);
}

Eigen::Vector3d Sphere::getCenter(){
	return center;
}

double Sphere::getRadius(){
	return radius;
}
