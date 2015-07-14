// List of functions to deal with Tecplot files
#include "tecplotio.hpp"

void Read_Tp2D_Velocities(string file, int Nx, int Ny, double** x, double** y, double** u, double** v) {
	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open/find file: " << file << endl;
		exit(1);
	}
	
	// saute l'entete dans le fichier
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);
	getline(iofile, stemp);
	
	for (int i=0; i<Ny; i++) {
		for (int j=0; j<Nx; j++) {
			// Read x-y coordinates
			iofile >> x[i][j];
			iofile >> y[i][j];
		
			// Read velocity x-y
			iofile >> u[i][j];
			iofile >> v[i][j];		
		}
	}
	iofile.close();
}

void Read_Tp2D_Average(string file, int Nx, int Ny, double** x, double** y, double** u, double** v, double** uv, double** u2, double** v2) {
	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open the file: " << file << endl;
		exit(1);
	}
	
	// saute l'entete dans le fichier
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);
	getline(iofile, stemp);
	
	double u_temp, v_temp;
	for (int i=0; i<Ny; i++) {
		for (int j=0; j<Nx; j++) {
			// Read x-y coordinates
			iofile >> x[i][j];
			iofile >> y[i][j];
	
			// Read velocity
			iofile >> u_temp;
			iofile >> v_temp;
		
			u[i][j] += u_temp;
			v[i][j] += v_temp;
			
			uv[i][j] += u_temp*v_temp;
			u2[i][j] += pow(u_temp, 2.0);
			v2[i][j] += pow(v_temp, 2.0);
		}
	}
	iofile.close();
}

void Read_Tp2D_Average(string file, int Nx, int Ny, double** x, double** y, double** z, double** u, double** v, double** w, double** uv, double** uw, double** vw, double** u2, double** v2, double** w2) {
	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open the file: " << file << endl;
		exit(1);
	}
	
	// saute l'entete dans le fichier
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);
	getline(iofile, stemp);
	
	double u_temp, v_temp, w_temp;
	for (int i=0; i<Ny; i++) {
		for (int j=0; j<Nx; j++) {
			// Read x-y-z coordinates
			iofile >> x[i][j];
			iofile >> y[i][j];
			iofile >> z[i][j];

			// Read velocity
			iofile >> u_temp;
			iofile >> v_temp;
			iofile >> w_temp;

			u[i][j] += u_temp;
			v[i][j] += v_temp;
			w[i][j] += w_temp;

			uv[i][j] += u_temp*v_temp;
			uw[i][j] += u_temp*w_temp;
			vw[i][j] += v_temp*w_temp;

			u2[i][j] += pow(u_temp, 2.0);
			v2[i][j] += pow(v_temp, 2.0);
			w2[i][j] += pow(w_temp, 2.0);
		}
	}
	iofile.close();
}

void Read_Point(string file, int N, double* u, double* v) {

	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open the file: " << file << endl;
		exit(1);
	}
	
	// remove to first comments lines
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);

	for (int i=0; i<N; i++) {
		// Read velocities
		iofile >> u[i];
		iofile >> v[i];
	}
	iofile.close();
}


void Read_FFT(string file, int N, double* fft_u, double* fft_v) {
	
	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open the file: " << file << endl;
		exit(1);
	}
	
	// remove to first comments lines
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);

	double dtemp;
	for (int i=0; i<N; i++) {
		// Read frequencies
		iofile >> dtemp;
		// Read power spectrum
		iofile >> fft_u[i];
		iofile >> fft_v[i];
	}
	iofile.close();
}


string Filename(string prefixe, string suffixe, int numero) {

	// Transform number into substring	
	stringstream ss;
	ss << numero;
	string num;
	ss >> num;
	
	// Adding padding of 0
	string padding;
	if (numero < 10) {
		for (int i=0;i<4;i++)
			padding += "0";
	}
	else if (numero < 100) {
		for (int i=0;i<3;i++)
			padding += "0";
	}
	else if (numero < 1000) {
		for (int i=0;i<2;i++)
			padding += "0";
	}
	else if (numero < 10000) {
		for (int i=0;i<1;i++)
			padding += "0";
	}

	num = padding + num;
	
	// return the file name into a string
	string filename = prefixe + num + suffixe;
	return filename;
}

void Write_Tp2D_AvgVelocities(string file, double time, int Nx, int Ny, double** x, double** y, double** u, double** v, double** up, double** vp, double** uvp)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"x y u v u_rms v_rms uv_rms", /* Defines the variables for the data
																					* file. Each zone must contain each of
																					* the variables listed here. The order
																					* of the variables in the list is used
																					* to define the variable number (e.g.
																					* X is Var 1).
																					*/
		(char*)file.c_str(),
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);
		
	/*Ordered Zone Parameters*/
	INTEGER4 ZoneType = 0; // Ordered
	INTEGER4 IMax = Nx; // x
	INTEGER4 JMax = Ny; // y
	INTEGER4 KMax = 1; // z
	INTEGER4 ICellMax                 = 0;
	INTEGER4 JCellMax                 = 0;
	INTEGER4 KCellMax                 = 0;
	double   SolutionTime             = time;
	INTEGER4 StrandID                 = 1;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0;
	 
	/*  Ordered Zone */
	TECZNE112((char*)"Ordered Zone",
			&ZoneType,
			&IMax,
			&JMax,
			&KMax,
			&ICellMax,
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZn,
			&IsBlock,
			&NFConns,
			&FNMode,
			&TotalNumFaceNodes,
			&TotalNumBndryFaces,
			&TotalNumBndryConnections,
			nullptr,
			nullptr,
			nullptr,
			&ShrConn);
			
	INTEGER4 III = IMax * JMax * KMax;

	TECDAT112(&III, &x[0][0], &IsDouble);
	TECDAT112(&III, &y[0][0], &IsDouble);
	TECDAT112(&III, &u[0][0], &IsDouble);
	TECDAT112(&III, &v[0][0], &IsDouble);
	TECDAT112(&III, &up[0][0], &IsDouble);
	TECDAT112(&III, &vp[0][0], &IsDouble);
	TECDAT112(&III, &uvp[0][0], &IsDouble);

	// close the grid file
	TECEND112();
}

void Write_Tp2D_AvgVelocities(string file, double time, int Nx, int Ny, double** x, double** y, double** z, double** u, double** v, double** w, double** up, double** vp, double** wp, double** uvp, double** uwp, double** vwp)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"x y z u v w u_rms v_rms w_rms uv_rms uw_rms vw_rms", /* Defines the variables for the data
																																* file. Each zone must contain each of
																																* the variables listed here. The order
																																* of the variables in the list is used
																																* to define the variable number (e.g.
																																* X is Var 1).
																																*/
		(char*)file.c_str(),
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);
		
	/*Ordered Zone Parameters*/
	INTEGER4 ZoneType = 0; // Ordered
	INTEGER4 IMax = Nx; // x
	INTEGER4 JMax = Ny; // y
	INTEGER4 KMax = 1; // z
	INTEGER4 ICellMax                 = 0;
	INTEGER4 JCellMax                 = 0;
	INTEGER4 KCellMax                 = 0;
	double   SolutionTime             = time;
	INTEGER4 StrandID                 = 1;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0;
	 
	/*  Ordered Zone */
	TECZNE112((char*)"Ordered Zone",
			&ZoneType,
			&IMax,
			&JMax,
			&KMax,
			&ICellMax,
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZn,
			&IsBlock,
			&NFConns,
			&FNMode,
			&TotalNumFaceNodes,
			&TotalNumBndryFaces,
			&TotalNumBndryConnections,
			nullptr,
			nullptr,
			nullptr,
			&ShrConn);
			
	INTEGER4 III = IMax * JMax * KMax;

	TECDAT112(&III, &x[0][0], &IsDouble);
	TECDAT112(&III, &y[0][0], &IsDouble);
	TECDAT112(&III, &z[0][0], &IsDouble);
	TECDAT112(&III, &u[0][0], &IsDouble);
	TECDAT112(&III, &v[0][0], &IsDouble);
  TECDAT112(&III, &w[0][0], &IsDouble);
	TECDAT112(&III, &up[0][0], &IsDouble);
	TECDAT112(&III, &vp[0][0], &IsDouble);
  TECDAT112(&III, &wp[0][0], &IsDouble);
	TECDAT112(&III, &uvp[0][0], &IsDouble);
  TECDAT112(&III, &uwp[0][0], &IsDouble);
  TECDAT112(&III, &vwp[0][0], &IsDouble);

	// close the grid file
	TECEND112();
}

void Write_Tp2D_Q(string file, int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"x y u v w q",  /* Defines the variables for the data
														* file. Each zone must contain each of
														* the variables listed here. The order
														* of the variables in the list is used
														* to define the variable number (e.g.
														* X is Var 1).
														*/
		(char*)file.c_str(),
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);
		
	// Loop to export all the other fields
	// they share the connectivity with the first one
	for (int i=0; i<N; i++) {
		
		/*Ordered Zone Parameters*/
		INTEGER4 ZoneType = 0; // Ordered
		INTEGER4 IMax = Nx; // x
		INTEGER4 JMax = Ny; // y
		INTEGER4 KMax = 1; // z
		INTEGER4 III = IMax*JMax*KMax;
		INTEGER4 ICellMax                 = 0;
		INTEGER4 JCellMax                 = 0;
		INTEGER4 KCellMax                 = 0;
		double   SolutionTime             = (double)i;
		INTEGER4 StrandID                 = 1;      /* StaticZone */
		INTEGER4 ParentZn                 = 0;
		INTEGER4 IsBlock                  = 1;      /* Block */
		INTEGER4 NFConns                  = 0;
		INTEGER4 FNMode                   = 0;
		INTEGER4 TotalNumFaceNodes        = 0;
		INTEGER4 TotalNumBndryFaces       = 0;
		INTEGER4 TotalNumBndryConnections = 0;
		INTEGER4 ShrConn                  = 0; // use first zone connectivity
		 
		/*  Ordered Zone */
		TECZNE112((char*)"Ordered Zone",
			&ZoneType,
			&IMax,
			&JMax,
			&KMax,
			&ICellMax,
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZn,
			&IsBlock,
			&NFConns,
			&FNMode,
			&TotalNumFaceNodes,
			&TotalNumBndryFaces,
			&TotalNumBndryConnections,
			nullptr,
			nullptr,
			nullptr,
			&ShrConn);

		TECDAT112(&III, &x[0][0], &IsDouble);
		TECDAT112(&III, &y[0][0], &IsDouble);
		TECDAT112(&III, &u[i][0][0], &IsDouble);
		TECDAT112(&III, &v[i][0][0], &IsDouble);
		TECDAT112(&III, &w[i][0][0], &IsDouble);
		TECDAT112(&III, &q[i][0][0], &IsDouble);
	} // End of the Strand loop
	
	// close the grid file
	TECEND112();
}

void Write_Tp2D_Q2(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 1; // 0=full 1=grid 2=solution

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"x y",  /* Defines the variables for the data
										* file. Each zone must contain each of
										* the variables listed here. The order
										* of the variables in the list is used
										* to define the variable number (e.g.
										* X is Var 1).
										*/
		(char*)"qgrid.plt",
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);
		
	// First field with the connectivity		
	/*Ordered Zone Parameters*/
	INTEGER4 ZoneType = 0; // Ordered
	INTEGER4 IMax = Nx; // x
	INTEGER4 JMax = Ny; // y
	INTEGER4 KMax = 1; // z
	INTEGER4 III = IMax*JMax*KMax;
	INTEGER4 ICellMax                 = 0;
	INTEGER4 JCellMax                 = 0;
	INTEGER4 KCellMax                 = 0;
	double   SolutionTime             = 0.0;
	INTEGER4 StrandID                 = 1;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0; // use first zone connectivity
	 
	/*  Ordered Zone */
	TECZNE112((char*)"Ordered Zone",
		&ZoneType,
		&IMax,
		&JMax,
		&KMax,
		&ICellMax,
		&JCellMax,
		&KCellMax,
		&SolutionTime,
		&StrandID,
		&ParentZn,
		&IsBlock,
		&NFConns,
		&FNMode,
		&TotalNumFaceNodes,
		&TotalNumBndryFaces,
		&TotalNumBndryConnections,
		nullptr,
		nullptr,
		nullptr,
		&ShrConn);

	TECDAT112(&III, &x[0][0], &IsDouble);
	TECDAT112(&III, &y[0][0], &IsDouble);

	// close the grid file
	TECEND112();
	
	// Loop to export all the other fields
	// they share the connectivity with the first one
	for (int i=1; i<N; i++) {
		/*Ordered Zone Parameters*/
		FileType  = 2; // 2 = solution file.
		char SolutionFileName[128];
		sprintf(SolutionFileName, "q%d.plt", i);

		TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"u v w q",  /* Defines the variables for the data
												* file. Each zone must contain each of
												* the variables listed here. The order
												* of the variables in the list is used
												* to define the variable number (e.g.
												* X is Var 1).
												*/
		SolutionFileName,
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);

		/*  Ordered Zone */
		TECZNE112((char*)"Ordered Zone",
			&ZoneType,
			&IMax,
			&JMax,
			&KMax,
			&ICellMax,
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZn,
			&IsBlock,
			&NFConns,
			&FNMode,
			&TotalNumFaceNodes,
			&TotalNumBndryFaces,
			&TotalNumBndryConnections,
			nullptr,
			nullptr,
			nullptr,
			&ShrConn);

		TECDAT112(&III, &u[i][0][0], &IsDouble);
		TECDAT112(&III, &v[i][0][0], &IsDouble);
		TECDAT112(&III, &w[i][0][0], &IsDouble);
		TECDAT112(&III, &q[i][0][0], &IsDouble);

		// close the solution file
		TECEND112();
	} // End of the Strand loop
}

void Write_Avg_Convergence(string file, pair<int, int>& indexes, vector2d<double>& u_average, vector2d<double>& v_average, vector2d<double>& u_error, vector2d<double>& v_error) 
{

	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	string title = "Convergence index " + to_string(indexes.first) + "-" + to_string(indexes.second);
	TECINI112((char*)title.c_str(), /* Name of the entire
		* dataset.
		*/
		(char*)"Series U_Avg V_Avg U_Error V_Error",
		(char*)file.c_str(),
		(char*)".",      /* Scratch Directory */
		&FileType,
		&Debug,
		&IsDouble);
	
	// index vector
	vector<double> series(u_average[0].size());
	for (size_t i(0); i<series.size(); i++)
		series[i] = double(i+1);


	// number of phase subdivisons
	for (size_t i(0); i<u_average.size(); i++) { 
		/*Ordered Zone Parameters*/
		INTEGER4 ZoneType = 0; // Ordered
		INTEGER4 IMax = u_average[i].size(); // number of series
		INTEGER4 JMax = 1; // y
		INTEGER4 KMax = 1; // z
		INTEGER4 III = IMax*JMax*KMax;
		INTEGER4 ICellMax                 = 0;
		INTEGER4 JCellMax                 = 0;
		INTEGER4 KCellMax                 = 0;
		double   SolutionTime             = (double)i;
		INTEGER4 StrandID                 = 1;      /* StaticZone */
		INTEGER4 ParentZn                 = 0;
		INTEGER4 IsBlock                  = 1;      /* Block */
		INTEGER4 NFConns                  = 0;
		INTEGER4 FNMode                   = 0;
		INTEGER4 TotalNumFaceNodes        = 0;
		INTEGER4 TotalNumBndryFaces       = 0;
		INTEGER4 TotalNumBndryConnections = 0;
		INTEGER4 ShrConn                  = 0; // use first zone connectivity

		/*  Ordered Zone */
		TECZNE112((char*)"Ordered Zone",
			&ZoneType,
			&IMax,
			&JMax,
			&KMax,
			&ICellMax,
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZn,
			&IsBlock,
			&NFConns,
			&FNMode,
			&TotalNumFaceNodes,
			&TotalNumBndryFaces,
			&TotalNumBndryConnections,
			nullptr,
			nullptr,
			nullptr,
			&ShrConn);

		TECDAT112(&III, series.data(), &IsDouble);
		TECDAT112(&III, u_average[i].data(), &IsDouble);
		TECDAT112(&III, v_average[i].data(), &IsDouble);
		TECDAT112(&III, u_error[i].data(), &IsDouble);
		TECDAT112(&III, v_error[i].data(), &IsDouble);

	} // End of the Strand loop

	// close the solution file
	TECEND112();
};

// ASCII format
void Write_Tp2D_Velocities(string file, int Nx, int Ny, double** x, double** y, double** u, double** v) {
	ofstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { 
		cerr << "Error: could not open/find file: " << file << endl;
		exit(1);
	}
	
	// tecplot headers
	iofile << "TITLE = \"field\"" << endl;
	iofile << "VARIABLES = \"x\", \"y\", \"u\", \"v\"" << endl;
  iofile << "ZONE I=" << Ny << ", J=" << Ny << endl;
	
	for (int i=0; i<Ny; i++) {
		for (int j=0; j<Nx; j++) {
			// Read x-y coordinates
			iofile << x[i][j] << " ";
			iofile << y[i][j] << " ";
		
			// Read velocity x-y
			iofile << u[i][j] << " ";
			iofile << v[i][j] << " ";	
			iofile << endl;	
		}
	}
	iofile.close();
}

void Write_Points(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v)
{
	// Change the data to point format
	// all files are saved in points folder and the name
	// follow NxNy.dat where Nx, Ny are the position of the 
	// points in the vector field
	char SolutionFileName[128];
	FILE* fp;
		
	for (int i=0; i<Ny; i++) {
		for (int j=0; j<Nx; j++) {
			sprintf(SolutionFileName, "./points/signal%03d-%03d.dat", j, i);
			fp = fopen(SolutionFileName,"w");

			if(fp == NULL) {
				printf("Can't open ./points/signal%03d-%03d.dat. Do the folder exists?\n", j, i);
				exit(0);
			}

			// Ecriture de l'entete pour les fichiers Tecplot
		  fprintf(fp, "# x =%15.8E, y =%15.8E\n", x[i][j], y[i][j]);
			fprintf(fp," VARIABLES = u, v\n");
			
			for (int k(0); k<N; k++)
				fprintf(fp,"%15.8E %15.8E\n", u[k][i][j], v[k][i][j]);

			fclose(fp);	
		}
	}
};

void Write_FFT(string filename, int Fs, int N, double* fft_u, double* fft_v)
{
	// Change the data to point format
	FILE* fp;
	fp = fopen(filename.c_str(),"w");

	if(fp == NULL) {
		cout << "Can't open file : " << filename << "." << endl;
		exit(0);
	}
	// Ecriture de l'entete pour les fichiers Tecplot
	fprintf(fp, "TITLE = \"fft\"");
	fprintf(fp,"variables = f, fft_u, fft_v,\n");
	fprintf(fp,"zone T=\"signal fft\", I= %d, DATAPACKING=POINT, ZONETYPE=ORDERED\n", N/2+1);

	for (int k(0); k<N/2+1; k++)
		fprintf(fp,"%f %15.8E %15.8E\n", double(Fs)*double(k)/double(N), fft_u[k], fft_v[k]);

	fclose(fp);	
}

void Write_FFT_plan(string filename, int Fs, int length, int N, double** fft_u, double** fft_v)
{
	//Opening the file
	ofstream myfile(filename.c_str());
	if (myfile.is_open())
	{
		// TP Headlines
		myfile << "TITLE = \"fft plan\"" << endl << "VARIABLES = index, f, fft_u, fft_v" << endl;
		myfile << "zone I=" << N/2+1 << ", J=" << length << ", DATAPACKING=POINT" << endl;

		for(int i(0); i<length; i++) {
			for(int j(0); j<N/2+1; j++) {
				myfile << i << " " << double(Fs)*double(j)/double(N) << " " << fft_u[i][j] << " " << fft_v[i][j] << endl;
			}
		}

		// Closing the file
		myfile.close();
	} 
	else {
		cout << "Can't open output file name: " << filename << endl;
		exit(0);
	}

}
