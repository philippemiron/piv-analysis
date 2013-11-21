#include "include.hpp"
#include "tecplotio.hpp"
#include "matrix.hpp"
#include "stats.hpp"
#include "diffint.hpp"

int main()
{
    // Parameters
    std::string filename = "/home/pissarro/phmir/1-resultat_piv/Ladyf/131119-higher_flow_rate/points/0225.dat";
    int N = 5476;

    // Create arrays
    double* u = new double[N];
    double* v = new double[N];

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

    /* initialize data to some function my_function(x,y) */
    double pdata=0;
    for (int i(0); i < N; ++i){
       pdata+=fft_u[i][0]*fft_u[i][0]+fft_u[i][1]*fft_u[i][1];
    }
    printf("power of original data is %f\n", pdata);

    /* compute transforms, in-place, as many times as desired */
    fftw_execute(plan_u);
    fftw_execute(plan_v);
    
    pdata=0;
    double normalization = sqrt(N);
    for (int i(0); i < N; ++i){
       fft_u[i][0]/=normalization;
       fft_u[i][1]/=normalization;
       pdata+=fft_u[i][0]*fft_u[i][0]+fft_u[i][1]*fft_u[i][1];
    }
    printf("power of original data is %f\n", pdata);
        
    // Write fft for every point
    Write_FFT(N, fft_u, fft_v);

    // Delete arrays created
    delete [] u;
    delete [] v;
    delete [] fft_u;
    delete [] fft_v;

    return 0;
}
