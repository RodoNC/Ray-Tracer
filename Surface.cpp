#include "Surface.h"

Surface::Surface(){
	fill = {0, 0, 0};
}

Surface::Surface(Eigen::Vector3d f){
	fill = f;
}

Surface::~Surface(){

}


Eigen::Vector3d Surface::getFill(){
	return fill;
}

