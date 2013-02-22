

#include <stdio.h>
#include <math.h>

int main (){


/* The Compound Interest Equation

    P = C (1 + r/n) nt 

where
    P = future value
    C = initial deposit
    r = interest rate (expressed as a fraction: eg. 0.06)
    n = # of times per year interest is compounded
    t = number of years invested

Simplified Compound Interest Equation
When interest is only compounded once per year (n=1), the equation simplifies to:

    P = C (1 + r) t 

*/

int timelength = 40;
int t=1;
double r;

for(t = 4; t<26; t++)
    printf("\t%d",t);
printf("\n");

for (t=1;t<=timelength;t++){
    printf ("%d\t", t);
    for(r = 4; r<26; r++)
	printf("%f\t",1/pow( 1.0+r/100,t));
    printf("\n");
}


}
