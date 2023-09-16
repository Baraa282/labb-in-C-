#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

int main(void) {
    
    srand(time(NULL)); // Initialize the random number generator with the current time .

    char name[255];
    int target = random () % 1024 ; // Generates a random number between 1 and 1023
    int guess;
    int attempts = 0;

    printf("Enter your name\n ");
    read_string(name, sizeof(name));

    printf("Hi %s, I'm thinking of a number... Can you guess it?\n", name);

    while (1) {
        guess = ask_question_int("");

        if (guess < target) {
            printf("Too low!\n");
        } else if (guess > target) {
            printf("Too high!\n");
        } else {
            printf("Bingo!\n");
            break;
        }

        attempts++;

        if (attempts >= 15) {
            printf("You've run out of guesses! I was thinking of %d!\n", target);
            break;
        }
    }


    return 0;
}
