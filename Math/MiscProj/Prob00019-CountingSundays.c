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
  if (year % 4 == 0 && month <= 1) result -= 1;
  result %= 7;
  return (result);
} 
 
#define END 2000
int
main(){
  int year = 1901,
      month,
      day = 1,
      result = 0;

  for (; year<=END; year++)
    for (month=0; month <12; month++)
      if (getdow(day, month, year) == SUN) {
//        printf ("1 %s %d was a %s\n", months_of_year[month], year, day_of_week[day] );
	result++;
      }

  printf("Solution is %d\n", result);
}

