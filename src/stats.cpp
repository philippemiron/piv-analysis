// List of statistics function
#include "stats.hpp"

// Calculate the average of a variable
void Average(int Nx, int Ny, int N, double*** x, double** x_avg) {
	
	// Add all the values
	for (int i=0; i < N; i++)
		for (int j=0; j < Ny; j++)
			for (int k=0; k < Nx; k++)
				x_avg[j][k] += x[i][j][k];	
				            
	
	// Divide by the number of measurements
	for (int i=0; i < Ny; i++)
		for (int j=0; j < Nx; j++)
			x_avg[i][j] /= (double) N;
}

// Calculate the average of a variable
void Average(int Nx, int Ny, int N, double*** x, double*** y, double** xy_avg) {
	
	// Add all the values
	for (int i=0; i < N; i++)
		for (int j=0; j < Ny; j++)
			for (int k=0; k < Nx; k++)
				xy_avg[j][k] += x[i][j][k]*y[i][j][k];	
				            
	
	// Divide by the number of measurements
	for (int i=0; i < Ny; i++)
		for (int j=0; j < Nx; j++)
			xy_avg[i][j] /= (double) N;
}

void RMS(int Nx, int Ny, double** velocity, double** velocity_squared, double** rms) {
	
	// RMS = sqrt(fluctuations^2)
   for (int i=0; i < Ny; i++) {
			for (int j=0; j < Nx; j++)
			{
      		    rms[i][j] = velocity_squared[i][j] - pow(velocity[i][j], 2.0);
			}
	}
}

void RMS(int Nx, int Ny, double** u, double** v, double** uv, double** rms) {
	
	// RMS = sqrt(fluctuations^2)
   for (int i=0; i < Ny; i++) {
			for (int j=0; j < Nx; j++)
			{
      		    rms[i][j] = uv[i][j] - u[i][j]*v[i][j];
			}
	}
}
