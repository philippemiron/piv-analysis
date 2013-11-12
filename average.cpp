#include "include.hpp"
#include "tecplotio.hpp"
#include "matrix.hpp"
#include "stats.hpp"
#include "diffint.hpp"

std::string filein, fileout;

int main()
{
	// Parameters
	std::string prefixe = "/Users/phil/Dropbox/Ladyf/20131028-Test_meilleures_images(3x32x32_50ov)/B";
	std::string suffixe = ".dat";
	int first_filenumber = 1;
	int N = 1000;
	int Nx = 80;
	int Ny = 50;
	
// or
	
	// Create arrays
	double** x = Construct2D(Ny, Nx);
	double** y = Construct2D(Ny, Nx);
	double** u = Construct2D(Ny, Nx);
	double** v = Construct2D(Ny, Nx);
	double** uv = Construct2D(Ny, Nx);
	double** u2 = Construct2D(Ny, Nx);
	double** v2 = Construct2D(Ny, Nx);
	double** uv2 = Construct2D(Ny, Nx);

	// Read the velocities of all the fields
	for (int i=0; i<N; i++)
	{
		// Get the filename
		filein = Filename(prefixe, suffixe, i+first_filenumber);
		// Read and fill up the arrays
		Read_Tp2D_Average(filein, Nx, Ny, i, x, y, u, v, uv, u2, v2, uv2);
	}
	
	// Calculate the average
	for (int i=0; i < Ny; i++) {
		for (int j=0; j < Nx; j++) {
			u[i][j]  /= (double) N;
			v[i][j]  /= (double) N;
			uv[i][j]  /= (double) N;
			u2[i][j] /= (double) N;
			v2[i][j] /= (double) N;
			uv2[i][j] /= (double) N;
		}
	}
	
	// RMS
	double** u_rms = Construct2D(Ny, Nx);
	double** v_rms = Construct2D(Ny, Nx);
	double** uv_rms = Construct2D(Ny, Nx);
	RMS(Nx, Ny, u, u2, u_rms);
	RMS(Nx, Ny, v, v2, v_rms);
	RMS(Nx, Ny, uv, uv2, uv_rms);
	
	
	// Write data
	fileout = "./average.plt";
	Write_Tp2D_AvgVelocities(fileout, Nx, Ny, x, y, u, v, uv, u_rms, v_rms, uv_rms);
	
	// Delete arrays created
	Destruct2D(x);
	Destruct2D(y);
	Destruct2D(u);
	Destruct2D(v);
	Destruct2D(uv);
	Destruct2D(u2);
	Destruct2D(v2);
	Destruct2D(uv2);
	Destruct2D(u_rms);
	Destruct2D(v_rms);
	Destruct2D(uv_rms);
	
	return 0;
}
