#ifndef DIALOG_H
#define DIALOG_H

#include <stdio.h>
#include "../aux_funcs/aux_funcs.h"
#include "tree.h"
#include "splay.h"

int D_Add(Tree* const tree);
int D_Find(Tree* const tree);
int D_Delete(Tree* const tree);
int D_Traverse(Tree* const tree);
int D_Show(Tree* const tree);
int D_Special(Tree* const tree);
int D_InputFromFile(Tree* const tree);
int D_Timing(Tree* const tree);

#endif
