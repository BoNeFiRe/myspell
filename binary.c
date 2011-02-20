#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binary.h"
#include "common.h"

/*
 * File: binarysearch.c - implementation of my binary search using bsearch(3).
 * 
 * Author: Jonathan R. Engelsma
 */

bool binary_lookup(char* word, int wcnt, char* dictionary) {
	char* dword = bsearch(&word, dictionary, wcnt, sizeof(dictionary[0]),
			cmpWords);
	if (dword != NULL) {
		return true;
	} else {
		return false;
	}
}
