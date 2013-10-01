#ifndef _include_
#define _include_

// LES .h DU SYSTEME
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale.h>
#include <algorithm>
#include <vector>
//#include <mpi.h>

using namespace std;

// LES MACROS LES PLUS UTILES
#ifndef signe
#define signe(a)   ( ((a)>=0.0) ? (1.0) : (-1.0) )
#endif

#ifndef max
#define max(a,b)   ( ((a)>(b)) ? (a) : (b) )
#endif

#ifndef min
#define min(a,b)   ( ((a)>(b)) ? (b) : (a) )
#endif

// logical variables
#define TRUE     (1)
#define FALSE    (0)

#endif
