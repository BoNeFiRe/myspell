//======================================================== file = myspell.c ===
//= Program that spell checks a given text file                                =
//==============================================================================
//=  Author: Matthew Levandowski                                               =
//=          Email: levandma@gvsu.edu                                          =
//=          Grand Valley State University                                     =
//=          CIS 363                                                           =
//==============================================================================
//----- Include files ----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "binarysearch.h"
#include "linearsearch.h"
#include "hashsearch.h"

//----- Constant defines -------------------------------------------------------
#define BUFSIZE 1024
#define MAX_WORD_LENGTH 23

//----- Global variables -------------------------------------------------------
char buffer[BUFSIZE];
char dict_file[] = "american-english";
char *in_file;
char out_file[] = "myout.txt";
FILE *dict_fptr;
FILE *input_fptr;
FILE *output_fptr;
char **dict = NULL;
char **input = NULL;
int dict_size; // # of strings in dictfile
int input_size; // # of strings in inputfilec
int j; // counter variable

//----- Function prototypes ----------------------------------------------------
bool load_dict_array(FILE *fp);
bool load_input_array(FILE *fp);
void tokenize(char *str);
void string_lower(char *src, char * dst);
void remove_puncs(char *src, char *dst);
void dobinary();
void dohash();
void dolinear();

//==============================================================================
//=  Main program                                                              =
//==============================================================================
int main(int argc, char **argv) {
	int opt = 0;
	int choice = 0;

	// check for input filename
	if (argc == 3) {
		in_file = argv[2];
	}

	while ((opt = getopt(argc, argv, "bhl:")) != -1) {
		switch (opt) {
		case 'b':
			choice = 'b';
			break;
		case 'h':
			choice = 'h';
			break;
		case 'l':
			choice = 'l';
			break;
		case '?':
			choice = 'h';
			//print_help(1);
			//exit(0);
		}
	}

	// open dictionary file
	dict_fptr = fopen(dict_file, "r");
	if (dict_fptr == NULL) {
		printf("*** ERROR in opening dictionary file (%s) *** \n", dict_file);
		exit(1);
	}

	// open input file
	input_fptr = fopen(in_file, "r");
	if (input_fptr == NULL) {
		printf("*** ERROR in opening input file #2 (%s) *** \n", in_file);
		exit(1);
	}

	output_fptr = fopen(out_file, "w");
	if (output_fptr == NULL) {
		printf("*** ERROR in opening output file (%s) *** \n", out_file);
		exit(1);
	}

	// print input header
	printf("My Spell Checker---------------------------------------- \n");

	// read dictionary file into memory
	load_dict_array(dict_fptr);

	// read input file into memory
	load_input_array(input_fptr);

	// Output results header
	printf("-------------------------------------------------------- \n");

	// perform search and output to file
	switch (choice) {
	case 'b':
		dobinary();
		break;
	case 'h':
		dohash();
		break;
	case 'l':
		dolinear();
		break;
	default:
		break;
	}

	// Output closing trailer
	printf("-------------------------------------------------------- \n");

	// cleanup
	//fcloseall();
	return 0;
}

void dolinear() {
	char *word;
	for (j = 0; j < input_size; j++) {
		word = input[j];
		if (!linear_lookup(word, dict_size, dict)) {
			// open output file
			printf("%s not found\n", word);
			fprintf(output_fptr, "%s\n", input[j]);
		}
	}
}

void dobinary() {
	char *word;
	for (j = 0; j < input_size; j++) {
		word = input[j];
		if (!binary_lookup(word, dict_size, dict)) {
			// open output file
			printf("%s not found\n", word);
			fprintf(output_fptr, "%s\n", word);
		}
	}
}

void dohash() {
	int hkey = 0;
	char *word;
	hash_table_t *ht = create_hash_table(dict_size);
	for (j = 0; j < dict_size; j++) {
		hkey = hash(dict[j]);
		add_string(ht, dict[j]);
	}
	for (j = 0; j < input_size; j++) {
		word = input[j];
		if (hash_lookup(ht, word) == NULL) {
			// open output file
			printf("%s not found\n", word);
			fprintf(output_fptr, "%s\n", word);
		}
	}
}

//------------------------------------------------------------------------------
//-  Function that converts a string to lower case and removes punctuations    -
//------------------------------------------------------------------------------
void remove_puncs(char *src, char *dst) {
	// remove puncs from beginning of word
	char *front = strchr(src, src[0]);
	//printf("char is: %c\n", *front);
	if (ispunct(*front)) {
		*src++;
		for (; *src; ++src) {
			*dst++ = (unsigned char) *src;
		}
	}
	// remove puncs from end of word
	char *end = strchr(dst, dst[strlen(dst) - 1]);
	//printf("char is: %c\n", *end);
	if (ispunct(*end)) {
		*end = 0;
	}
}

//------------------------------------------------------------------------------
//-  Function that converts a string to lower case                             -
//------------------------------------------------------------------------------
void string_lower(char *src, char *dst) {
	for (; *src; ++src) {
		*dst++ = tolower((unsigned char) *src);
	}
	*dst = 0;
}

//------------------------------------------------------------------------------
//-  Function to read dictionary file into  memory                             -
//------------------------------------------------------------------------------
bool load_dict_array(FILE *fp) {
	char buf[1024];
	// initilize word count
	dict_size = 0;
	printf("Loading Dictionary...");
	while (fgets(buf, 1024, fp) != NULL) {
		//reallocate memory based on how big the file is using dict_size
		dict = (char **) realloc(dict, (dict_size + 1) * sizeof(char *));
		// load a string into the buffer
		buf[strlen(buf) - 1] = 0;
		//add to dict array
		dict[dict_size++] = strdup(buf);
	}
	printf("done... %d words loaded.\n", dict_size);
	return true;
}

//------------------------------------------------------------------------------
//-  Function to read input file into memory
//------------------------------------------------------------------------------
bool load_input_array(FILE *fp) {
	char buf[1024];
	// initilize word count
	input_size = 0;
	printf("Loading Input File...");
	while (fgets(buf, 1024, fp) != NULL) {
		// load a string into the buffer
		buf[strlen(buf) - 1] = 0;
		// tokenize the string line
		tokenize(buf);
	}
	printf("done... %d words loaded.\n", input_size);
	return true;
}

//------------------------------------------------------------------------------
//-  Function to read input file into memory
//------------------------------------------------------------------------------
void tokenize(char *str) {
	char *token = strtok(str, " ");
	while (token != NULL) {
		input = (char **) realloc(input, (input_size + 1) * sizeof(char *));
		remove_puncs(token, token);
		string_lower(token, token);
		input[input_size++] = strdup(token);
		token = strtok(NULL, " ");
	}
}
