/*
 * common.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Matthew LEvandowski
 *	 	Email: levandma@mail.gvsu.edu
 *      GVSU Computer Science
 */

#ifndef COMMON_H_
#define COMMON_H_

int cmpWords(const void *w1, const void *w2);
bool load_dict_array();
bool load_input_array(FILE *ptr);
void remove_puncs(char *src, char *dst);
void string_upper(char *src, char *dst);

#endif /* COMMON_H_ */
