#include "Triangle.h"

Triangle::Triangle(){
	p0 = {0, 0, 0};
	p1 = {0, 0, 0};
	p2 = {0, 0, 0};
	fill = {0, 0, 0};
}

Triangle::Triangle(Eigen::Vector3d a, Eigen::Vector3d b , Eigen::Vector3d c, Eigen::Vector3d f){
	p0 = a;
	p1 = b;
	p2 = c;
	fill = f;
}

Triangle::~Triangle(){

}

double Triangle::hit(Eigen::Vector3d eye, Eigen::Vector3d dir){
	//this section was taken from page 79 of textbook
	// setting up variables from textbook
	dir = dir.normalized();
	
	double a = p0[0] - p1[0];
	double b = p0[1] - p1[1];
	double c = p0[2] - p1[2];
	double d = p0[0] - p2[0];
	double e = p0[1] - p2[1];
	double f = p0[2] - p2[2];
	double g = dir[0];
	double h = dir[1];
	double i = dir[2];
	double j = p0[0] - eye[0];
	double k = p0[1] - eye[1];
	double l = p0[2] - eye[2];
	
	double M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
	
	//compute t	
	double t = -1*(f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c))/M;
	if(t < 1) return 0;
	
	double alpha = (i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c))/M;
	if(alpha < 0 or alpha > 1) return 0;
	
	double beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g))/M;
	if(beta < 0 or beta > (1 - alpha)) return 0;
		
	return t;
}

Eigen::Vector3d Triangle::getPoint(int choice){
	switch(choice) {
		case 0:
			return p0;
			break;
		case 1:
			return p1;
			break;
		case 2:
			return p2;
			break;
		default:
			return {0,0,0};
	}
}
	

