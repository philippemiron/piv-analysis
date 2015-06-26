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
	string name = "points/signal";
	string outname = "fields/B";
	int N  = 100;
	int Nx = 10;
	int Ny = 10;
	int first_filenumber = 1;
	
	// Create arrays
	double** x = Construct2D(Ny, Nx);
	double** y = Construct2D(Ny, Nx);
	double** u = Construct2D(Nx*Ny, N);
	double** v = Construct2D(Nx*Ny, N);

  string filename;
  int pIndex(0);
  for (int i(0); i<Nx; i++) {
    for (int j(0); j<Ny; j++) {
      // form the filename of the point signal
      ostringstream ssi, ssj;
		  ssi << setw(3) << setfill('0') << i;
		  ssj << setw(3) << setfill('0') << j;
		  filename = name + ssi.str() + "-" + ssj.str() + ".dat";
		  
		  pIndex = i*Ny + j;
		  cout << filename << endl;
		  //Read_Point(filename, N, u[pIndex], v[pIndex]);
	  }
	}
	
	// TODO: read or generate x-y meshes!
	
	// convert all the signals to field data
	double*** ufield = Construct3D(N, Nx, Ny);
	double*** vfield = Construct3D(N, Nx, Ny);
	
	for (int i(0); i<Nx; i++) {
    for (int j(0); j<Ny; j++) {
      pIndex = i*Ny + j;
      for (int k(0); k<N; k++) {
        ufield[k][i][j] = u[pIndex][k];
        vfield[k][i][j] = v[pIndex][k];
      }
    }
  }
	
	// output fields
	for (int i(0); i<N; i++) {
	  ostringstream ssi;
	  ssi << setw(5) << setfill('0') << i;
	  filename = outname + ssi.str() + ".dat";
	  Write_Tp2D_Velocities(filename, Nx, Ny, x, y, ufield[i], vfield[i]);
  }
  
	// Delete arrays created
	Destruct2D(x);
	Destruct2D(y);
	Destruct2D(u);
	Destruct2D(v);
	Destruct3D(ufield);
	Destruct3D(vfield);
	
	return 0;
}
