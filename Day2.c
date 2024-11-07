#include <stdio.h>
 
void main( ) {
    int number1, number2, number3;
    int largest;
 
   
    printf("Enter three numbers: ");
    scanf("%d %d %d", &number1, &number2, &number3);
 
   
    if (number1 >= number2 && number1 >= number3) {
        largest = number1;
    } else if (number2 >= number1 && number2 >= number3) {
        largest = number2;
    } else {
        largest = number3;
    }
 
  
    printf("The largest number is: %d\n", largest);
 
    
}