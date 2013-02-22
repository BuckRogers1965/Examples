#include <stdio.h>

/* Given a set of strings, create a search tree of values */

typedef struct Node {

        unsigned long Value;
        struct Node * Child[4];

} Node;

Node * AllocNode(){

	Node * Root;
	int i;

//	printf(".");

        // create the nodes, zeroed memory;
        Root = (Node *)calloc(sizeof(Node), 1);
	if (Root == 0) 
		return 0;

        // initialize the first new node
	for (i=0; i<4; i++)
        	Root->Child[i] = 0;
        Root->Value = 0;
	
	return Root;
}

int getBPValue(char basepair){

	switch (basepair){
		case 'A':
			return 0;
		case 'T':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;
	}

	return -1;
}

int Insert (Node * Root, char * String, int length){

	Node * Current;
	int i, basepair;

	Current = Root;
	Current->Value++;

//printf("%s\n", String);
	for (i=0; String[i] && i < length; i++){
		basepair = getBPValue(String[i]);
		if (basepair !=-1){
			if (!Current->Child[basepair]){
				Current->Child[basepair] = AllocNode();
				if (!Current->Child[basepair]){
					fprintf(stderr,"No more memory\n"); 
					exit(1);
				}
			}
//			printf("+");
			Current = Current->Child[basepair];
			Current->Value++;
		}
	}
}

#define LENGTH 12

long depth = 0;
char result[LENGTH+1];

void AnalyseTree(Node * Strand){

	int i,j;
	char basepairs [4]= {'A','T','C','G'};

	if (!Strand)
		return;
	
	depth++;

	for (i=0; i<4; i++){
		if (Strand->Child[i]){
			result[depth-1]=basepairs[i];
			result[depth]=0;
			if (Strand->Child[i]->Value > LENGTH)
				printf("%d	%s\n", Strand->Child[i]->Value, result);
			AnalyseTree(Strand->Child[i]);
		}
	}
	
	
	depth--;
}

int main (){

	Node * Strand;
	int i;
	int j=0;
	int current;
	int basepair;
	char string[LENGTH+1];

	Strand = AllocNode();
/*
	for (i=0; i<4; i++){
		Strand->Child[i]=AllocNode();
	}

	for (i=0; i<4; i++){
		Strand->Child[0]->Child[i]=AllocNode();
		Strand->Child[1]->Child[i]=Strand->Child[0]->Child[i];
		Strand->Child[2]->Child[i]=Strand->Child[0]->Child[i];
		Strand->Child[3]->Child[i]=Strand->Child[0]->Child[i];
	}

	/* preload the string */
	while ((current = getchar()) !=EOF){

		basepair = getBPValue(current);

		if (basepair != -1){
			string[j]=current;
			j++;
			if (j > LENGTH-1){
				string[j]=0;
				break;
			}
		}
	}

	Insert(Strand, string, i);

	while ((current = getchar()) !=EOF){
		//printf("%c ", current);
		
                basepair = getBPValue(current);

                if (basepair != -1){
			memcpy(string, string+1, LENGTH-1);
                        string[LENGTH-1]=current;
			Insert(Strand, string, LENGTH);
                }
	}

	AnalyseTree(Strand);

	return 0;
}

