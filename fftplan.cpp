/*
	Calculate the Fast Fourrier Trans of a velocity signal 
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
#include "windows.hpp"
int main()
{


// Parameters
std::string fftname = "spectre/fft";
std::string fftplan = "fft_plan";
int axis = 1; // 0 for plan in parallel to x axis, 1 for y axis
int index_min = 0;
int index_max = 79;
int nx = 80;
int ny = 50;
int Fs = 200;
int N = pow(2, 10);
int verbose = 0;

// According to the axis selection
// we construct the matrix with the length
// ny or nx by N/2+1, the number of freq.
const int length = (axis==0) ? nx : ny;
double** fft_plan_u = Construct2D(length, N/2+1);
double** fft_plan_v = Construct2D(length, N/2+1);
std::string file_i;
std::string file_j;
fftplan += (axis==0) ? "_y_" : "_x_";

// for all the index, we read the signals and 
// add them to the 2d fft_u and fft_v matrices


for (int i=index_min; i<=index_max; i++) {
	for (int j(0); j<length; j++) {

		std::ostringstream ssi, ssj;
		ssi << std::setw(3) << std::setfill('0') << i;
		ssj << std::setw(3) << std::setfill('0') << j;
		file_i = ssi.str();
		file_j = ssj.str();
		std::string filename;
		if (axis == 0) 
			filename = fftname + file_j + "-" + file_i + ".dat";
		else
			filename = fftname + file_i + "-" + file_j + ".dat";
		
	
		// array for power final spectrum
		double* fft_u = new double[N/2+1];
		double* fft_v = new double[N/2+1];

		// reading the signal
		if (verbose) std::cout << "reading file: " << filename << std::endl;
		Read_FFT(filename, N, fft_u, fft_v);

		for(int k(0); k<N/2+1; k++) {
			fft_plan_u[j][k] = fft_u[k];
			fft_plan_v[j][k] = fft_v[k];	
		}

		delete [] fft_u;
		delete [] fft_v;
	}

	// Write fft on the selected plan
	std::string output_filename;
	output_filename = fftplan + file_i + ".dat";

	if (verbose) std::cout << "exporting to " << output_filename << std::endl;
	Write_FFT_plan(output_filename, Fs, length, N, fft_plan_u, fft_plan_v);
}

Destruct2D(fft_plan_u);
Destruct2D(fft_plan_v);

return 0;
}
