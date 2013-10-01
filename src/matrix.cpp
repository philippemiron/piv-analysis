// Construction and destruction of 2D, 3D and 4D matrices.

/////////////////////
// Create a 2D matrix
double** Construct2D(int Nx, int Ny) {
	
double* ptr   = new double  [Nx*Ny];
double** x = new double* [Nx];
for(int i=0;i<Nx;i++,ptr+=Ny) 
	x[i]=ptr;

return x;
}

// Delete a 2D matrix
void Destruct2D(double** x) {
	delete [] x[0];
	delete [] x;
}

/////////////////////
// Create a 3D matrix
double*** Construct3D(int Nx, int Ny, int Nz) {

double* ptr = new double [Nx*Ny*Nz];
double** m = new double* [Nx*Ny];
double*** x = new double** [Nx];
for (int i=0;i<Nx;i++,m+=Ny) {
	x[i]=m;
	for(int j=0;j<Ny;j++,ptr+=Nz) {
		m[j]=ptr;
	}
}
return x;
}

// Delete a 3D matrix
void Destruct3D(double*** x) {
	delete [] x[0][0];
	delete [] x[0];
	delete [] x;
}

/////////////////////
// Create a 4D matrix
double**** Construct4D(int Nx, int Ny, int Nz, int N) {

double*  ptr = new double [N*Nx*Ny*Nz];
double**   m = new double* [N*Nx*Ny];
double***  n = new double** [N*Nx];
double**** x = new double*** [N];

for (int i=0;i<N;i++,n+=Nx) {
    x[i]=n;
    for (int j=0;j<Nx;j++,m+=Ny) {
        n[j]=m;
        for(int k=0;k<Ny;k++,ptr+=Nz) {
                m[k]=ptr;
        }
    }
}
return x;
}

// Delete a 4D matrix
void Destruct4D(double**** x) {
	delete [] x[0][0][0];
   delete [] x[0][0];
	delete [] x[0];
	delete [] x;
}