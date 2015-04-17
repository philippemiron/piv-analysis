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
string name = "points/signal";
string fftname = "spectre/fft";
int imin = 0;
int imax = 79;
int jmin = 0;
int jmax = 49;
int Fs = 200;
int samples_per_block = 2738;
int number_of_blocks = 5;
int N = pow(2, 10);
int verbose = 0;


// variable for filename creation
string file_i, file_j, filename, fft_filename;

// calculate a specto rfor all the indices of the 2D
// piv data between imin-imax jmin-jmax
for (int index_i=imin; index_i<=imax; index_i++) {
	for (int index_j=jmin; index_j<=jmax; index_j++) {
		// Creating filename with index
		// format is nameXXX-YYY.dat where
		// X and Y are the indexes in x,y padded with 0
		ostringstream ssi, ssj;
		ssi << setw(3) << setfill('0') << index_i;
		ssj << setw(3) << setfill('0') << index_j;
		file_i = ssi.str();
		file_j = ssj.str();
		filename = name + file_i + "-" + file_j + ".dat";
		fft_filename = fftname + file_i + "-" + file_j + ".dat";

		// number of averages per independant block
		int averages_per_blocks = int(samples_per_block/N)*2-1;
		if (samples_per_block - int(samples_per_block/N)*double(N) > N/2)
			averages_per_blocks++;

		// array for power final spectrum
		vector<double> power_u(N/2+1, 0.0);
		vector<double> power_v(N/2+1, 0.0);

		// reading of all the signals
		vector<double> u_all(samples_per_block*number_of_blocks, 0.0);
		vector<double> v_all(samples_per_block*number_of_blocks, 0.0);
		Read_Signal(filename, samples_per_block*number_of_blocks, &u_all[0], &v_all[0]);

		double rms_u_t(0), rms_v_t(0);
		// loop for all the averages fft
		for (int k(0); k<number_of_blocks; k++) {
			for (int j(0); j<averages_per_blocks; j++) {
				// Create arrays
				double* u = new double[N];
				double* v = new double[N];
				double* window = new double[N];

				// Retrieve portion of signals
				int index_skip = k*samples_per_block + j*N/2;
				for (int i(0); i<N; i++) {
					u[i] = u_all[index_skip + i];
					v[i] = v_all[index_skip + i];
				}

				// substract the average to u and v
				double u_avg = Average(N, u);
				double v_avg = Average(N, v);
		
				// rms of the signal in time
				for (int i(0); i<N; i++) {	
					u[i] -= u_avg;
					v[i] -= v_avg;
					rms_u_t += u[i]*u[i];
					rms_v_t += v[i]*v[i];
				}

				// windowing
				double windows_sum = 0.0;
				for (int i = 0; i<N; i++) {
					window[i] = hanning(i, N); // TODO outside of the double for
					u[i] *= window[i];
					v[i] *= window[i];
					windows_sum += window[i]*window[i];
				}

				// Copy values to complex array
				fftw_complex* fft_u = new fftw_complex[N];
				fftw_complex* fft_v = new fftw_complex[N];
				for (int i(0); i<N; i++) {
					 fft_u[i][0] = u[i];
					 fft_u[i][1] = 0.0;
					 fft_v[i][0] = v[i];
					 fft_v[i][1] = 0.0;
				}

				/* create plan for forward DFT */
				fftw_plan plan_u = fftw_plan_dft_1d(N, fft_u, fft_u, FFTW_FORWARD, FFTW_ESTIMATE);
				fftw_plan plan_v = fftw_plan_dft_1d(N, fft_v, fft_v, FFTW_FORWARD, FFTW_ESTIMATE);

				/* compute transforms, in-place, as many times as de(SolutionFileNamesired */
				fftw_execute(plan_u);
				fftw_execute(plan_v);

				// Normalization of the spectrum
				// multiply by 2 because we keep only 
				// half of the spectrum (symmetric)
				double normalization = 2.0*double(1.0/Fs)/windows_sum;
				for (int i(0); i<N/2+1; i++) {
					power_u[i] += (fft_u[i][0]*fft_u[i][0] + fft_u[i][1]*fft_u[i][1])*normalization;
					power_v[i] += (fft_v[i][0]*fft_v[i][0] + fft_v[i][1]*fft_v[i][1])*normalization;
				}

				// Delete the plan
				fftw_destroy_plan(plan_u);
				fftw_destroy_plan(plan_v);
				fftw_cleanup();

				// Delete arrays created
				delete [] u;
				delete [] v;
				delete [] window; 
				delete [] fft_u;
				delete [] fft_v;
			}
		}

		// signal in time rms
		rms_u_t /= averages_per_blocks*number_of_blocks*N;
		rms_v_t /= averages_per_blocks*number_of_blocks*N;

		// Average the power spectrum of u and v
		double rms_u(0), rms_v(0);
		for (int i(0); i < N/2+1; ++i) {
			power_u[i] /= averages_per_blocks*number_of_blocks;
			power_v[i] /= averages_per_blocks*number_of_blocks;
			rms_u += power_u[i]*(double(Fs)/double(N));
			rms_v += power_v[i]*(double(Fs)/double(N));
		}
		
		if (verbose) {
			cout << "Signal " << index_i << "-" << index_j << endl;
			cout << averages_per_blocks << " average has been done." << endl;
			cout << "rms_u = " << rms_u_t << " " <<  rms_u << endl;
			cout << "rms_v = " << rms_v_t << " " <<  rms_v << endl;
		}

		// Write fft for every point
		Write_FFT(fft_filename, Fs, N, &power_u[0], &power_v[0]);
	}
}
return 0;
}
