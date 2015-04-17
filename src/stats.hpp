#include "include.hpp"

void Average(int Nx, int Ny, int N, double*** x, double** x_avg);
void Average(int Nx, int Ny, int N, double*** x, double*** y, double** xy_avg);
double Average(int N, double* x);
void RMS(int Nx, int Ny, double** velocity, double** velocity_squared, double** rms);
void RMS(int Nx, int Ny, double** u, double** v, double** uv, double** rms);