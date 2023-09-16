#include <stdio.h>
#include <string.h>


int read_string(char *buf, int buf_siz) {    //the pointer char array that spicfy where the read string should be stored
    int i;                         //keep track of the current position 
    int c;                            // store char read 

    // Läs in strängen tecken för tecken
    for (i = 0; i < buf_siz - 1; i++) {
        c = getchar(); //read each char untill newline or end of file
        // Om vi når '\n' eller EOF, avsluta inläsningen
        if (c == '\n' || c == EOF) {
            break;
        }

        // Annars, lagra tecknet i bufferten
        buf[i] = (char)c; // storing the char read fron input into the char buffer
    }

    // Nullterminera strängen
    buf[i] = '\0';

    // Töm eventuell överskottsinformation i inmatningsbufferten
    if (c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF);
    }

    return i;
}

int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n');
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}


char *ask_question_string(char *question, char *buf, int buf_siz) {
    char *result;
    int read;

    do {
        printf("%s\n", question);
        read = read_string(buf, buf_siz);

        if (read == 0) {
            printf("Please enter a non-empty string.\n");
        }
    } while (read == 0);

    // Allocate memory for the result and copy the string
    result = strdup(buf);

    return result;
}

