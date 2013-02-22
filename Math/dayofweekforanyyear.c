#include <stdio.h>
#include <stdlib.h>

/* given any date, give the day of the week

   date can be in form of 
        
   	day month year
   
  Later, add ability to parse other date formats
  and things like now, today, etc.  

  This generic date converter will be useful for many things.

  year 1900 has an offset of 0, this is useful
  Take someone born in 1965 
  1965 - 1900 = 65
  65 is 5 short of 70, which leaves 2
  65/4 = 16 with a remainder of 1. 
  drop 14 because it is a multiple of 7 which leaves 2
  
  2 for year + 2 for leap years + 9 for day  + 6 for month = 19
  drop 14 from that which leaves 5, 
  So I was born on a Thursday.
*/

#define SAT 0
#define SUN 1
#define MON 2
#define TUE 3
#define WED 4
#define THU 5
#define FRI 6

#define JAN 1
#define FEB 4
#define MAR 4
#define APR 0
#define MAY 2
#define JUN 5
#define JUL 0
#define AUG 3
#define SEP 6
#define OCT 1
#define NOV 4
#define DEC 6

char * day_of_week[7] ={"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  };

char * months_of_year[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

int monthoffset[12] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

int
getdow(int day, int month, int year){
  int result = year - 1900 ;
  result = result + result/4 + day + monthoffset[month] ; 
  result %= 7;
  return (result);
} 
 
int
main(){
  printf("Me   %s\n", day_of_week[getdow(9, 9-1,  1965)]);
  printf("Mom  %s\n", day_of_week[getdow(4, 10-1, 1948)]);
  printf("Bill %s\n", day_of_week[getdow(5, 1-1,  1941)]);
  printf("Future %s\n", day_of_week[getdow(1, 1-1, 2041)]);
  exit(0);
}

