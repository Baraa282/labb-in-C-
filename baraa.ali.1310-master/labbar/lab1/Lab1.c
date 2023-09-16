
//Hello World 
/*#include <stdio.h>
int main (void){
    puts("Hello , World !");
    return 0;
}*/

//---------------------------------------------------


/*#include <stdio.h>
int main (void){
char *msg = "Hello , World !";
int year = 2020;
printf("%s in the year %d \n " , msg , year);
}*/

//----------------------------------------------------

//3.1 - Mini-Övning
/* #include <stdio.h>

int main(void)
{
  int x = 1;
  int y = 2;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  puts("=====");
  int tmp = x ;
  x = y ;
  y = tmp;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  return 0;
}*/

//------------------------------------------------------

// 4. skriva ut talföjden 1-10

/*#include<stdio.h>
int main (void){
    for (int i=1;i<=10;i++ ){
        printf("%d\n", i);
        }
    return 0;
}*/

//----------------------------------------
// 5-Skriv ut talföljden 10–1
/*#include<stdio.h>
int main (void){
    for (int i=10;i>=1;i-- ){
        printf("%d\n", i);
        }
    return 0;
}*/

//-----------------------------------------------


//6. Nästade loopar
/*#include<stdio.h>
int main (void) {
    for (int i=1 ; i <= 10 ; i++){
        for (int j = 1 ; j <= i ; j++){
            printf ("*");
        }
        printf ("\n");

    }
    return 0 ;
}*/

//---------------------------------------------------------

//7-Kommandoradsargument 1/2





//-----------------------------------
//8- Primtalstes
/*#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) {
        return 0; // Numbers less than or equal to 1 are not prime
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0; // If n is divisible by any number between 2 and sqrt(n), it's not prime
        }
    }
    return 1; // If no divisor is found, the number is prime
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]); // Convert the argument to an integer

    if (is_prime(num)) {
        printf("%d is a prime number\n", num);
    } else {
        printf("%d is not a prime number\n", num);
    }

    return 0;
}*/


//-----------------------------------------------------------
// Största gemensamma delare (GCD):
/* #include <stdio.h>
#include <stdlib.h> // Include this for atoi function

// Funktion för att beräkna gcd med Euklides algoritm
int gcd(int a, int b) {
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a; // eller b (de är lika vid detta skede)
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s number1 number2\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]); // Convert the first argument to an integer
    int num2 = atoi(argv[2]); // Convert the second argument to an integer

    if (num1 <= 0 || num2 <= 0) {
        printf("Input numbers must be positive.\n");
        return 1; // Avsluta programmet med felkod
    }

    // Beräkna största gemensamma delaren med hjälp av Euklides algoritm
    int result = gcd(num1, num2);

    // Skriv ut resultatet
    printf("gcd(%d, %d) = %d\n", num1, num2, result);

    return 0; // Avsluta programmet med lyckad kod
}*/


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_number(char *str)
{
    int length = strlen(str);

    
    if (length == 0)     
        return false;

    
    if (str[0] == '-')
        str++; 
    
    if(strlen(str) == 0){
        return false;
    }

    
    for (int i = 0; i < strlen(str); i++)
    {
        
        if (!isdigit(str[i]))
            return false;
    }

    
    return true;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (is_number(argv[1]))
        {
            printf("%s is a number\n", argv[1]);
        }
        else
        {
            printf("%s is not a number\n", argv[1]);
        }
    }
    else
    {
        printf("Please provide a command line argument!\n");
    }

    return 0;
}
















