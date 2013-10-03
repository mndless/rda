//////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////

int sumOfDivisors(int number);
int factorial (int number);
void printResult (int num1, int num2, int num3);

int main() {
    int value=1;            // collect user entered int value
    while (value >= 1) {
        printf ("==== Enter a positive integer (zero to quite): ====\n");
        scanf  ("%i", &value);
        if (value >= 1) {
            int sumOfDivisor = sumOfDivisors(value);
            int factorials = factorial(value);
            printResult(value, sumOfDivisor, factorials);
        } else {
            if (value < 0) {   // bad data
                printf ("*** incorrect input ***\n\n");
                value = 1; // reset to stay in while loop
            } // end if value < 0
        }// end if value
    } // end while value
} // end main

int sumOfDivisors(int number) {
    int sum = 0;
    int div;
    int i;
    for (i=1; i <= number; i++) {
        div = number%i;
        if (div == 0) {
            sum = sum + i;
        } // end if div = 0
    } // end if int i
    return(sum);
} // end function sumOfDivisors

int factorial (int number) {
    int fact=1;
    int i;
    for (i=number; i >= 1 ; i--) {
        fact = fact * i;
    } // end if i
    return(fact);
} // end function factorial

void printResult (int num1, int num2, int num3) {
    printf ("\nThe sum of the divisors for %i is %i, ", num1, num2);
    if ((num1*2) > num2) {
        printf (" which is Abundant\n");
    } else if ((num1*2) < num2) {
        printf (" which is Deficient\n");
    } else if ((num1*2) == num2) {
        printf (" which is Perfect\n");
    } // end if
    printf ("The factorial of the number %i is: %i\n\n", num1, num3);
} // end function printResult
