#include <stdio.h>


void swap(int *a, int *b) {
    int temp = *a;     // cteate a temp variabel to hold the value of a 
    *a = *b;         // assign the value of b to a 
    *b = temp;      // assign the value of tem to b 
}

int main() {
    int x = 42;
    int y = 7;

    printf("before swap: x = %d, y = %d\n", x, y);

    
    swap(&x, &y); // call the swap function with pointers

    printf("after swap: x = %d, y = %d\n", x, y);

    return 0;
}



