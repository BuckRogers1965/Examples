//#include <stdlib.h>
//#include <stdargs.h>
//#include <math.h>
#include <stdbool.h>

typedef long double (*syseqf) (long double *);
typedef void * SystemNL;

SystemNL * System_New(int OrderSize, char * Title);
SystemNL * Spline_Dispose(SystemNL * s, long double x);
bool System_AddFunc(SystemNL * s, int index, long double initial, syseqf f);
bool System_AddJacobian(SystemNL * s, int a, int b, syseqf f);
void System_Solve(SystemNL * s);
