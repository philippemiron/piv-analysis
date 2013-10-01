#include "include.hpp"
#include "TECIO.h"

void Read_Tp2D_Velocities(std::string file, int Nx, int Ny, int k, double** x, double** y, double*** u, double*** v);
std::string Filename(std::string prefixe, std::string suffixe, int numero);

// Binary function
void Write_Tp2D_AvgVelocities(std::string file, int Nx, int Ny, double** x, double** y, double** u, double** v);
void Write_Tp2D_Q(std::string file, int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);
void Write_Tp2D_Q2(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);

// Fields to points format (ASCII)
void Write_Points(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v);
