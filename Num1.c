//~ comments 100413
//~ Programming Assignments General Requirements (PAGR)
//~ General Assignment Grading Rubric (GAGR)
//~ Programming Assignment 2 (PA2)

#include <stdio.h>

int sumOfDivisors (int number);
int factorial (int number);
void printResult (int num1, int num2, int num3);

int main(void) {

//
//~  See PAGR 2.d and GAGR, 5pts  x is descriptive ?
//~  Is a variable declaration here considered a global variable? 
//

   int x;	

   printf("Enter a positive integer (or zero to quit):\n");

//
//~  according to PA2, page 3, is should look like the below
//~  printf ("==== Enter a positive integer (zero to quit): ====\n");
//

   scanf("%d",&x);

//
//~ how are you catching the '0' to exit?

//~ how are you handling incorrect data entry - PA2, page 3?
//

   sumOfDivisors(x);
   factorial(x);
   printResult();

//
//~ after this runs one time, how are you propting for next entry? PA2, page 3?
//

}  // end of main

int sumOfDivisors (int number) {

   int sum=0;
   int i;

   for (i=1; i<=number; i++) {

        if (number%i==0) {

           sum+=1;

        }  // end if num%i

   }  // end for i=1

   return sum;
}  // end sumOfDivisors

int factorial (int number) {

   int i;

   for (i=1; i<number; i++) {
       
         number *= i;

   }  // end for i=1

   return number;
   
}  // end factorial
   
void printResult (int num1, int num2, int num3) {

   if (num1<2*num2) {
        printf("The sum of the divisors for %d is: %d which is deficient\n",
        num1, num2);
   }  // end if num1<2*num2
   else if (num1>2*num2) {
        printf("The sum of the divisors for %d is: %d which is abundant\n",
        num1, num2);
   }  // end else if num1>2*num2
   else {
        printf("The sum of the divisors for %d is: %d which is perfect\n",
        num1, num2);
   }  // end else

//
//~ you aren't printing the factorial, PA2, page 3
//  
 
}  // end printResult

