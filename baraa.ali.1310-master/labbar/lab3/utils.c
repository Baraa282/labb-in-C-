#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


char *strdup(const char *str) {
  char *copy = (char *)malloc(strlen(str) + 1);//This line allocates memory dynamically for the duplicate string. It calculates the length of the input string str using strlen(str) and adds 1 to account for the null-terminator  
  if (copy) { // if statement checks if the memory allocation was successful
    strcpy(copy, str); // Inside the block, the strcpy function is used to copy the contents of the original string str into the copy string
  }
  return copy; // Finally, the function returns a pointer to the duplicate string, which is now a separate copy of the input string. 
}

int read_string(char *buf, int buf_siz) { 
  if (fgets(buf, buf_siz, stdin) == NULL) { //the fgets function to read a line of text from the standard input (stdin) and store it in the buf character array.
    return 0; // Input error or EOF
  }
  buf[strcspn(buf, "\n")] = '\0'; // Remove newline character - strcspn to find the index of the first newline character ('\n') in the buf string and replaces it with the null-terminator ('\0'). 
  return 1;
}

bool is_number(char *str) {
  char *endptr; // Declare a pointer to char called endptr
  (void)strtof(str, &endptr); // Convert the string to a float and set endptr to the stopping position
  return !(*endptr != '\0' && *endptr != '\n');   // Check if endptr is at the end of the string
}

bool is_float(char *str) {
  char *endptr;
  (void)strtod(str, &endptr);
  return !(*endptr != '\0' && *endptr != '\n');
}

bool not_empty(char *str) {
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
  char buf[256];
  answer_t result;

  do {
    printf("%s\n", question);
  } while (!read_string(buf, sizeof(buf)) || !check(buf));

  result = convert(buf);

  return result;
}

char *ask_question_string(char *question) {
  return ask_question(question, not_empty, (convert_func)strdup).string_value;
}

int ask_question_int(char *question) {
  return ask_question(question, is_number, (convert_func)atoi).int_value;
}

double ask_question_float(char *question) {
  return ask_question(question, is_float, (convert_func)strtod).float_value;
}



