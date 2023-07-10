#ifndef SPLAY_H
#define SPLAY_H

#include "tree.h"
#include "dop_funcs.h"
#include <stdlib.h>
#include <stdio.h>

int add(Tree* const tree, unsigned int key, unsigned int info);
Node* find(Tree* const tree, unsigned int key, Node** prev);
int list_push_back(Node* const node, unsigned int info);
Node* create_new_node(Node* const par, unsigned int key, unsigned int info);
void rotate_left(Tree* const tree, Node* node);
void rotate_right(Tree* const tree, Node* node);
void splay(Tree* const tree, Node* node);
void print_show(const Node* node);
void print_info(const Node* const node);
Node* find_traverse_successor(const Node* node);
int delete(Tree* const tree, Node* node, int ind);
void list_delete(Node* const node, int ind);
Node* merge(Tree* const tree, Node* const left, Node* const right);
Node* find_max_node(const Node* node);
Node* find_min_node(const Node* node);
void traverse(const Node *node, unsigned int decimal_places);
unsigned int count_decimal_places(unsigned int x);
void special_task(Tree* const tree, unsigned int key);
Node* find_next(const Node* node);
int input_from_file(Tree* const tree, char* const filename);
void erase(Node* const node);

#endif
