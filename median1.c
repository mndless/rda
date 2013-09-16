/*  Header info  */


#include <stdio.h>

int main(void) {

   int debug=1;     // not used, delete
   int looping=1;   // flag, loop until cleared
   int a, b, c;     // int values entered
   float avg;       // the average of the int values
   int temp;        // temp holding
   int chg;         // flag, if changed during sort
   int resp;        // response, continue ?


// loop until the looping flag is cleared by user response 0
   while(looping==1){

        printf("Enter your first integer:\n");
        scanf("%i", &a);
        printf("Enter your second integer:\n");
        scanf("%i", &b);
 printf("Enter your last integer:\n");
        scanf("%i", &c);

// set chg to 1... loop until nothing has changed
        chg=1;

// loop for sort int into decreasing order
        while(chg==1) {

// if nothing changes, chg flag will be 0
           chg=0;

// re-order a and b
            if(a<b) {
 temp = a;
                a = b;
                b = temp;
                chg = 1;

           } // end of if a and b

// re-order b and c
           if(b<c) {

                temp = b;
                b = c;
                c = temp;
                chg = 1;

           }  // end of if b and c

        }  // end of chg while

// calc avg and cast ints to float
        avg = (float)(a + b + c)/3;

 printf("The median of your three integers %d, %d, %d is: %d\n", a, b, c, b);

        printf("The average of your three integers %d, %d, %d is: %5.1f\n", a, b, c, avg);

        printf("Would you like to continue? Enter 1 for yes, 0 for no.");
        scanf("%d", &resp);

        if(resp==0) {

           looping = 0;     // clear looping flag and exit

        } // end of resp if

   }  // end of looping  while

return 0;

}  // end of main
