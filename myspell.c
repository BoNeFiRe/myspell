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
#include <binary.h>
#include <linear.h>
#include <hashsearch.h>

//----- Constant defines -------------------------------------------------------
#define BUFSIZE 1024
#define MAX_WORD_LENGTH 23

//----- Global variables -------------------------------------------------------
char buffer[BUFSIZE];
char* dictionary[100000];
char* input[100000];
int dict_wcnt; // # of strings in dictionary
int input_wcnt; // # of strings in inputfile
int i; // counter variable

//==============================================================================
//=  Main program                                                              =
//==============================================================================
int main(void) {
	FILE *dict_fptr;
	FILE *input_fptr;
	FILE *output_fptr;
	char in_file[] = "tamingoftheshrew.txt";
	char out_file[] = "myout.txt";
	char in_string[1024];

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

	// read dictionary file into memory
	read_dict(dict_fptr);

	// read input file into memory
	read_input(input_fptr);

	// Output results header
	printf("-------------------------------------------------------- \n");

	// perform search and output to file
	char *key;
	output_fptr = fopen(out_file, "w");
	for (i = 0; i < input_size; i++) {
		key = input[i];
		//if(bin_search(dict, dict_size, input[i]) == 0)
		if (linear_search(dict, dict_size, key) == 0) {
			// open output file

			printf("%s not found\n", input[i]);
			fprintf(output_fptr, "%s\n", input[i]);
		}
	}

	// Output closing trailer
	printf("-------------------------------------------------------- \n");

	// cleanup
	fcloseall();
	return 0;
}
