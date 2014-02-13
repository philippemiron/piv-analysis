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
    //std::string filename = "./points/signal019-025.dat";
	std::string filename = "signal_test.dat";
	// Sample frequency
	//int Fs = 200;

	int Fs = 200;
	int N  = 3100; // even value
	int N_window;
	

    // Create arrays
    double* u = new double[N];
    double* v = new double[N];
	double* window = new double[N];
	double* power_u = new double[N/2+1];
	double* power_v = new double[N/2+1];

    // Read the signals
    Read_Signal(filename, N, u, v);

    // substract the average to u and v
    double u_avg, v_avg;
    for (int i(0); i<N; i++) 
    {
        u_avg += u[i];
        v_avg += v[i];
    }
    u_avg /= N;
    v_avg /= N;
    for (int i(0); i<N; i++) 
    {
        u[i] -= u_avg;
        v[i] -= v_avg;
    }
	
	// windowing
	double windows_sum;
	for (int i = 0; i < N; i++) {
		window[i] = hanning(i, N);
		//window[i] = rectangular(i, N);
    	u[i] *= window[i];
		v[i] *= window[i];
		windows_sum += window[i]*window[i];
	}
	
    // Copy values to complex array
    fftw_complex* fft_u = new fftw_complex[N];
    fftw_complex* fft_v = new fftw_complex[N];
    for (int i(0); i<N; i++) {
         fft_u[i][0] = u[i];
         fft_u[i][1] = 0;
         fft_v[i][0] = v[i];
         fft_v[i][1] = 0;
    }

    /* create plan for forward DFT */
    fftw_plan plan_u = fftw_plan_dft_1d(N, fft_u, fft_u, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_plan plan_v = fftw_plan_dft_1d(N, fft_v, fft_v, FFTW_FORWARD, FFTW_ESTIMATE);

    /* compute transforms, in-place, as many times as desired */
    fftw_execute(plan_u);
    fftw_execute(plan_v);

	// Normalization of the spectrum
	// multiply by 2 because we keep only 
	// half of the spectrum (symmetric)
	double normalization = 2.0*double(1.0/Fs)/windows_sum;
	for (int i(0); i < N/2+1; ++i){
		power_u[i] = (fft_u[i][0]*fft_u[i][0] + fft_u[i][1]*fft_u[i][1])*normalization;
		power_v[i] = (fft_v[i][0]*fft_v[i][0] + fft_v[i][1]*fft_v[i][1])*normalization;
	}	    

    // Write fft for every point
    Write_FFT(Fs, N, power_u, power_v);

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
	delete [] power_u;
	delete [] power_v;

    return 0;
}
