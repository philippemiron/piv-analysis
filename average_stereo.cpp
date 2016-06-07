/*
Calculate the average and rms of two dimensionals stereo velocity fields
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
#include "stats.hpp"

string filein, fileout;

int main()
{
	
// Parameters
vector<string> prefixe(15, "/home/pissarro/phmir/1-donnees_piv/Ladyf/150707-Stereo_vortex/1.15/s");
for (size_t i(0); i<prefixe.size(); i++)
	prefixe[i] += to_string(i+1) + "/B";

string suffixe = ".dat";
int first_filenumber = 1;
int N =  450;
int Nx = 140;
int Ny = 73;
double avgtime = 0.0;

// Create arrays
double** x = Construct2D(Ny, Nx);
double** y = Construct2D(Ny, Nx);
double** z = Construct2D(Ny, Nx);
double** u = Construct2D(Ny, Nx);
double** v = Construct2D(Ny, Nx);
double** w = Construct2D(Ny, Nx);
double** uv = Construct2D(Ny, Nx);
double** uw = Construct2D(Ny, Nx);
double** vw = Construct2D(Ny, Nx);
double** u2 = Construct2D(Ny, Nx);
double** v2 = Construct2D(Ny, Nx);
double** w2 = Construct2D(Ny, Nx);

// Read the velocities of all the fields
for (size_t folder(0); folder<prefixe.size(); folder++) {
	for (int i=0; i<N; i++)
	{
		// Get the filename
		filein = Filename(prefixe[folder], suffixe, i+first_filenumber);

		// Read and fill up the arrays
		Read_Tp2D_Average(filein, Nx, Ny, x, y, z, u, v, w, uv, uw, vw, u2, v2, w2);
	}
}

// Calculate the average
for (int i=0; i < Ny; i++) {
	for (int j=0; j < Nx; j++) {
		u[i][j]  /= (double) N*prefixe.size();
		v[i][j]  /= (double) N*prefixe.size();
		w[i][j]  /= (double) N*prefixe.size();
		uv[i][j] /= (double) N*prefixe.size();
		uw[i][j] /= (double) N*prefixe.size();
		vw[i][j] /= (double) N*prefixe.size();
		u2[i][j] /= (double) N*prefixe.size();
		v2[i][j] /= (double) N*prefixe.size();
		w2[i][j] /= (double) N*prefixe.size();
	}
}

// RMS
double** u_rms = Construct2D(Ny, Nx);
double** v_rms = Construct2D(Ny, Nx);
double** w_rms = Construct2D(Ny, Nx);
double** uv_rms = Construct2D(Ny, Nx);
double** uw_rms = Construct2D(Ny, Nx);
double** vw_rms = Construct2D(Ny, Nx);
RMS(Nx, Ny, u, u2, u_rms);
RMS(Nx, Ny, v, v2, v_rms);
RMS(Nx, Ny, w, w2, w_rms);
RMS(Nx, Ny, u, v, uv, uv_rms);
RMS(Nx, Ny, u, w, uw, uw_rms);
RMS(Nx, Ny, v, w, vw, vw_rms);

// Write data
fileout = "./average.plt";
Write_Tp2D_AvgVelocities(fileout, avgtime, Nx, Ny, x, y, z, u, v, w, u_rms, v_rms, w_rms, uv_rms, uw_rms, vw_rms);

// Delete arrays created
Destruct2D(x);
Destruct2D(y);
Destruct2D(z);
Destruct2D(u);
Destruct2D(v);
Destruct2D(w);
Destruct2D(uv);
Destruct2D(uw);
Destruct2D(vw);
Destruct2D(u2);
Destruct2D(v2);
Destruct2D(w2);
Destruct2D(u_rms);
Destruct2D(v_rms);
Destruct2D(w_rms);
Destruct2D(uv_rms);
Destruct2D(uw_rms);
Destruct2D(vw_rms);

return 0;

}
