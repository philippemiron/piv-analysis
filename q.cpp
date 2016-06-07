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
#include "diffint.hpp"

string filein, fileout;

int main()
{

// Parameters
vector<string> prefixe(1, "/home/pissarro/phmir/1-donnees_piv/Ladyf/150610-Piston-Trig-VR/s");
for (size_t i(0); i<prefixe.size(); i++)
	prefixe[i] += to_string(i+1) + "/B";

string suffixe = ".dat";
int first_filenumber = 1;
int N =  2500;
int Nx = 153;
int Ny = 75;

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
for (size_t folder(0); folder<prefixe.size(); folder++) {
	for (int i=0; i<N; i++) {
		// Get the filename
		filein = Filename(prefixe[folder], suffixe, i+first_filenumber);
		// Read and fill up the arrays
		Read_Tp2D_Velocities(filein, Nx, Ny, x, y, u[i], v[i]);
	}
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
