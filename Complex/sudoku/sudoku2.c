#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

typedef struct grid_t {
	int entry [10][10];
} grid;

void
PuzzlePrint(struct grid_t * game) {

	int i, j, k;

	for (i=1; i<10; i++) {
		printf("|-|-|-|-|-|-|-|-|-|\n");
		for (j=1; j<10; j++) {
				printf("|");
				if (game->entry[i][j])
					printf("%d", game->entry[i][j]);
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

		// if it's already cleared, try again.
		if (game->entry[randrow][randcol]==0)
			continue;

		game->entry[randrow][randcol]=0;
		game->entry[10-randrow][10-randcol]=0;
		if(randrow == 5 && randcol == 5)
			NumToClear++;

		NumToClear--;
		NumToClear--;

	}
}

int
PuzzleValidMove(struct grid_t * game, int row, int col, int val) {

	int i, j, offset_i, offset_j;

	// a move is valid if val doesn't exist in the row, col or minigrid

	if(game->entry[row][col])
		return 0;

	for (i=1; i<10; i++){
		if (game->entry[row][i] == val)
			return 0;
		if (game->entry[i][col] == val)
			return 0;
	}

	offset_i = ((row-1)/3)*3+1;
	offset_j = ((col-1)/3)*3+1;

	for(i=offset_i; i<(offset_i+3); i++)
		for (j=offset_j; j<(offset_j+3); j++)
			if (game->entry[i][j] == val)
				return 0;

	return 1;
}


int
PuzzleInsert(struct grid_t * game, int row, int col, int val) {

	int i;

	if (PuzzleValidMove(game, row, col, val)) {
		game->entry[row][col] = val;
		return 1;
	} else {
		// This value in this cell is not valid
		return 0;
	}
}

int
PuzzleColCount(struct grid_t * game, int col, int val) {

	int i;

	int count = 0;

	for (i=1; i<10; i++)
		if (PuzzleValidMove(game, i, col, val))
			count++;

	return count;
}

int
PuzzleSolo(struct grid_t * game, int row, int col, int val) {
	
	int count = 0;
	int i;

	for (i=1; i<10; i++) {
		if(PuzzleValidMove(game, row, col, i)){
			count ++;

			// increment again if the value we are looking to enter will fit here.
			if (i==val)
				count++;
		}
	}

	if(count > 1)
		return 0;
	else
		return 1;
}

int
PuzzleRandomInsert (struct grid_t * game, int col, int val) {

	int i, result, rvalue, colcount, count;		
	static recursive = 0;

	colcount =  PuzzleColCount(game, col, val);

	if(recursive > 10)
		return 0;

	if (colcount == 0)
		return 0;

	rvalue  = random();
        result  = (rvalue/(RAND_MAX/(colcount))) + 1;

	count = 0;
	
	for (i=1; i<10; i++) {
		if (PuzzleValidMove(game, i, col, val)){
			count++;
			if (count == result){

				if (PuzzleSolo(game, i, col, val)){
					if (colcount > 1) {
						int returnval;

						recursive++;
						returnval = PuzzleRandomInsert(game, col, val);
						recursive--;
						return returnval;
					}
				} else {
					return PuzzleInsert(game, i, col, val);
				}
			}
		}
	}	
	return 0;
}

int
PuzzleCheck(struct grid_t * game){

	int i, j, zeros;

	zeros = 0;

	for (i=1; i<10; i++)
		for (j=1; j<10; j++)
			if (!game->entry[i][j])
				zeros++;

	if (zeros)
		return 0;
	else
		return 1;

}

int
PuzzleInit(struct grid_t * game){

	int i, j;

	for (i=1; i<10; i++) 
		for (j=1; j<10; j++) 
			game->entry[i][j]=0;

	for (i=1; i<10; i++) 
        	for (j=1; j<10; j++) 
			if (!PuzzleRandomInsert(game, j, i ))
				return 0;

	return 1;
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

	for (i=0; i<1000; i++) {
		game = PuzzleCreate();
		do {
			PuzzleInit(game);
			tries++;
		} while (!PuzzleCheck(game));


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
