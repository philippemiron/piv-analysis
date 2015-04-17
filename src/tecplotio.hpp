#include "include.hpp"
#include "TECIO.h"

void Read_Tp2D_Velocities(string file, int Nx, int Ny, int k, double** x, double** y, double*** u, double*** v);
void Read_Tp2D_Average(string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** uv, double** u2, double** v2);
void Read_Tp2D_Average(string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** w, double** uv, double** uw, double** vw, double** u2, double** v2, double** w2);
string Filename(string prefixe, string suffixe, int numero);
void Read_Signal(string file, int N, double* u, double* v);
void Read_FFT(string file, int N, double* fft_u, double* fft_v);

// Binary function
void Write_Tp2D_AvgVelocities(string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** up, double** vp, double** uvp);
void Write_Tp2D_AvgVelocities(string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** w, double** up, double** vp, double** wp, double** uvp, double** uwp, double** vwp);
void Write_Tp2D_Q(string file, int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);
void Write_Tp2D_Q2(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q);

// Fields to points format (ASCII)
void Write_Points(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v);

// Write FFT
void Write_FFT(string filename, int Fs, int N, double* fft_u, double* fft_v);
void Write_FFT_plan(string filename, int Fs, int length, int N, double** fft_u, double** fft_v);