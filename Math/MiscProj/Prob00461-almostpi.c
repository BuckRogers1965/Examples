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
   long double y = 5*x;
   long double ia, ib, ic, id;

   long double min = 10;
   long double minh;
   long double r;
   long double rt;
   
   n = 200 * x;

   long double a =   6 * x;
   long double b =  75 * x;
   long double c =  89 * x;
   long double d = 226 * x;

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
     printf ("%Lf\n", minh );
}
