#include <stdbool.h>

typedef void * spline;

spline *
Spline_New(int max_point_count);

bool 
Spline_AddPoint(spline * s, long double x, long double y);

long double
Spline_Solve(spline * s, long double x);

long double
Spline_Derive(spline * s, long double x);

int
Spline_PointCount(spline * s);
