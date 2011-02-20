/*
 * common.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Matthew LEvandowski
 *	 	Email: levandma@mail.gvsu.edu
 *      GVSU Computer Science
 */

/*
 * comparison function required by bsearch
 */
int cmpWords(const void *w1, const void *w2) {
	return strcmp(*(char**) w1, *(char**) w2);
}

bool load_dict_array() {
	FILE *fp = fopen("american-english", "r");
	char buf[1024];
	if (!fp) {
		printf("whoops, could not open dictionary.  sorry.\n");
		return false;
	}

	wcnt = 0;
	printf("Loading...");

	while (fgets(buf, 1024, fp) != NULL) {
		buf[strlen(buf) - 1] = 0;
		dictionary[wcnt++] = strdup(buf);
	}
	printf("done... %d words loaded.\n", wcnt);
	return true;
}

//------------------------------------------------------------------------------
//-  Function to read input file into memory
//------------------------------------------------------------------------------
bool load_input_array(FILE *ptr) {
	char in_string[128]; // temp char holder;
	// read from file
	while (!feof(ptr)) {
		if (fscanf(ptr, "%s", in_string) < 1) {
			break;
		}
		input = (char **) realloc(input, (input_size + 1) * sizeof(char *));
		//puts(in_string);

		// make two pointers to remove punctuations
		char *tmp = &in_string;
		char *tmp2 = &in_string;

		// remove punctuation and put in lower case
		remove_puncs(tmp, tmp2);

		//store string into array
		input[input_size++] = strdup(in_string);
		//  printf("%s\n", input[input_size-1]);

	}
}

//------------------------------------------------------------------------------
//-  Function that converts a string to lower case and removes punctuations    -
//------------------------------------------------------------------------------
void remove_puncs(char *src, char *dst) {
	for (; *src; ++src)
		if (!ispunct((unsigned char) *src))
			*dst++ = tolower((unsigned char) *src);
	*dst = 0;
}

//------------------------------------------------------------------------------
//-  Function that converts a string to upper case                             -
//------------------------------------------------------------------------------
void string_upper(char *src, char *dst) {
	for (; *src; ++src) {
		*dst++ = toupper((unsigned char) *src);
	}
	*dst = 0;
}

