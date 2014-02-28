typedef struct Que Que;
struct Que
{
  long double x;
  int depth;
  Que *next;

} myQue;


Que *
QCreate ();

void
Push (Que * queue, long double value);

long double
Pop (Que * queue);

int
QDepth (Que * queue);

