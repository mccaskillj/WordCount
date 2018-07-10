/*
* word_count.c
* Jordan McCaskill
* CMPT360
* Assignment 1
* main program which deals with the parsing of the data in the input file
*	and the creation and deletion of the main list
*/

#include "word_count.h"

/*
* Main program function which checks for files and starts the parsing
*	if file is found
*/
int main(int argc, char *argv[])
{
	struct main_list *dictionary = malloc(sizeof(struct main_list)*26);

	FILE *file = NULL; // file pointer

	if (argv[1]) {
	file = fopen(argv[1], "rt");
	} else {
		printf("Usage: ./word_count <filename>\n");
		return 1;
	}

	if (file == NULL) {
		printf("File not found\n");
		exit(0);
	}

	parse(file, dictionary);

	if (file != NULL)
		fclose(file);

	for (int i = 0; i < 26; i++) {
		if ((&dictionary[i])->first != NULL)
			print_list(&dictionary[i]);

	}
	free(dictionary);

	return 0;
}

/*
* Parse the input from the file and store it on the linked list
*/
void parse(FILE *file, struct main_list *dictionary)
{
	char *input_word = malloc(sizeof(char)*1000);
	char *word;
	int eval;
	int len;

	while (fscanf(file, "%999s", input_word) == 1) {
		len = strlen(input_word);
		word = malloc(sizeof(char)*(len+1));
		strncpy(word, input_word, len+1);
		eval = 1;
		for (int i = 0; word[i]; i++)
			word[i] = tolower(word[i]);
		eval = eval * check_punc_outer(word);
		eval = eval * check_digits(word);

		if (eval == 1)
			append(&dictionary[word[0] - 'a'], word);
		else
			free(word);
	}
	free(input_word);
}

/*
* Check for numbers and unallowed internal characters in a word
*	return 0 for not allowed and 1 for allowed
*/
int check_digits(char *word)
{
	if (strpbrk(word,
		"!\"#$&()*+[]{}|\\/:;,<.>@%^=`~0123456789") != NULL) {
		return 0;
	}
	if (strchr(word, '\'') != strrchr(word, '\'') ||
		strchr(word, '-') != strrchr(word, '-')) {
		return 0;
	}
	return 1;
}

/*
* Check the outer punctuation of a word and remove it if not allowed
*	then return 0 if word is not allowed and 1 if allowed
*/
int check_punc_outer(char *word)
{
	int len = strlen(word);

	if (len == 1) {
		if (word[0] >= 97 && word[0] <= 122)
			return 1;
		return 0;
	}
	for (int i = len-1; i >= 0 &&
		(word[i] > 122 || word[i] < 97); i--) {
		word[i] = '\0';
	}
	while (word[0] && (word[0] > 122 || word[0] < 97))
		for (int i = 0; word[i]; i++)
			word[i] = word[i+1];

	if (word[0] == '\0')
		return 0;
	return 1;
}
