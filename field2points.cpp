/*
	Create spatial signal from two dimensionals velocity fields
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
	string prefixe = "/home/pissarro/phmir/1-donnees_piv/Ladyf/150526-Piston/0.8hz/B";
	string suffixe = ".dat";
	int first_filenumber = 1;
	int N  = 5000;
	int Nx = 78;
	int Ny = 100;
	
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
		Read_Tp2D_Velocities(filein, Nx, Ny, x, y, u[i], v[i]);
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
