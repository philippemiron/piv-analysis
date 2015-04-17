/*
Calculate the "dumb" phase average
The timesteps have to be constant and a multiple of the 
period so every  n files can be simple averaged together

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
string prefixe = "/home/pissarro/phmir/1-donnees_piv/Ladyf/150415-Pulse/171733-high/B";
string suffixe = ".dat";
int first_filenumber = 1;
int N =  1000;
int N_Phase = 40;
int Nx = 80;
int Ny = 50;


// Create arrays
double*** x = Construct3D(N_Phase, Ny, Nx);
double*** y = Construct3D(N_Phase, Ny, Nx);
double*** u = Construct3D(N_Phase, Ny, Nx);
double*** v = Construct3D(N_Phase, Ny, Nx);
double*** u2 = Construct3D(N_Phase, Ny, Nx);
double*** v2 = Construct3D(N_Phase, Ny, Nx);
double*** uv = Construct3D(N_Phase, Ny, Nx);
vector<int> count_per_phase(N_Phase, 0);

// Read the velocities of all the fields
for (int i=0; i<N; i+=N_Phase) {
	for (int j=0; j<N_Phase; j++) {
		if (i+j < N) {
			// Get the filename
			filein = Filename(prefixe, suffixe, i+j+first_filenumber);
			// Read and fill up the arrays
			Read_Tp2D_Average(filein, Nx, Ny, x[j], y[j], u[j], v[j], uv[j], u2[j], v2[j]);
			count_per_phase[j]++;
		}
	}
}

// Calculate the average
for (int i=0; i < N_Phase; i++) {
	for (int j=0; j < Ny; j++) {
		for (int k=0; k < Nx; k++) {
			u[i][j][k]  /= (double) count_per_phase[i];
			v[i][j][k]  /= (double) count_per_phase[i];
			u2[i][j][k] /= (double) count_per_phase[i];
			v2[i][j][k] /= (double) count_per_phase[i];
			uv[i][j][k] /= (double) count_per_phase[i];
		}
	}
}

// RMS
double*** u_rms = Construct3D(N_Phase, Ny, Nx);
double*** v_rms = Construct3D(N_Phase, Ny, Nx);
double*** uv_rms = Construct3D(N_Phase, Ny, Nx);

for (int i=0; i < N_Phase; i++) {
	RMS(Nx, Ny, u[i], u2[i], u_rms[i]);
	RMS(Nx, Ny, v[i], v2[i], v_rms[i]);
	RMS(Nx, Ny, u[i], v[i], uv[i], uv_rms[i]);
}

// Write data
for (int i=0; i < N_Phase; i++) {
	fileout = "./phase_average_" + to_string(i) + ".plt";
	Write_Tp2D_AvgVelocities(fileout, Nx, Ny, x[i], y[i], u[i], v[i], u_rms[i], v_rms[i], uv_rms[i]);
}


// Delete arrays created
Destruct3D(x);
Destruct3D(y);
Destruct3D(u);
Destruct3D(v);
Destruct3D(uv);
Destruct3D(u2);
Destruct3D(v2);
Destruct3D(u_rms);
Destruct3D(v_rms);
Destruct3D(uv_rms);

return 0;

}