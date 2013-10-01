// List of functions to deal with Tecplot files
#include "tecplotio.hpp"

void Read_Tp2D_Velocities(string file, int Nx, int Ny, int k, double** x, double** y, double*** u, double*** v) {
	ifstream iofile;
	iofile.open(file.c_str());
	if(!iofile) { // file couldn't be opened
		cerr << "Error: could not be open file: " << file << endl;
		exit(1);
	}
	
	// saute l'entete dans le fichier
	string stemp;
	getline(iofile, stemp);
	getline(iofile, stemp);
	
	double dtemp;
	for (int j=0; j<Ny; j++)
	{
		for (int i=0; i<Nx; i++)
		{
			// Read x-y coordinates
			iofile >> x[j][i];
			iofile >> y[j][i];
		
			// Read velocity x-y
			iofile >> u[k][j][i];
			iofile >> v[k][j][i];		
		}
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
	if (numero < 10)
	{
		for (int i=0;i<3;i++)
			padding += "0";
	}
	else if (numero < 100)
	{
		for (int i=0;i<2;i++)
			padding += "0";
	}
	else if (numero < 1000)
	{
		for (int i=0;i<1;i++)
			padding += "0";
	}

	num = padding + num;
	
	// return the file name into a string
	string filename = prefixe + num + suffixe;
	return filename;
}

void Write_Tp2D_AvgVelocities(string file, int Nx, int Ny, double** x, double** y, double** u, double** v)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution
	INTEGER4 I         = 0; /* Used to track return codes */

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	I = TECINI112((char*)"Ordered Zone", /* Name of the entire
		* dataset.
		*/
		(char*)"x y u v",  /* Defines the variables for the data
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
	double   SolutionTime             = 0.0;
	INTEGER4 StrandID                 = 0;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0;
	 
	/*  Ordered Zone */
	I = TECZNE112((char*)"Ordered Zone",
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
   
	I   = TECDAT112(&III, &x[0][0], &IsDouble);
	I   = TECDAT112(&III, &y[0][0], &IsDouble);
	I   = TECDAT112(&III, &u[0][0], &IsDouble);
	I   = TECDAT112(&III, &v[0][0], &IsDouble);

	// close the grid file
	I = TECEND112();
}

void Write_Tp2D_Q(string file, int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 0; // 0=full 1=grid 2=solution
	INTEGER4 I         = 0; /* Used to track return codes */

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	I = TECINI112((char*)"Ordered Zone", /* Name of the entire
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
	for (int i=0; i<N; i++){
		
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
	INTEGER4 StrandID                 = i;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0; // use first zone connectivity
	 
	/*  Ordered Zone */
	I = TECZNE112((char*)"Ordered Zone",
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
   

	I   = TECDAT112(&III, &x[0][0], &IsDouble);
	I   = TECDAT112(&III, &y[0][0], &IsDouble);
	I   = TECDAT112(&III, &u[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &v[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &w[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &q[i][0][0], &IsDouble);
	} // End of the Strand loop
	
	// close the grid file
	I = TECEND112();
}

void Write_Tp2D_Q2(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v, double*** w, double*** q)
{
	// Ordered binary file
	INTEGER4 Debug     = 0;
	INTEGER4 IsDouble =  1; // 0=single 1=double
	INTEGER4 FileType  = 1; // 0=full 1=grid 2=solution
	INTEGER4 I         = 0; /* Used to track return codes */

	/*
	* Open the file and write the tecplot datafile
	* header information
	*/
	I = TECINI112((char*)"Ordered Zone", /* Name of the entire
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
	INTEGER4 StrandID                 = 0;      /* StaticZone */
	INTEGER4 ParentZn                 = 0;
	INTEGER4 IsBlock                  = 1;      /* Block */
	INTEGER4 NFConns                  = 0;
	INTEGER4 FNMode                   = 0;
	INTEGER4 TotalNumFaceNodes        = 0;
	INTEGER4 TotalNumBndryFaces       = 0;
	INTEGER4 TotalNumBndryConnections = 0;
	INTEGER4 ShrConn                  = 0; // use first zone connectivity
	 
   /*  Ordered Zone */
   I = TECZNE112((char*)"Ordered Zone",
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
   
	I   = TECDAT112(&III, &x[0][0], &IsDouble);
	I   = TECDAT112(&III, &y[0][0], &IsDouble);

   // close the grid file
   I = TECEND112();
	
	// Loop to export all the other fields
	// they share the connectivity with the first one
	for (int i=1; i<N; i++) {
		
	/*Ordered Zone Parameters*/
   FileType  = 2; // 2 = solution file.
   char SolutionFileName[128];
   sprintf(SolutionFileName, "q%d.plt", i);
	
	I = TECINI112((char*)"Ordered Zone", /* Name of the entire
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
	I = TECZNE112((char*)"Ordered Zone",
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
   
	I   = TECDAT112(&III, &u[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &v[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &w[i][0][0], &IsDouble);
	I   = TECDAT112(&III, &q[i][0][0], &IsDouble);
	
	// close the solution file
	I = TECEND112();
	} // End of the Strand loop
}

/// ASCII format

void Write_Points(int Nx, int Ny, int N, double** x, double** y, double*** u, double*** v)
{
	// Change the data to point format
	// all files are saved in points folder and the name
	// follow NxNy.dat where Nx, Ny are the position of the 
	// points in the vector field
	char SolutionFileName[128];
	FILE* fp;
		
	for (int j=0; j<Ny; j++)
	{
		for (int i=0; i<Nx; i++)
		{
			sprintf(SolutionFileName, "./points/%02d%02d.dat", i, j);
			fp = fopen(SolutionFileName,"w");
			if(fp == NULL) {
				printf("Can't open ./points/%02d%02d.dat. Do the folder exists?\n", i, j);
				exit(0);
			} 
			// Ecriture de l'entete pour les fichiers Tecplot
			fprintf(fp,"variables = t, u, v\n");
			fprintf(fp,"zone T=\" %02d %02d x= %f y= %f \", I= %d, DATAPACKING=POINT, ZONETYPE=ORDERED\n\n", i, j, x[j][i], y[j][i], N);
			for (int k=0; k<N; k++)
				fprintf(fp,"%d %24.10e %24.10e\n", k, u[k][j][i], v[k][j][i]);

			fclose(fp);	
		}
	}
}