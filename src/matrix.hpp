#ifndef _matrix_
#define _matrix_

#include "include.hpp"

double** Construct2D(int Nx, int Ny);
void Destruct2D(double** x);

double*** Construct3D(int Nx, int Ny, int Nz);
void Destruct3D(double*** x);

double**** Construct4D(int Nx, int Ny, int Nz, int N);
void Destruct4D(double**** x);

template<typename T> using vector2d = std::vector<std::vector<T>>;
template<typename T> using vector3d = std::vector<std::vector<std::vector<T>>>;
void Resize(vector2d<double> &vec, int N1, int N2); 
void Resize(vector3d<double> &vec, int N1, int N2, int N3);
void Resize(vector2d<int> &vec, int N1, int N2); 
void Resize(vector3d<int> &vec, int N1, int N2, int N3);

#endif