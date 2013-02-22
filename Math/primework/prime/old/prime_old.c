
#include "stdio.h"
#include "math.h"

int number;

main()
{
        printf("Which number do you wish to start the test with? ");
        scanf("%d",&number);
        printf("\n");
        printf("I'm starting with number %d\n",number);
        if (number<1) number=1;
        if (number==1) printf("1\n");
        if (number<=2) printf("2\n");
        if (!(number % 2)) number++;
        if (number==1) number=3;
        do
        {
                if (isprime(number)) printf("%d\n",number);
                number+=2;
        }while (number<5000000) ;
}

isprime(int thenumber)
{
        int isitprime=1,loop;
        for(loop=3 ; (isitprime) && (loop<(sqrt(thenumber)+1)) ; loop+=2)
                isitprime = (thenumber % loop);
        return(isitprime);
}

