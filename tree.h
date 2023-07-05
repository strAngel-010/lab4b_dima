#ifndef TREE_H
#define TREE_H

typedef struct Item{
    unsigned int info;
    struct Item* next;
}Item;

typedef struct Node{
    unsigned int key;
    Item* head;
    int items;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct Tree{
    Node* root;
}Tree;

#endif
