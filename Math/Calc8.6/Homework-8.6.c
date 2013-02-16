/*
	Numeric Integration Code
	Using trapazoidal and Simpson Parabola Techniques
	Based on the homework from secion 8.6 of 
	Thomas Caculus Early Transcendentals

	By James M. Rogers
	Began work on this on 9 Feb 2013
	Finished required homework on 16 Feb 2013

	Work left to do, 
		Solve the rest of the problems in section 8.6.
		Add various other numeric integration techniques.
		Find maximum could do multiple passes on smaller
			segments with finer resolution to find 
			the most accurate maximum without
			taking a lot of time with too fine a 
			search on the entire function
		Another possible techinque would be to find where 
			The first differential is 0 and scan
			around those points for maximum.
		This cannot integrate discontinuous functions.
		With functions less than 10 iterations, pretty print
			out all the work used to find the answer.

	Notes:
	Going beyond a million iterations seems to decrease accuracy.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//To add a new function to integrate you  must add
// the function - used to calculate the result.
// the first dirivative - currently not used
// the second dirivative - used to find the error in the trapazoidal method
// the fourth dirivative - used to find the error in the simpsons parabola method
// the actual itegral of the function - used to find the true error rate

// Then add the methods you want to use to solve the problem down below in main

// example 1 - x squared 
long double fe1    (long double x){ return (x*x); }
long double dfe1   (long double x){ return (2*x); }
long double ddfe1  (long double x){ return (2); }
long double ddddfe1(long double x){ return (0); }
long double ife1   (long double x){ return (x * x *x / 3); }

// example 2  
long double fe2    (long double x){ return (5 * x *x *x *x); }
long double dfe2   (long double x){ return (20*x*x*x); }
long double ddfe2  (long double x){ return (60*x*x); }
long double ddddfe2(long double x){ return (120); }
long double ife2   (long double x){ return (x * x *x *x *x ); }

// example 5  -  1/x 
long double fe5    (long double x){ return (1/x); }
long double dfe5   (long double x){ return (1/(x*x)); }
long double ddfe5  (long double x){ return (6/(x*x*x)); }
long double ddddfe5(long double x){ return (24/(x*x*x*x*x)); }
long double ife5   (long double x){ return (log(x)); }

// problem 1   x   
long double fp1    (long double x){ return (x); }
long double dfp1   (long double x){ return (1); }
long double ddfp1  (long double x){ return (0); }
long double ddddfp1(long double x){ return (0); }
long double ifp1   (long double x){ return (x * x / 2); }

// problem 2  - 2x -1  
long double fp2    (long double x){ return (2 * x -1); }
long double dfp2   (long double x){ return (2); }
long double ddfp2  (long double x){ return (0); }
long double ddddfp2(long double x){ return (0); }
long double ifp2   (long double x){ return (x * x -x); }

// problem 3   
long double fp3    (long double x){ return (x * x + 1); }
long double dfp3   (long double x){ return (2*x); }
long double ddfp3  (long double x){ return (2); }
long double ddddfp3(long double x){ return (0); }
long double ifp3   (long double x){ return (x * x * x / 3  +x); }

// problem 4   
long double fp4    (long double x){ return (x * x - 1); }
long double dfp4   (long double x){ return (2 * x); }
long double ddfp4  (long double x){ return (2); }
long double ddddfp4(long double x){ return (0); }
long double ifp4   (long double x){ return (x * x * x / 3 - x); }

// problem 5   
long double fp5    (long double x){ return (x * x * x + x); }
long double dfp5   (long double x){ return (3 * x * x + 1); }
long double ddfp5  (long double x){ return (6 * x); }
long double ddddfp5(long double x){ return (0); }
long double ifp5   (long double x){ return (x * x * x * x / 4  + x * x /2); }

// problem 6   
long double fp6    (long double x){ return (x * x * x + 1); }
long double dfp6   (long double x){ return (3 * x * x); }
long double ddfp6  (long double x){ return (6 * x); }
long double ddddfp6(long double x){ return (0); }
long double ifp6   (long double x){ return (x * x * x * x / 4  + x); }

// problem 7   
long double fp7    (long double x){ return ( 1 /(x*x)); }
long double dfp7   (long double x){ return (-2/(x*x*x)); }
long double ddfp7  (long double x){ return (6/(x*x*x*x)); }
long double ddddfp7(long double x){ return (120/(x*x*x*x*x*x)); }
long double ifp7   (long double x){ return (-1/(x)); }

// problem 8   
long double fp8    (long double x){ return (1 /((x-1)*(x-1))); }
long double dfp8   (long double x){ return (-2/((x-1)*(x-1)*(x-1))); }
long double ddfp8  (long double x){ return (6/((x-1)*(x-1)*(x-1)*(x-1))); }
long double ddddfp8(long double x){ return (120/((x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1))); }
long double ifp8   (long double x){ return (1/(1-x)); }

// problem 9   
long double fp9    (long double x){ return (sinl(x)); }
long double dfp9   (long double x){ return (cosl(x)); }
long double ddfp9  (long double x){ return (-sinl(x)); }  
long double ddddfp9(long double x){ return (sinl(x)); }
long double ifp9   (long double x){ return (-cosl(x)); }

// problem 10   
long double fp10    (long double x){ return (sinl(M_PI*x)); }
long double dfp10   (long double x){ return (-M_PI *cosl(M_PI*x)); }
long double ddfp10  (long double x){ return (-M_PI * M_PI * sinl(M_PI * x)); }
long double ddddfp10(long double x){ return (M_PI*M_PI*M_PI*M_PI*sinl(M_PI*x)); }
long double ifp10   (long double x){ return (-cosl(M_PI*x)/M_PI); }

// problem 19   
long double ddfp19  (long double x){ return (.25*powl((x+1), -2.5));}
long double ddddfp19(long double x){ return (.9375 * powl((x+1), -3.5)); }

// problem 20   
long double ddfp20  (long double x){ return (.75 * powl((x+1), -2.5) ); }
long double ddddfp20(long double x){ return (6.5625 * powl((x+1), -4.5)); }

// problem 21   
long double ddfp21  (long double x){ return (-sinl(x+1)); }
long double ddddfp21(long double x){ return (sinl(x+1)); }

// problem 22   
long double ddfp22  (long double x){ return (-cosl(x+M_PI)); }
long double ddddfp22(long double x){ return (cosl(x+M_PI)); }

long double para (long double b, long double e, long double n,
		long double (*f)(long double)){

	long double r = 0;	// result
	long double r2 = 0;	// result every other even interval
	long double r4 = 0;	// result every other even interval

	long double c=(e-b); // The change in x per unit   
	long double ca=c/n/3; // The multiplier for final result
	long double ba = b * n + c; // the begining numerator 
	long double ea = e * n;     // the ending numerator

	if (!n) return 0;

	for (;ba<ea; ba+=c*2)
		r4 += f(ba/n);  // sum all the intervals
	r4*= 4;  // quad alternating interval values.

	ba = b * n + c*2; // the begining numerator 
	for (;ba<ea; ba+=c*2)
		r2 += f(ba/n);  // sum all the intervals
	r2*= 2;  // double alternating interval values.

	r = r2 + r4;
	r += f(b) + f(e); //handle the first and last interval
	r *= ca; // apply the final multiplier

	return r;
}

long double trap (long double b, long double e, long double n,
		long double (*f)(long double)){

	long double r = 0;	// result
	long double c=(e-b); // The change in x per unit   
	long double ca=c/n/2; // The multiplier for final result
	long double ba = b * n +c; // the begining numerator 
	long double ea = e * n ;     // the ending numerator

	if (!n) return 0;

	for (;ba<ea; ba+=c)
		r += f(ba/n);  // sum all the intervals

	r *= 2;  // double all the interval values.
	r += f(b) + f(e); //handle the first and last interval
	r *= ca; // apply the final multiplier

	return r;
}

long double inte (long double b, long double e, long double (*f)(long double)){

	return (f(e)-f(b));
}

long double findUpper (long double b, long double e, long double (*f)(long double)){

	// since we used numberic methods for everything else
	// we are going to find max on interval using brute force.
	long double r = 0;	 // result
	long double n = 100000; //The number of tries per unit.
	long double ba = b*n ; // the begining numerator 
	long double ea = e*n + 1 ;     // the ending numerator

	for (;ba<ea; ba++) r = fmaxl(fabsl(f(ba/n)), r);

	return r;
}

long double etrap(long double b, long double e, long double n, long double (*f)(long double)){
	long double c = (e-b);
	long double et = findUpper(b,e,f);

	return ((et * c * c * c)/(12 * n * n));
}

long double epara(long double b, long double e, long double n, long double (*f)(long double)){

	long double c = e-b;
        long double et = findUpper(b,e,f);

        return ((et * c * c * c * c * c)/(180 * n * n * n * n));
}

long double autoTrapN(long double b, long double e, long double (*f)(long double)){
	long double c = e-b;
	long double et = findUpper(b,e,f);

	return roundl ( powl((et *c *c *c / 12 *10000), .5)+.6);
}

long double autoParaN(long double b, long double e, long double (*f)(long double)){

	long double  c = e-b;
	long double et = findUpper(b,e,f);

	return (roundl ((powl((et*c *c *c *c *c /180 * 10000 ), .25) +1)/2 ) * 2);
}

// Does the homework according to the requirements in section 1
void process (char * name, long double b, long double e, long double n, long double (*f)(long double), long double (*ddf)(long double), long double (*ddddf)(long double), long double (*fi)(long double)){

	long double rt = 0;	// result using trapaziod method
	long double rte = 0;	// error using trapaziod method

	long double rp = 0;	// result using parabola method
	long double rpe = 0;	// error using parabola method

	long double ri = 0;	// result using integration
	int autointerval = 0;

	if (!n) autointerval = 1;

	printf("%s \n", name);
	ri  = inte (b, e, fi);

	if (autointerval) n = autoTrapN(b, e, ddf);
	rt  = trap (b, e, n, f);
	rte = etrap(b, e, n, ddf);

	printf("    I trap i: %8.0Lf a: %10.6Lf, %10Le \tb:  %4.7Lf, %10Le c%5.2Lf \n", n, rt, rte, ri, (rt-ri), ((rt-ri)/ri)*100 );

	if (autointerval) n = autoParaN(b, e, ddddf);
	rp  = para (b, e, n, f);
	rpe = epara(b, e, n, ddddf);

	printf("   II Simp i: %8.0Lf a: %10.6Lf, %10Le \tb:  %4.7Lf, %10Le c%5.2Lf \n", n, rp, rpe, ri, (rp-ri), ((rp -ri)/ri)*100);

	printf ("\n");
}

// Does the homework according to the requirements in section 2
void process2 (char * name, long double b, long double e, long double (*ddf)(long double), long double (*ddddf)(long double)){

	long double n;

	printf("%s\t", name);

	n = autoTrapN(b, e, ddf);
	printf("    a: %4.0Lf", n);

	n = autoParaN(b, e, ddddf);
	printf("\tb: %4.0Lf ", n);

	printf ("\n");
}

// Individual word problem solution.
void Solve25 (){
	printf("\n8.6 - 25 gas tank problem\n\n");

	double tankcapacity=5000;
	double lbpercft=42;
	//double hspacing = 1;
	int segcount = 7;
	double s[7]={1.5, 1.6, 1.8, 1.9, 2.0, 2.1, 2.1};
	double area=0;
	double tankvolume=tankcapacity/lbpercft;

	printf("A tank that must hold %f pounds of fuel\n", tankcapacity );
	printf("At %f pounds per cubic feet\n", lbpercft);
	printf("the tank must be %f cubic feet\n", tankvolume);
	
	int j, k;
	area = s[0];
	printf("%.2f ", area);
	for (j=1, k=segcount-1; j< k; j++, j++){
		area += 4*s[j];
		printf("+ 4 * %.2f ", s[j] );
	}
	for (j=2, k=segcount-1; j< k; j++, j++){
		area += 2*s[j];
		printf("+ 2 * %.2f ", s[j]);
	}
	area += s[segcount-1];
	printf("+  %.2f ", s[segcount-1]);
	printf("=  %.2f\n", area);

	area *= .333333333333;

	printf("Area divided by change in interval/3 or 1/3  is %f \n", area);
	printf("Tank length is %f \n\n", tankvolume/area);
}

int main (){
	printf ("Problem    - function  Iterations  Result             Error\n");
	process ("Example  1 ", 1, 2, 4,    &fe1, &ddfe1, &ddddfe1, &ife1);
	process ("Example  1 ", 1, 2, 1000, &fe1, &ddfe1, &ddddfe1, &ife1);
	process ("Example  2 ", 0, 2, 4,    &fe2, &ddfe2, &ddddfe2, &ife2);
	process ("Example  3 ", 0, 2, 4,    &fe2, &ddfe2, &ddddfe2, &ife2);
	process ("Example  4 ", 0, 2, 22,   &fe2, &ddfe2, &ddddfe2, &ife2);
	process ("Example  4a", 0, 2, 1000, &fe2, &ddfe2, &ddddfe2, &ife2);
	process ("Example  5 ", 1, 2, 10,   &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 30,   &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 50,   &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 100,  &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 1000,  &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 10000,  &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 100000,  &fe5, &ddfe5, &ddddfe5, &ife5);
	process ("Example  5 ", 1, 2, 1000000,  &fe5, &ddfe5, &ddddfe5, &ife5);

	process ("Problem  1 ",  1, 2, 4,    &fp1, &ddfp1, &ddddfp1, &ifp1);
	process ("Problem  2 ",  1, 3, 4,    &fp2, &ddfp2, &ddddfp2, &ifp2);
	process ("Problem  3 ", -1, 1, 4,    &fp3, &ddfp3, &ddddfp3, &ifp3);
	process ("Problem  4 ", -2, 0, 4,    &fp4, &ddfp4, &ddddfp4, &ifp4);
	process ("Problem  5 ",  0, 2, 4,    &fp5, &ddfp5, &ddddfp5, &ifp5);
	process ("Problem  6 ", -1, 1, 4,    &fp6, &ddfp6, &ddddfp6, &ifp6);
	process ("Problem  7 ",  1, 2, 4,    &fp7, &ddfp7, &ddddfp7, &ifp7);
	process ("Problem  8 ",  2, 4, 4,    &fp8, &ddfp8, &ddddfp8, &ifp8);
	process ("Problem  9 ",  0, M_PI, 4, &fp9, &ddfp9, &ddddfp9, &ifp9);
	process ("Problem 10 ",  0, 1, 4,    &fp10, &ddfp10, &ddddfp10, &ifp10);

	process2 ("Problem 11 ",  1, 2, &ddfp1,  &ddddfp1);
	process2 ("Problem 12 ",  1, 3, &ddfp2,  &ddddfp2);
	process2 ("Problem 13 ", -1, 1, &ddfp3,  &ddddfp3);
	process2 ("Problem 14 ", -2, 0, &ddfp4,  &ddddfp4);
	process2 ("Problem 15 ",  0, 2, &ddfp5,  &ddddfp5);
	process2 ("Problem 16 ", -1, 1, &ddfp6,  &ddddfp6);
	process2 ("Problem 17 ",  1, 2, &ddfp7,  &ddddfp7);
	process2 ("Problem 18 ",  2, 4, &ddfp8,  &ddddfp8);
	process2 ("Problem 19 ",  0, 3, &ddfp19, &ddddfp19);
	process2 ("Problem 20 ",  0, 3, &ddfp20, &ddddfp20);
	process2 ("Problem 21 ",  0, 2, &ddfp21, &ddddfp21);
	process2 ("Problem 22 ", -1, 1, &ddfp22, &ddddfp22);

	Solve25();

	return 0;
}
