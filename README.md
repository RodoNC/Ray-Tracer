Ray Tracer

Project written in c++
Uses Eigen Library

Outside sources used:
I used this source to learn how to use Eigen vector
https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
I also used various c++ websites to look up functions in the standard library
No other outside sources were used, all the math was either from the class lectures or the textbook

In this project we create a simple raytracer that reads an nff file to create a ppm file image

The nff file contains details about the camera such as location and view direction,
and the scene such as background color and the surfaces to be rendered

The first part of the project parses through the nff file to get details about the camera and scene

Then we set up variable to make it easy to go from camera coordinates to world coordiantes

The actual raytracing algorithm consists of generating a ray for each pixel and setting that
pixel's color to either background or fill color depending on hit or miss of a surface

Both the hit detection for triangle and spheres are from textbook

Note: spheres has problems

run "make proj1" to build
run "make run" to run with tetra-3.nff and output to output.ppm

From teapot-3.nff
![alt text](https://github.com/RodoNC/Ray-Tracer/blob/main/tea.png)
From tetra-3.nff
![alt text](https://github.com/RodoNC/Ray-Tracer/blob/main/output.png)
