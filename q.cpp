/*
Calculate vorticity and q critieria from two dimensionals velocity fields
Copyright (C) 2014  Philippe Miron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/> 
*/

#include "include.hpp"
#include "tecplotio.hpp"
#include "matrix.hpp"
#include "stats.hpp"
#include "diffint.hpp"

string filein, fileout;

int main()
{

// Parameters
string prefixe = "20131009-premieres_mesures/B";
string suffixe = ".dat";
int first_filenumber = 1;
int N = 202;
int Nx = 54;
int Ny = 34;

// Create arrays
double** x = Construct2D(Ny, Nx);
double** y = Construct2D(Ny, Nx);
// Velocities
double*** u = Construct3D(N, Ny, Nx);
double*** v = Construct3D(N, Ny, Nx);
// Derivatives
double*** dux = Construct3D(N, Ny, Nx);
double*** duy = Construct3D(N, Ny, Nx);
double*** dvx = Construct3D(N, Ny, Nx);
double*** dvy = Construct3D(N, Ny, Nx);
// Eulerian critieria
double*** w = Construct3D(N, Ny, Nx);
double*** q = Construct3D(N, Ny, Nx);

// Read the velocities of all the fields
for (int i=0; i<N; i++) {
	// Get the filename
	filein = Filename(prefixe, suffixe, i+first_filenumber);
	// Read and fill up the arrays
	Read_Tp2D_Velocities(filein, Nx, Ny, i, x, y, u, v);
}

// derivation calculation
Derivative2D_x(Nx, Ny, N, fabs(x[0][1]-x[0][0]), u, dux);
Derivative2D_y(Nx, Ny, N, fabs(y[1][0]-y[0][1]), u, duy);
Derivative2D_x(Nx, Ny, N, fabs(x[0][1]-x[0][0]), v, dvx);
Derivative2D_y(Nx, Ny, N, fabs(y[1][0]-y[0][1]), v, dvy);

// Calculate voricity
Vorticity(Nx, Ny, N, dvx, duy, w);
// Calculate Q critieria
QCriterion(Nx, Ny, N, dux, duy, dvx, dvy, q);

// Write data
fileout = "./qcritieria.plt";
Write_Tp2D_Q(fileout, Nx, Ny, N, x, y, u, v, w, q);

// To output grid/solutions in different files
//Write_Tp2D_Q2(Nx, Ny, N, x, y, u, v, w, q);

// Delete arrays created
Destruct2D(x);
Destruct2D(y);
Destruct3D(u);
Destruct3D(v);
Destruct3D(w);
Destruct3D(q);

return 0;

}