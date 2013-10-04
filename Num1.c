#include <stdio.h>

int sumOfDivisors (int number);
int factorial (int number);
void printResult (int num1, int num2, int num3);

int main(void) {

   int x;

   printf("Enter a positive integer (or zero to quit):\n");
   scanf("%d",&x);

   sumOfDivisors(x);
   factorial(x);
   printResult();


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
   
}  // end printResult

