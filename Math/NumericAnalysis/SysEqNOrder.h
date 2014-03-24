typedef long double (*syseqf) (long double, long double, long double);
typedef void * syseq;

syseq * syseq_New (long double u1, long double u2, long double start, long double end,
		long double step, syseqf f1, syseqf f2, char * title);
syseq * syseq_Dispose (syseq * s);
long double syseq_GetU1 (syseq * s);
long double syseq_GetU2 (syseq * s);
long double syseq_GetStart (syseq * s);
long double syseq_GetEnd (syseq * s);
long double syseq_GetRange (syseq * s);
long double syseq_GetStep (syseq * s);
long double syseq_GetMax (syseq * s);
long double syseq_GetT (syseq * s, int i);
long double syseq_GetH (syseq * s);
long double syseq_GetW (syseq * s, int j, int i);
void syseq_Print (syseq * s);


