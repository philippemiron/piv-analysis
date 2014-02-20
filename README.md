piv-analysis

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
along with this program.  If not, see http://www.gnu.org/licenses

Different code for particles image velocimetry analysis

average.bin
	- calculate the average and rms of two dimensionals velocity fields
field2points.bin
	- create spatial signal from two dimensionals velocity fields
q.bin
	- calculate vorticity and q critieria from two dimensionals velocity fields

fft.bin
	- calculate the Fast Fourrier Trans of a velocity signal
	- uses fftw (https://github.com/FFTW/fftw3) to calculate the fft.

I/O files format
	- all I/O files are based on Tecplot360 format
	- the TecIO library can be used to generate binary file format if needed see details here http://www.tecplot.com/downloads/tecio-library/


