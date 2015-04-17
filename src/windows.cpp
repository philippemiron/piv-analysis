#include "windows.hpp"

// Window functions
// to test them out.. 
// http://en.wikipedia.org/wiki/Window_function
//
// i is the sample index 
// N is the number of samples

double rectangular(int i, int N)
{
	return 1.0;
}

double triangular(int i, int N)
{
	return (1.0 - fabs((double(i) - double(N-1)/2.0)/double(N/2)));
}

double parzen(int i, int N)
{
	return (1.0 - fabs((double(i) - 0.5*double(N-1))/(0.5*double(N+1))));
}

double welch(int i, int N)
{
	return (1.0 - pow((double(i)-0.5*double(N-1))/(0.5*double(N+1)),2));
}

double hanning(int i, int N)
{
	return (0.5 * (1.0 - cos(2.0*M_PI*double(i)/double(N-1))));
}

double hamming(int i, int N)
{
	return (0.54 - 0.46*cos(2.0*M_PI*double(i)/double(N-1)));
}

double blackman(int i, int N)
{
	double a0 = 7938.0/18608.0;
	double a1 = 9240.0/18608.0;
	double a2 = 1430.0/18608.0;
	return (a0 - a1*cos(2.0*M_PI*double(i)/double(N-1)) + a2*cos(4.0*M_PI*double(i)/double(N-1)));
}

double nuttal(int i, int N)
{
	double a0 = 0.355768;
	double a1 = 0.487396;
	double a2 = 0.144232;
	double a3 = 0.012604;
	return (a0 - a1*cos(2.0*M_PI*double(i)/double(N-1)) + a2*cos(4.0*M_PI*double(i)/double(N-1)) - a3*cos(6.0*M_PI*double(i)/double(N-1)));
}


double blackman_nuttal(int i, int N)
{
	double a0 = 0.3635819;
	double a1 = 0.4891775;
	double a2 = 0.1365995;
	double a3 = 0.0106411;
	return (a0 - a1*cos(2.0*M_PI*double(i)/double(N-1)) + a2*cos(4.0*M_PI*double(i)/double(N-1)) - a3*cos(6.0*M_PI*double(i)/double(N-1)));
}

double blackman_harris(int i, int N)
{
	double a0 = 0.35875;
	double a1 = 0.48829;
	double a2 = 0.14128;
	double a3 = 0.01168;
	return (a0 - a1*cos(2.0*M_PI*double(i)/double(N-1)) + a2*cos(4.0*M_PI*double(i)/double(N-1)) - a3*cos(6.0*M_PI*double(i)/double(N-1)));
}

double flat_top(int i, int N)
{
	double a0 = 1.0;;
	double a1 = 1.93;
	double a2 = 1.29;
	double a3 = 0.388;
	double a4 = 0.028;
	return (a0 - a1*cos(2.0*M_PI*double(i)/double(N-1)) + a2*cos(4.0*M_PI*double(i)/double(N-1)) - a3*cos(6.0*M_PI*double(i)/double(N-1)) + a4*cos(8.0*M_PI*double(i)/double(N-1)));
}

double sin_window(int i, int N)
{
	return sin(M_PI*double(i)/double(N-1));
}