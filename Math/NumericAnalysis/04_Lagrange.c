
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


/*

	James M. Rogers

	

	For this we have the concept of a list of points.


*/

typedef struct Point Point;

struct Point
{

  long double x;
  long double y;
  Point *next;

} myPoint;


Point *
AddPoint (Point * head, long double x, long double y)
{

  Point *newP = (Point *) malloc (sizeof (Point));

  newP->x = x;
  newP->y = y;
  newP->next = head;

  return newP;

}

Point *
FreePoints (Point * Head)
{

  Point *Next = Head->next;
  if (!Next)
    return NULL;

  free (Head);

  return (FreePoints (Next));

}

void
PrintPoints (Point * Head)
{

  Point *Curr = Head;
  int n = 0;

  while (Curr)
    {
      printf ("%d  %Lf  %Lf\n", n, Curr->x, Curr->y);
      Curr = Curr->next;
    }

}

long double
FindTerm (Point * Head, Point * Skip, long double x)
{

  Point *Curr = Head;

  long double n = 1;
  long double d = 1;

  while (Curr)
    {
      if (Curr == Skip)
	goto skipcurrent;
      n *= (x - Curr->x);
      d *= (Skip->x - Curr->x);
    skipcurrent:
      Curr = Curr->next;
    }
  return n / d;
}

long double
FindSolution (Point * Head, long double x)
{

  long double result = 0;
  Point *Curr = Head;

  while (Curr)
    {
      result += FindTerm (Head, Curr, x) * Curr->y;
      Curr = Curr->next;
    }
  return result;
}

void
main ()
{

  long double i;
  Point *Head = NULL;
//  Head = AddPoint(Head, 2,   0.5);
//  Head = AddPoint(Head, 2.5, 0.4);
//  Head = AddPoint(Head, 4,   0.25);

  for (i = .1; i < 5; i = i + .101)
    {
      Head = AddPoint (Head, i, 1 / i);
    }



  //PrintPoints(Head);

  long double y = FindSolution (Head, 3);

  printf ("Result for 3 is %30.20Lf\n", y);

  Head = FreePoints (Head);

}
