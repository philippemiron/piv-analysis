#include "include.hpp"
#include "tecplotio.hpp"
#include "matrix.hpp"
#include "stats.hpp"
#include "diffint.hpp"

string filein, fileout;

int main()
{
	// Parameters
	string prefixe = "data/champ";
	string suffixe = ".dat";
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
	
	// Write data for every point
	Write_Points(Nx, Ny, N, x, y, u, v);
	
	// Delete arrays created
	Destruct2D(x);
	Destruct2D(y);
	Destruct3D(u);
	Destruct3D(v);
	
	return 0;
}