#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// Define the type answer_t
typedef union {
  int int_value;
  float float_value;
  char *string_value;
} answer_t;

// Define function pointer types
typedef bool (*check_func)(char *);
typedef answer_t (*convert_func)(char *);

// Function prototypes
extern char *strdup(const char *); //  The extern keyword is used to indicate that the function strdup is declared but not defined in the current source file It returns a pointer to the duplicated string 
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
bool is_float(char *str);
bool not_empty(char *str);
answer_t ask_question(char *question, check_func check, convert_func convert);
char *ask_question_string(char *question);
int ask_question_int(char *question);
double ask_question_float(char *question);

#endif /* UTILS_H */
