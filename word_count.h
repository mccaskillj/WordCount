/*
* word_count.h
* Jordan McCaskill
* CMPT360
* Assignment 1
* Includes and function prototypes for main program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"

/*
* Function prototypes
*/
void parse(FILE *file, struct main_list *dictionary);
int check_digits(char *word);
int check_punc_outer(char *word);
