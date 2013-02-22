#include <stdio.h>

void calcResult(long result[], double total){

	double dist[5] = {0,0,0,0,0};
	char bp[5] = {'T', 'A', 'G', 'C', 'N'};
	int i;
	long subtotal=0;

	for (i=0; i<4; i++){
		subtotal += result[i];	
	}

	for (i=0; i<4; i++){
		dist[i] = (double)result[i]/(double)subtotal;
		printf("%c\t%ld\t%f\n", bp[i], result[i], dist[i]*100);

		// ok, this is tricky
		// I am replacing the old value of result with a new value
		// based on percentage of total counted
		// to project the final result
		result[i] += dist[i]*result[4];
	}

	// don't print this line if we are projecting into the future
	if (result[4])
		printf("Total Unknown is %ld\n", result[4]);

	printf("\n");

}

int main (){

	long result[5] = {0,0,0,0,0};
	int current;
	long total = 0, totalInFile = 0;

	while ((current = getchar()) !=EOF){

		switch (current){
			case 'T':
				result[0]++;
				break;
			case 'A':
				result[1]++;
                                break;
			case 'G':
				result[2]++;
				break;
			case 'N':
				result[4]++;
				break;
			case 'C':
				result[3]++;
				break;
			default:
				total--;
		}
		total++;
		totalInFile++;
	}

	printf("Actual Results\n");
	calcResult(result, total);

	if (result[4]){
		// in the projected future there will be no unknows
		result[4]=0;
		printf("Projected Results\n");

		calcResult(result, total);
	}

	printf("Processed %ld out of %ld.\n", total, totalInFile);

	return 0;
}
