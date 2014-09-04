/*
utility functions
*/

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

void *safe_malloc(size_t size)
{
	void *mem = NULL;
	if ((mem = calloc(1, size)) == NULL) {
		fprintf(stderr, "Error: safe_malloc() cannot allocate "
			"memory of size %lu.\n", size);
		exit(EXIT_FAILURE);
	}
	return mem;
}

void *safe_realloc(void *old_mem, size_t new_size)
{
	if ((old_mem = realloc(old_mem, new_size)) == NULL) {
		fprintf(stderr, "Error: safe_realloc() cannot allocate "
			"new memory of size %lu.\n", new_size);
		exit(EXIT_FAILURE);
	}
	return old_mem;
}

