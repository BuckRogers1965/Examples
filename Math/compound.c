#include <stdio.h>

main(){
 
	float balance;
	float interest;
	float annual_interest;
	float rate_of_inflation;
	float deposit;
	int years;
	int months;
	balance=1250;
	rate_of_inflation=.04;
	annual_interest=.18;
	interest=annual_interest-rate_of_inflation;
	deposit=0;

	printf("Interest %f  Deposit %f\n", interest, deposit);

	for(months=12;balance<=1000000;months=months+12) {
		balance=balance+balance*interest+deposit;
		printf("months %d  dollars %f\n", months, balance);
	}
	years=months/12;
	printf("years %d  dollars %f\n", years, balance);
}

