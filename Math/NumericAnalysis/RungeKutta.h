typedef long double (*rkf) (long double, long double);
typedef void * rk;

rk * rk_New (long double alpha, long double start,
	long double end, long double step, rkf f);
rk * rk_Dispose (rk * r);
long double rk_GetAlpha (rk * r);
long double rk_GetStart (rk * r);
long double rk_GetEnd (rk * r);
long double rk_GetRange (rk * r);
long double rk_GetStep (rk * r);
long double rk_GetMax (rk * r);
long double rk_GetT (rk * r);
long double rk_GetH (rk * r);
long double rk_GetW (rk * r, int i);
void rk_Print (rk * r);
