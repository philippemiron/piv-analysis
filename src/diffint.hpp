#include "include.hpp"

void Derivative2D_x(int Nx, int Ny, int N, double delta, double*** x, double*** dx);
void Derivative2D_y(int Nx, int Ny, int N, double delta, double*** y, double*** dy);
void Vorticity(int Nx, int Ny, int N, double*** dvx, double*** duy, double*** w);
void QCriterion(int Nx, int Ny, int N, double*** dux, double*** duy, double*** dvx, double*** dvy, double*** q);