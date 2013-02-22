#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
//void exit( int exit_code );

void Expression();
void Expected(char *);

#define TAB = '\t';

char *Look;  /* Lookahead Character */

struct node {
   char symbol;
   int value;
   struct node *right;
   struct node *left;
} node_size;
typedef struct node *NODEPTR;

void push(struct node *node, int value);

struct node *stored; 
struct node * head = NULL;
struct node *freeList = NULL;

struct node * NewNode (){
   struct node *new;
   if (!freeList) {
      freeList = malloc (sizeof(node_size));
      freeList->right = NULL;
   }
   if (!freeList->right){
      new = malloc (sizeof(node_size));
   } else {
      new = freeList;
      freeList = freeList->right;
   }
   new->symbol='\0';
   new->value=0;
   new->right = NULL;
   new->left = NULL;
   return new;
}

void DelNode (struct node * node){
   if (!node)
      return;
   DelNode(node->right);
   node->right = NULL;
   DelNode(node->left);
   node->left = NULL;
   //free(node);
   node->right=freeList;
   freeList=node;
}

struct node * InitStack(){
	return NewNode();
}

void push(struct node *node, int value){

	struct node * temp;
	temp = NewNode();
	temp->value=value;
        temp->right = node->right;
	node->right = temp;
}

int pop(struct node *stack){
	struct node *current = stack->right;
	int value;
        if (!current) {
printf("\n\"");
PrintTree (head);
printf("\"\n");
      Expected("Stack Underflow Not ");
	    return 0;
}
	value = current->value;
	stack->right = current->right;
	current->right = NULL;
	DelNode(current);
	return value;
}

void InsertValue(int value){

   struct node * current = stored;
   struct node * temp;

   while (current->right && current->value != value && current->right->value < value)
      current=current->right;

   if (current->right && current->value == value || current->right && current->right->value == value)
      return;

   stored->value++;
   temp = NewNode();
   temp->value = value;
   temp->right = current->right;
   current->right=temp;
}

void PrintValue(){
   struct node * current = stored;
   printf (" %d unique { ", current->value);
   while (current && current->right){
      current=current->right;
      printf ("%d", current->value);
      if (current->right)
         printf(", ");
   }
   printf("}\n");
}
                              
void GetChar() {
   Look++;
}

int IsWhite(char c){
   return isspace(c);
}

void SkipWhite (){
   while (IsWhite(Look[0])) 
      GetChar();
}

void Init(char *s){
   Look=s;
   SkipWhite();
}

void Expected(char * s){
   printf("Error %s Expected.", s);
   exit (1);
}

void Match(char x){
   if (Look[0] == x){
      GetChar();
      SkipWhite();
   } else {
      char error[4];
      error[0]='\'';
      error[0]=x;
      error[0]='\'';
      error[0]='\0';
      Expected(error);
   }
}

int IsDigit(char c){
   return isdigit(c);
}

int GetNum (){
   int x=0;
   if (!IsDigit(Look[0]))
      Expected("Integer");
   while (IsDigit(Look[0])){
      x = x*10 + Look[0]-'0';
      GetChar();
   }
   SkipWhite();
   return x;
}

int IsSymbol(char c){
   switch(c){
      case '+':
      case '-':
      case '*':
         return 1;
         break;
      default:
         return 0;
   }
}

char GetSymbol(){
   char c;
   if (!IsSymbol(Look[0]))
	Expected("Symbol");
   c = Look[0];
   GetChar();
   SkipWhite();
   return c;
}

struct node *ParseInput(){
   struct node * head = NewNode();
   head->value = GetNum();
   head->symbol = 'n';
   while(Look[0]){
      struct node * temp;

      temp=NewNode();
      temp->symbol = GetSymbol();
      temp->right=head;
      head = temp;

      temp=NewNode();
      temp->value = GetNum();
      temp->symbol = 'n';
      head->left=temp;
   }
   return head;
}

int PrintTree (struct node * node){
   if (!node)
      return;
   PrintTree(node->right);
   PrintTree(node->left);
   if (node->symbol == 'n')
       printf(" %d ", node->value);
   else
       printf(" %c ", node->symbol);
   fflush(stdout);
}

int ct(struct node *node, struct node *result){
   if (!node)
      return;
   ct(node->right, result);
   ct(node->left, result);
   if (node->symbol != 'n'){
	int x = pop (result);
	int y = pop (result);
	switch (node->symbol) {
	case '-':
		push (result, y-x);
		break;
        case '+':
		push (result, y+x);
		break;
	case '*':
		push (result, y*x);
		break;
	 default:
		break;
        } 
   } else {
      push (result, node->value);
   }
}

int walkright(struct node * );

int walkleft(struct node * node){

   struct node * result;

   struct node * temp = node->left;
   struct node * current;
   if (!temp || !temp->left || temp->left->symbol == 'n')
	return 0;

   current=temp->left;

   node->left = current;
   temp->left = current-> right;
   current->right= temp;

   walkright(head);
   walkleft(head);

   walkright(current);
   walkleft(current);

   result = InitStack();
   ct(head, result);
   InsertValue(pop(result));
   DelNode(result);

   node->left=temp;
   current->right = temp->left;
   temp->left = current;   

   return 1;
}


int walkright(struct node * node){

   struct node * result;

   struct node * temp = node->right;
   struct node * current;
   if (!temp || !temp->right || temp->right->symbol == 'n')
	return 0;

   current=temp->right;

   node->right = current;
   temp->right = current-> left;
   current->left= temp;

   walkleft(head);
   walkright(head);

   walkleft(current);
   walkright(current);

   result = InitStack();
   ct(head, result);
   InsertValue(pop(result));
   DelNode(result);

   node->right=temp;
   current->left = temp->right;
   temp->right = current;   

   return 1;
}

int CalcTree(){

    struct node * result = InitStack();

    ct(head, result);
    InsertValue(pop(result));
    DelNode(result);

    walkright(head);
    walkleft(head);
}

void TraverseTree(struct node * current){

     int x = 0;
     head = current;

    CalcTree();

    while (current->right && current->right->symbol != 'n'){

        current = head->right;
        head->right = current->left;
        current->left = head;
        head = current;

        CalcTree();
    }
}

void parenPermutations(char *s){
   struct node * result = NULL;

   Init(s);
   head = ParseInput();
   stored = InitStack();

   TraverseTree(head);
   PrintValue();

   DelNode(stored);
   DelNode(head);
}

int
main (){

   int i;
   for (i=0; i< 1000000; i++){ 
   parenPermutations("1 + 2 + 3 * 4 - 5 * 2");
   parenPermutations("1 + 2 - 3 * 4");
   parenPermutations("1 - 1 + 1");
   parenPermutations("10");
   }
}
