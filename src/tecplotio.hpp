#include "include.hpp"
#include "TECIO.h"

void Read_Tp2D_Velocities(std::string file, int Nx, int Ny, int k, double** x, double** y, double*** u, double*** v);
void Read_Tp2D_Average(std::string file, int Nx, int Ny, int k, double** x, double** y, double** u, double** v, double** uv, double** u2, double** v2);
std::string Filename(std::string prefixe, std::string suffixe, int numero);
void Read_Signal(std::string file, int N, double* u, double* v);

// Binary function
void Write_Tp2D_AvgVelocities(std::string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** up, double** vp, double** uvp);
void Write_Tp2D_Q(std::string file, int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);
void Write_Tp2D_Q2(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);

// Fields to points format (ASCII)
void Write_Points(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v);
void Write_FFT(int N, fftw_complex* u, fftw_complex* v);
