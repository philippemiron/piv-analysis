// List of statistics function
#include "stats.hpp"

// Calculate the average of a variable
void Average(int Nx, int Ny, int N, double*** x, double** x_avg) {
	
	// Add all the values
	for (int k=0; k < N; k++)
		for (int j=0; j < Ny; j++)
			for (int i=0; i < Nx; i++)
				x_avg[j][i] += x[k][j][i];	
				            
	
	// Divide by the number of measurements
	for (int j=0; j < Ny; j++)
		for (int i=0; i < Nx; i++)
			x_avg[j][i] /= (double) N;
}

void RMS(int Nx, int Ny, int N, double*** vitesse, double*** fluctuation, double** moyenne, double** variance) {
	
	// Soustrait la moyenne au champs de vitesse
	// RMS = fluctiations^2
	for (int i=0; i<Nx; i++) {
		for (int j=0; j < Ny; j++) {
			for (int k=0; k < N; k++)
			{
      		fluctuation[i][j][k] = vitesse[i][j][k] - moyenne[i][j];
      		variance[i][j] += pow(fluctuation[i][j][k],2);	
			}
		}
	}
	// Divise par le nombre de valeurs
	for (int i=0; i<Nx; i++)
		for (int j=0; j < Ny; j++)
				variance[i][j] /= N;
}
