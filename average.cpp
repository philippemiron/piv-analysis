#include "include.hpp"
#include "tecplotio.hpp"
#include "matrix.hpp"
#include "stats.hpp"
#include "diffint.hpp"

std::string filein, fileout;

int main()
{
	// Parameters
	std::string prefixe = "data/champ";
	std::string suffixe = ".dat";
	int first_filenumber = 1;
	int N = 20;
	int Nx = 71;
	int Ny = 39;
	
	// Create arrays
	double** x = Construct2D(Ny, Nx);
	double** y = Construct2D(Ny, Nx);
	double*** u = Construct3D(N, Ny, Nx);
	double*** v = Construct3D(N, Ny, Nx);

	// Read the velocities of all the fields
	for (int i=0; i<N; i++)
	{
		// Get the filename
		filein = Filename(prefixe, suffixe, i+first_filenumber);
		// Read and fill up the arrays
		Read_Tp2D_Velocities(filein, Nx, Ny, i, x, y, u, v);
	}

	// Calculate the average
	double** u_avg = Construct2D(Ny, Nx);
	double** v_avg = Construct2D(Ny, Nx);
	Average(Nx, Ny, N, u, u_avg);
	Average(Nx, Ny, N, v, v_avg);
	
	// Write data
	fileout = "./average.plt";
	Write_Tp2D_AvgVelocities(fileout, Nx, Ny, x, y, u_avg, v_avg);
	
	// Delete arrays created
	Destruct2D(x);
	Destruct2D(y);
	Destruct3D(u);
	Destruct3D(v);
	Destruct2D(u_avg);
	Destruct2D(v_avg);
	
	return 0;
}
