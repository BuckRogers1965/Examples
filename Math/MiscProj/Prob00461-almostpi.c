#include <stdio.h>
#include <math.h>


const long double pi = 3.14159265358979323846264338327950288419716939937510;
long double n;

long double
F(long double k){
  return powl(M_E, k/n) -1;
}

long double
G(long double a, long double b, long double c, long double d){
return F(a) + F(b) + F(c) +F(d) ;
}

long double
H(long double a, long double b, long double c, long double d){
return powl(a, 2) + powl(b,2) + powl(c,2) +powl(d, 2) ;
}

void
main () {

   long double x = 500;
   long double y = 1*x;
   long double ia, ib, ic, id;
   ia = ib = ic = id = 0;

   long double min = 10;
   long double minh;
   long double r;
   long double rt;
   
   n = 200 * x;

   long double a =   6 * x;
   long double b =  75 * x;
   long double c =  89 * x;
   long double d = 226 * x;
  long double asave=0, bsave=0, csave=0, dsave=0;

/*
   for (ia=a-y; ia<(a+y); ia++)
     for (ib=b-y; ib<(b+y); ib++)
       for (ic=c-y; ic<(c+y); ic++)
         for (id=d-y; id<(d+y); id++) 
           {
              rt = G(ia, ib, ic, id);
              r = fabsl(rt - pi) ;
              if (r<min) {
                printf ("%0.20Lf\n", rt );
                minh = H(ia, ib, ic, id) ;
                min = r;
              } 
           }
*/

  long double minrt;

         for (id=0; id<d*5; id++) 
           {
              rt = F(a) + F(b) + F(c) + F(id);
              r = fabsl(rt - pi) ;
              if (r<min) {
                //printf ("%0.20Lf\n", rt );
                minh = H(ia, ib, ic, id) ;
                dsave = id;
                min = r;
                minrt = rt;
              } else break;
           }
    
           minh = H(asave, bsave, csave, dsave) ;
     printf ("a %0.0Lf b %0.0Lf c %0.0Lf d %0.0Lf %Lf  %0.30Lf\n", asave, bsave, csave, dsave, minh, minrt );
         min = 400;

         for (ic=0; ic<c*5; ic++)
           {
              rt = F(a) + F(b) + F(dsave) +F(ic);
              //printf ("%0.0Lf  %0.20Lf\n", ic, rt );
              r = fabsl(rt - pi) ;
              if (r<min) {
                //printf ("%0.20Lf\n", rt );
                csave = ic;
                min = r;
                minrt = rt;
              } else break;
           }

           minh = H(asave, bsave, csave, dsave) ;
     printf ("a %0.0Lf b %0.0Lf c %0.0Lf d %0.0Lf %Lf  %0.30Lf\n", asave, bsave, csave, dsave, minh, minrt );
         min = 400;

         for (ib=0; ib<b*5; ib++)
           {
              rt = F(a) + F(dsave) +F(csave) + F(ib);
              //printf ("%0.0Lf  %0.20Lf\n", ic, rt );
              r = fabsl(rt - pi ) ;
              if (r<min) {
                //printf ("%0.20Lf\n", rt );
                bsave = ib;
                min = r;
                minrt = rt;
              } else break;
           }

           minh = H(asave, bsave, csave, dsave) ;
     printf ("a %0.0Lf b %0.0Lf c %0.0Lf d %0.0Lf %Lf  %0.30Lf\n", asave, bsave, csave, dsave, minh, minrt );
         min = 400;

         for (ia=0; ia<a*5; ia++)
           {
              rt = F(dsave) +F(csave) + F(bsave) + F(ia);
              //printf ("%0.0Lf  %0.20Lf\n", ic, rt );
              r = fabsl(rt - pi ) ;
              if (r<min) {
                //printf ("%0.20Lf\n", rt );
                asave = ia;
                min = r;
                minrt = rt;
              } else break;
           }

           minh = H(asave, bsave, csave, dsave) ;
     printf ("a %0.0Lf b %0.0Lf c %0.0Lf d %0.0Lf %Lf  %0.30Lf\n", asave, bsave, csave, dsave, minh, minrt );
}
