/*
 * hashsearch.h
 *
 *  Created on: Feb 20, 2011
 *      Author: Matthew LEvandowski
 *	 	Email: levandma@mail.gvsu.edu
 *      GVSU Computer Science
 */
#ifndef HASHSEARCH_H_
#define HASHSEARCH_H_

typedef struct _list_t_ {
	char *str;
	struct _list_t_ *next;
} list_t;

typedef struct _hash_table_t_ {
	int size; /* the size of the table */
	list_t **table; /* the table elements */
} hash_table_t;

unsigned int hash(char *str);

hash_table_t *create_hash_table(int size);

list_t *hash_lookup(hash_table_t *hashtable, char *str);

int add_string(hash_table_t *hashtable, char *str);

void free_table(hash_table_t *hashtable);

#endif /* HASHSEARCH_H_ */
