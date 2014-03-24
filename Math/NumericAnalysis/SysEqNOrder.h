typedef long double (*syseqf) (long double, long double *);
typedef void * syseq;

syseq * syseq_New (long double start, long double end, long double step, char * title);
int syseq_AddOrder (syseq * s, long double u, syseqf f);
syseq * syseq_Dispose (syseq * s);
int syseq_Calculate(syseq * s);
long double syseq_GetOrderCount (syseq * s);
long double syseq_GetU (syseq * s, int ordercount);
long double syseq_GetStart (syseq * s);
long double syseq_GetEnd (syseq * s);
long double syseq_GetRange (syseq * s);
long double syseq_GetStep (syseq * s);
long double syseq_GetMax (syseq * s);
long double syseq_GetT (syseq * s, int i);
long double syseq_GetH (syseq * s);
long double syseq_GetW (syseq * s, int j, int i);
void syseq_Print (syseq * s) ;

