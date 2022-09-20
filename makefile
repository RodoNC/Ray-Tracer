proj1: Triangle.o Sphere.o Surface.o proj1.cpp
	g++ -O3 -I /usr/include/eigen3/ Triangle.o Sphere.o Surface.o proj1.cpp -o proj1

Triangle.o: Triangle.h Triangle.cpp Surface.o
	g++ -O3 -I /usr/include/eigen3/ -c Triangle.cpp

Sphere.o: Sphere.h Sphere.cpp Surface.o
	g++ -O3 -I /usr/include/eigen3/ -c Sphere.cpp
	
Surface.o: Surface.h Surface.cpp
	g++ -O3 -I /usr/include/eigen3/ -c Surface.cpp
	
run: 
	./proj1 tetra-3.nff

val:
	valgrind ./proj1 tetra-3.nff
