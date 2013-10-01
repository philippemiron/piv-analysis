// List of derivation and integration functions


// First Derivative in x
void Derivative2D_x(int Nx, int Ny, int N, double delta, double*** x, double*** dx) {
	
	// Add all the values
	for (int k=0; k < N; k++)
	{
		for (int j=0; j < Ny; j++)
		{
			// Boundaries values
      	dx[k][j][0] = (-1.0*x[k][j][2] + 4.0*x[k][j][1] - 3.0*x[k][j][0])/(2.0*delta);
      	dx[k][j][Nx-1] = (-1.0*x[k][j][Nx-3] + 4.0*x[k][j][Nx-2] - 3.0*x[k][j][Nx-1])/(2.0*delta);
			for (int i=1; i < Nx-1; i++)
			{
				dx[k][j][i] = (-x[k][j][i-1] + x[k][j][i+1])/(2.0*delta);
			}
		}
	}
}
		
// First Derivative in y
void Derivative2D_y(int Nx, int Ny, int N, double delta, double*** y, double*** dy) {
	
	// Add all the values
	for (int k=0; k < N; k++)
	{
		for (int i=0; i < Nx; i++)
		{
			// Boundaries values
      	dy[k][0][i] = (-1.0*y[k][2][i] + 4.0*y[k][1][i] - 3.0*y[k][0][i])/(2.0*delta);
			dy[k][Ny-1][i] = (-1.0*y[k][Ny-3][i] + 4.0*y[k][Ny-2][i] - 3.0*y[k][Ny-1][i])/(2.0*delta);
			for (int j=1; j < Ny-1; j++)
			{
				dy[k][j][i] = (-y[k][j-1][i] + y[k][j+1][i])/(2.0*delta);
			}
		}
	}
}

// Vorticity calculation
void Vorticity(int Nx, int Ny, int N, double*** dvx, double*** duy, double*** w) {

	for (int k=0; k < N; k++)
		for (int j=0; j < Ny; j++)
			for (int i=0; i < Nx; i++)
				w[k][j][i] = dvx[k][j][i] - duy[k][j][i];
}

// Q
void QCriterion(int Nx, int Ny, int N, double*** dux, double*** duy, double*** dvx, double*** dvy, double*** q) {

	for (int k=0; k < N; k++)
		for (int j=0; j < Ny; j++)
			for (int i=0; i < Nx; i++)
				q[k][j][i] = -0.5*(dux[k][j][i]*dux[k][j][i]+dvx[k][j][i]*duy[k][j][i] + duy[k][j][i]*dvx[k][j][i]+dvy[k][j][i]*dvy[k][j][i]);
}