/*
* lists.c
* Jordan McCaskill
* CMPT360
* Assignment 1
* Functions which deal with the creation, printing and deleting the
*	linked list
*/
#include "lists.h"

/*
* create_node()
* Given a pointer to a char array, creates a new node for the list
*/
struct main_node *create_node(char *word)
{
	struct main_node *new_node = malloc(sizeof(struct main_node));

	// Check the memory allocation for success
	if (new_node == NULL) {
		FAILURE;
		exit(1);
	}

	new_node->word = word;
	new_node->number = 1;
	new_node->next = NULL;
	new_node->prev = NULL;

	// Check the memory allocation for success
	if (new_node->word == NULL) {
		FAILURE;
		exit(1);
	}

	return new_node;
}

/*
* compare()
* Compares the word to the existing list location to determine whether
*	to add a new node or increment a counter
*/
int compare(struct main_list *my_list, struct main_node *pos, char *word)
{
	int comp = strcmp(word, pos->word);

	if (comp < 0) {
		struct main_node *new_node = create_node(word);

		new_node->next = pos;
		new_node->prev = pos->prev;
		if (pos->prev != NULL)
			pos->prev->next = new_node;
		pos->prev = new_node;
		if (pos == my_list->first)
			my_list->first = new_node;
	} else if (comp == 0) {
		pos->number += 1;
		free(word);
	} else {
		struct main_node *new_node = create_node(word);

		new_node->prev = pos;
		pos->next = new_node;
	}

	return 0;
}

/*
* append()
* Add the value of the word to the list either by incrementing a counter
*	or adding a new node to the list
*/
int append(struct main_list *my_list, char *word)
{
	// If the list is empty set the first node to newNode
	if (my_list->first == NULL)
		my_list->first = create_node(word);
	// If the list is not empty set the last node next value to the newNode
	else {
		struct main_node *pos = my_list->first;

		for (; pos->next != NULL &&
			strcmp(word, pos->word) > 0; pos = pos->next)
			;

		compare(my_list, pos, word);
	}

	return 0;
}

/*
* print_list()
* Loop through the linked lists and print off all the words and their
*	number of occurances and then free all the char arrays and structs
*/
int print_list(struct main_list *my_list)
{
	struct main_node *pos = my_list->first;
	struct main_node *next_pos = my_list->first->next;

	for (; pos != NULL && next_pos != NULL;
		pos = next_pos, next_pos = pos->next) {

		printf("%8d %s\n", pos->number, pos->word);
		free(pos->word);
		pos->word = NULL;
		free(pos);
	}
	printf("%8d %s\n", pos->number, pos->word);
	free(pos->word);
	free(pos);

	return 0;
}
