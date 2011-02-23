/*
 * binarysearch.c
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
#include "binarysearch.h"

int binary_lookup(char *word, int dict_size, char **dict) {
	int position;
	int begin = 0;
	int end = dict_size - 1;
	int cond = 0;
	while (begin <= end) {
		position = (begin + end) / 2;
		if ((cond = strcmp(dict[position], word)) == 0)
			return position;
		else if (cond < 0)
			begin = position + 1;
		else
			end = position - 1;
	}
	return 0;
}
