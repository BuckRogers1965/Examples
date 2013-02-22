#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

int recursion = 0;

typedef struct cell_t {
	int entry[10];
} cell;


typedef struct grid_t {
	struct cell_t array [10][10];
} grid;


void
PuzzlePrint(struct grid_t * game) {

	int i, j, k;

	for (i=1; i<10; i++) {
		printf("|-|-|-|-|-|-|-|-|-|\n");
		for (j=1; j<10; j++) {
				printf("|");
				if (game->array[i][j].entry[0])
					printf("%d", game->array[i][j].entry[0]);
				else
					printf(" ");
		}
		printf("|\n");
	}

	printf("|-|-|-|-|-|-|-|-|-|\n\n");
}

void
PuzzleClear(struct grid_t * game, int NumToClear) {

	while(NumToClear> 0){
		
		int randrow, randcol, rvalue, coloffset;

		rvalue  = random();
        	randrow  = rvalue/(RAND_MAX/5) + 1;
		
		if(randrow==5)
			coloffset = 5;
		else
			coloffset = 9;

		rvalue  = random();
                randcol  = rvalue/(RAND_MAX/coloffset) + 1;

		//printf("Clearing %d %d  and %d %d \n", randrow, randcol, 10-randrow, 10-randcol);
		game->array[randrow][randcol].entry[0]=0;
		game->array[10-randrow][10-randcol].entry[0]=0;
		if(randrow == 5 && randcol == 5)
			NumToClear++;

		NumToClear--;
		NumToClear--;

	}
}

void
SetRowToVal(struct grid_t * game, int row, int val) {

	int i;

	for (i=0; i<10; i++)
		game->array[row][i].entry[val] = 1;
}

void
SetColToVal(struct grid_t * game, int col, int val) {

	int i;

	for (i=0; i<10; i++)
		game->array[i][col].entry[val] = 1;
}

void
SetMiniGridToVal(struct grid_t * game, int row, int col, int val) {

	int i, j, offset_i, offset_j;

	offset_i = (row-1)/3;

	offset_j = (col-1)/3;

	for(i=1; i<4; i++)
		for (j=1; j<4; j++)
			game->array[i+offset_i*3][j+offset_j*3].entry[val] = 1;

}


int
PuzzleInsert(struct grid_t * game, int row, int col, int val) {

	int i;
	//printf("inserting %d  at row %d col %d  ***\n", val, row, col );

	if (!game->array[row][col].entry[val]) {

		SetRowToVal(game, row, val);

		SetColToVal(game, col, val);

		SetMiniGridToVal(game, row, col, val);

		game->array[row][col].entry[0] = val;
		for (i=1; i<10; i++)
			game->array[row][col].entry[i] = 1;

		return 1;
	} else {
		// This value in this cell is not valid
		return 0;
	}

}

int
PuzzleRowCount(struct grid_t * game, int row, int val) {

	int i;

	// start with the max
	int count = 9;

	for (i=1; i<10; i++)
		// subtract one for each entry that is set to val
		count = count - game->array[row][i].entry[val];

	return count;
}

int
PuzzleColCount(struct grid_t * game, int col, int val) {

	int i;

	// start with the max
	int count = 9;

	for (i=1; i<10; i++)
		// subtract one for each entry that is set to val
		count = count - game->array[i][col].entry[val];

	return count;
}

int
PuzzleMiniGridCount(struct grid_t * game, int row, int col, int val){

	
	int i, j, offset_i, offset_j;

	// start with the max
	int count;

	count = 9;

	offset_i = (row-1)*3+1;

	offset_j = (col-1)*3+1;

	for(i=offset_i; i<(offset_i+3); i++)
		for (j=offset_j; j<(offset_j+3); j++){
			//printf("row %d col %d count %d\n", i, j, count );
			count = count - game->array[i][j].entry[val];
		}

	return count;

}

int
PuzzleRandomInsert (struct grid_t * game, int col, int val) {

	int i, result, rvalue, colcount, count;		

	colcount =  PuzzleColCount(game, col, val);

	if (recursion> colcount)
		return 0;


	if (colcount == 0) {
		return 0;
	}

	rvalue  = random();
        result  = (rvalue/(RAND_MAX/(colcount))) + 1;

	count = 0;

	
	for (i=1; i<10; i++) {
		// subtract one for each entry that is set to val
		if (!game->array[i][col].entry[val]){
			count++;
			if (count == result){
				int j;
				int onlyval;
				for (j=1; j < 10; j++)
					onlyval = onlyval + game->array[i][col].entry[j];

				if (onlyval == 8 && !game->array[i][col].entry[val]) {

					int returnval;
					recursion++;

					returnval=  PuzzleRandomInsert (game, col, val);

					recursion--;

					break;
				} else {
					return PuzzleInsert(game, i, col, val);
				}
			}
		}	
	}



}

void
PuzzleCheckDouble(struct grid_t * game){
}

void
PuzzleCheckOnly(struct grid_t * game){

	int i, j, k, replaced, follow;
			int onlyval;

	replaced = 0;
	onlyval = 0;

	for (i=1; i<10; i++) {
		for (j=1; j<10; j++) {
                        for (k=1; k < 10; k++) {
                             onlyval = onlyval + game->array[i][j].entry[k];
				if (!game->array[i][j].entry[k])
					follow = k;
			}

                        if (onlyval == 8) {
			     //printf("Found! %d at  %d %d\n", follow, i, j);
                             PuzzleInsert (game, i, j, follow);
			     replaced++;
			}
		}
		onlyval=0;
	}
}

int
PuzzleCheck(struct grid_t * game){

	int i, j, zeros;

	zeros = 0;

	for (i=1; i<10; i++) {
		for (j=1; j<10; j++) {
			if (!game->array[i][j].entry[0])
				zeros++;
		}
	}

	if (zeros)
		return 0;
	else
		return 1;

}

int
PuzzleMiniGridRandomInsert(struct grid_t * game, int row, int col, int val) {

	int i, j, offset_i, offset_j;
	int result, rvalue, colcount, count;		

	colcount =  PuzzleMiniGridCount(game, col, row, val);

	if (colcount == 0) {
		return 0;
	}

	rvalue  = random();
        result  = (rvalue/(RAND_MAX/(colcount))) +1 ;

	count = 0;

			//printf("row %d col %d result %d colcount %d *****\n", row, col, result, colcount );
	offset_i = (row-1)*3 +1 ;

	offset_j = (col-1)*3 +1 ;

	for(i=offset_i; i<(offset_i+3); i++)
		for (j=offset_j; j<(offset_j+3); j++)

			//printf("row %d col %d count %d\n", i, j, count );
			if (!game->array[i][j].entry[val]) {
				count++;

				if (count == result){

					if(!PuzzleInsert(game, i, j, val))
						return 0;
					goto done;
				}
			}

	done:
	return 1;
}

int PuzzleInit(struct grid_t * game){

	int i, j, k;

	for (i=1; i<10; i++) {
		for (j=1; j<10; j++) {
			for (k=0; k<10; k++) {
				game->array[i][j].entry[k]=0;
			}
		}
	}

//	for (i=1; i<10; i++) 
//		for (j=1; j<4; j++)
//			for (k=1; k<4; k++) {
//				PuzzleMiniGridRandomInsert(game, j, k, i);
//			}


	for (i=1; i<10; i++) {
        	for (j=1; j<10; j++) {
			if (! PuzzleRandomInsert(game, i, j ))
				return 0;
//			PuzzleCheckOnly(game);
			//PuzzleCheckDouble(game);
		}
	}


}

struct grid_t *
PuzzleCreate(){

	struct grid_t * game = (struct grid_t *) malloc (sizeof(grid));

	if (!game)
		return NULL;

	return game;
}

void
PuzzleDestroy(struct grid_t * game){

	free (game);
	game = NULL;

}

int
main () {

	int i;

	int tries = 0;

	int total = 0;
	int ttries = 0;

	struct grid_t * game;

	srandom(time(NULL));

	for (i=0; i<10000; i++) {
		game = PuzzleCreate();
		do {
			PuzzleInit(game);
			tries++;
		} while (!PuzzleCheck(game));

				printf("\n");

		ttries++;

		total = total + tries;

		printf("count %d  avr: %d  tries: %d \n\n", i, total/ttries, tries);
		tries = 0;
		PuzzlePrint(game);

		PuzzleClear(game, 40);

		PuzzlePrint(game);
	}

	PuzzleDestroy(game);

return 0;
}
