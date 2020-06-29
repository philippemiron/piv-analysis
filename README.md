# Different code for particles image velocimetry analysis

average.bin
	- calculate the average and rms of two dimensional velocity fields

field2points.bin
	- create spatial signal from two dimensional velocity fields

q.bin
	- calculate vorticity and q criteria from two dimensional velocity fields

fft.bin
	- calculate the Fast Fourier Trans of a velocity signal
	- uses the open source code FFTW (https://github.com/FFTW/fftw3)

I/O files format
	- all I/O files are based on Tecplot 360 format
	- the TecIO library can be used to generate binary file format if needed see details here http://www.tecplot.com/downloads/tecio-library/
