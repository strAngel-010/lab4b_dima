#ifndef TIMING_H
#define TIMING_H

#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "splay.h"
#include "dialog.h"

#define add_timing_filename "add.txt"
#define find_timing_filename "find.txt"
#define delete_timing_filename "delete.txt"

enum RAND_LIMITS{
    MAX_KEY = 100,
    MIN_KEY = 1
};

int timing(unsigned int min_elems, unsigned int max_elems, unsigned int step, unsigned int trees);
int add_rand_elems(const int elems, Tree* const tree, unsigned int* const keys);

#endif
