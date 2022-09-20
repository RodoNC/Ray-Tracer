#include "Triangle.h"
#include "Sphere.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>


int main(int argc, char** argv){
	////////////////////////////////////////////////////////////////////////////////////////
	// get command line arguments
	std::string fname = "";
	std::string oname = "output.ppm";
	if(argc == 1){
		std::cout << "Please enter nff file" << std::endl;
		return 0;
	}
	if(argc == 3){
		oname = argv[2];		
	}
	
	
	////////////////////////////////////////////////////////////////////////////////////////
	// variables from nff file
	Eigen::Vector3d bgcolor = {0, 0, 0};
	Eigen::Vector3d from = {0, 0, 0};
	Eigen::Vector3d at = {0, 0, 0};
	Eigen::Vector3d up = {0, 0, 0};
	double fov = 0;
	double hither = 0;
	int xres = 0;
	int yres = 0;
	Eigen::Vector3d fill = {0, 0, 0};
	// list of surfaces
	std::vector<Surface*> surfaces;
	
	////////////////////////////////////////////////////////////////////////////////////////
	// parse through file
	std::string line;
	std::ifstream infile;
	infile.open(argv[1]);
	int pos, pos2, numP;
	Eigen::Vector3d p0, p1, p2 = {0, 0, 0};
	if(infile.is_open()){
		while (std::getline(infile, line)){
			switch (line[0]){
			// get background color
			case 'b':
				for(int ii = 0; ii <=2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					bgcolor[ii] = std::stof(line.substr(pos + 1, pos2));
					line = line.substr(pos + 1);
				}				
				break;
			// get viewpoint description
			case 'v':
				//get from
				std::getline(infile, line);
				for(int ii = 0; ii <=2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					from[ii] = std::stof(line.substr(pos + 1, pos2));
					line = line.substr(pos + 1);
				}
				//get at
				std::getline(infile, line);
				for(int ii = 0; ii <=2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					at[ii] = std::stof(line.substr(pos + 1, pos2));
					line = line.substr(pos + 1);
				}
				//get up
				std::getline(infile, line);
				for(int ii = 0; ii <=2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					up[ii] = std::stof(line.substr(pos + 1, pos2));
					line = line.substr(pos + 1);
				}
				//get fov
				std::getline(infile, line);
				pos = line.find(" ");
				fov = std::stof(line.substr(pos + 1));
				fov = M_PI * fov / 180;
				//get hitther
				std::getline(infile, line);
				pos = line.find(" ");
				hither = std::stof(line.substr(pos + 1));
				//get resolution
				std::getline(infile, line);
				pos = line.find(" ");
				pos2 = line.substr(pos + 1).find(" ");
				xres = std::stoi(line.substr(pos + 1, pos2));
				yres = std::stoi(line.substr(pos + pos2 + 1));
				break;
			//get fill
			case 'f':
				for(int ii = 0; ii <=2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					fill[ii] = std::stof(line.substr(pos + 1, pos2));
					line = line.substr(pos + 1);
				}
				break;
			//get surfaces
			case 'p':
				numP = (int)(line[2] - 48);
				//get p0
				std::getline(infile, line);
				for(int ii = 0; ii <= 2; ++ii){
					pos = line.find(" ");
					p0[ii] = std::stof(line.substr(0, pos));
					line = line.substr(pos + 1);
				}
				//get p1
				std::getline(infile, line);
				for(int ii = 0; ii <= 2; ++ii){
					pos = line.find(" ");
					p1[ii] = std::stof(line.substr(0, pos));
					line = line.substr(pos + 1);
				}
				//get p2
				std::getline(infile, line);
				for(int ii = 0; ii <= 2; ++ii){
					pos = line.find(" ");
					p2[ii] = std::stof(line.substr(0, pos));
					line = line.substr(pos + 1);
				}				
				surfaces.push_back(new Triangle(p0, p1, p2, fill));
				
				// if more than 3 points
				for(int hh = 0; hh <= numP - 4; ++hh){
					p1 = p2;
					std::getline(infile, line);
					//get next point
					for(int ii = 0; ii <= 2; ++ii){
						pos = line.find(" ");
						p2[ii] = std::stof(line.substr(0, pos));
						line = line.substr(pos + 1);
					}				
					surfaces.push_back(new Triangle(p0, p1, p2, fill));						
				}	
			
				break;
			// get spheres
			case 's':
				//get center point
				for(int ii = 0; ii <= 2; ++ii){
					pos = line.find(" ");
					pos2 = line.substr(pos + 1).find(" ");
					p0[ii] = std::stof(line.substr(pos + 1, pos2));
					std::cout << p0[ii] << " ";
					line = line.substr(pos + 1);
				}
				surfaces.push_back(new Sphere(p0, std::stod(line.substr(pos + 1, pos2))));
				break;
			default:
				break;
			}
		}
		infile.close();
	}
	else std::cout << "could not open file" << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Camera coordinates
	
	//this section was taken from in class
	Eigen::Vector3d tempv = from - at;
	Eigen::Vector3d w = tempv.normalized();
	Eigen::Vector3d u = up.cross(w).normalized();
	Eigen::Vector3d v = w.cross(u);
	double ar = xres/yres;
	//magnitude of from - at
	double d = sqrt(tempv[0] * tempv[0] + tempv[1] * tempv[1] + tempv[2] * tempv[2]);
	double h = 2 * d * std::tan(fov/2) / xres;
	
	
	////////////////////////////////////////////////////////////////////////////////////////
	// ray tracing part

	//vector for pixels
	std::vector<Eigen::Vector3d> im(xres * yres, {0,0,0});
	
	double t= 0;
	Eigen::Vector3d dir = {0,0,0};
	//go from topleft to bottom right
	for(int ii = 0; ii < yres; ++ii){
		for(int jj = 0; jj < xres; ++jj){
			double tempt = 0;
			//generate ray, math from in class
			//points to topleft pixel and moves from left to right top to bottom
			dir = (-d*tan(fov/2)+h/2+ii*h)*u+(d*tan(fov/2)/ar-h/2-jj*h)*v-d*w;
			
			//set to background color by default
			im[ii * xres + jj] = bgcolor;
			
		
			//check for intersection with all triangles
			int surfaceID = 0;
			for(int kk = 0; kk < surfaces.size(); ++kk){				
				//check hit
				tempt = surfaces[kk]->hit(from, dir);
				//returns smallest t
				if(tempt > hither){
					t = tempt;
					surfaceID = kk;
				}		
			}
			
			//set to fill on hit
			if(t > hither) im[ii * xres + jj] = surfaces[surfaceID]->getFill();	
			
			//set t back to 0 for next pixel
			t = 0;
		}
	}
	
	////////////////////////////////////////////////////////////////////////////////////////
	//write ppm file
	
	//write pixels from image
	unsigned char pixels[yres][xres][3];
	int counter = 0;
	for(int ii = 0; ii < xres; ++ii){
		for(int jj = 0; jj < yres; ++jj){
			pixels[jj][ii][0] = im.at(counter)[0] * 255;
			pixels[jj][ii][1] = im.at(counter)[1] * 255;
			pixels[jj][ii][2] = im.at(counter)[2] * 255;
			counter++;
		}
	}


	//code from example
	std::FILE *f = fopen(oname.c_str(),"wb");
	std::fprintf(f, "P6\n%d %d\n%d\n", xres, yres, 255);
	std::fwrite(pixels, 1, xres * yres * 3, f);
	std::fclose(f);

	
	
	//destructor
	for(int ii = 0; ii < surfaces.size(); ++ii){
		delete surfaces[ii];
		surfaces[ii] = nullptr;
	}
	
	return 0;
}
