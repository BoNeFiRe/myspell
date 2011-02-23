/*
 * linearsearch.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Matthew LEvandowski
 *	 	Email: levandma@mail.gvsu.edu
 *      GVSU Computer Science
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linearsearch.h"

/*
 * finds a word using a linear search algorithm
 */
bool linear_lookup(char *word, int wcnt, char **dictionary) {
	int i;
	for (i = 0; i < wcnt; i++) {
		if (strcmp(dictionary[i], word) == 0) {
			return true;
		}
	}
	return false;
}

