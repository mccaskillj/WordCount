/*
* lists.h
* Jordan McCaskill
* CMPT360
* Assignment 1
* Structs, includes, and function prototypes for linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE printf("ERROR ALLOCATING MEMORY")

/*
* Struct for the nodes which hold the word data in the list
*/
struct main_node {
	char *word; // Array for instruction
	int number;
	struct main_node *next; // Pointer to the next node
	struct main_node *prev;
};

/*
* Struct for the header of the list
*/
struct main_list {
	struct main_node *first; // Pointer to first node in the list
};

/*
* Function prototypes
*/
struct main_node *create_node(char *word);
int compare(struct main_list *my_list, struct main_node *pos, char *word);
int append(struct main_list *my_list, char *word);
int print_list(struct main_list *my_list);
