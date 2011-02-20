/*
 * linear.c
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
#include "linear.h"
#include "common.h"

char* dictionary[100000];
int wcnt;

/*
 * finds a word using a linear search algorithm
 */
bool linear_lookup(char **str, int max, char *value) {
	int i;
	for (i = 0; i < max; i++) {
		if (cmpWords(str[i], value) == 0) {
			return true;
		}
	}
	return false;
}

