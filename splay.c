#include "splay.h"

int add(Tree* const tree, unsigned int key, unsigned int info){
    Node* prev = NULL;
    Node* find_res = find(tree, key, &prev);
    if (find_res){
        int push_res = list_push_back(find_res, info);
        if (push_res == RES_ERR){
            return RES_ERR;
        }
        splay(tree, find_res);
        tree->root = find_res;
        return RES_OK;
    }

    Node* node = create_new_node(prev, key, info);
    if (!node){
        return RES_ERR;
    }

    if (!(tree->root)){
        tree->root = node;
        return RES_OK;
    }

    splay(tree, node);
    tree->root = node;
    return RES_OK;
}

Node* find(Tree* const tree, unsigned int key, Node** prev){
    Node* cur = tree->root;
    while (cur){
        if (prev){
            *prev = cur;
        }
        if (key > cur->key){
            cur = cur->right;
        } else if (key < cur->key){
            cur = cur->left;
        } else {
            return cur;
        }
    }
    return NULL;
}

int list_push_back(Node* const node, unsigned int info){
    Item* cur = node->head;
    while (cur->next){
        cur = cur->next;
    }
    Item* item = (Item*) malloc(sizeof(Item));
    if (!item){
        return RES_ERR;
    }

    item->next = NULL;
    item->info = info;
    cur->next = item;
    ++(node->items);
    return RES_OK;
}

Node* create_new_node(Node* const par, unsigned int key, unsigned int info){
    Item* item =  (Item*) malloc(sizeof(Item));
    if (!item){
        return NULL;
    }

    Node* node = (Node*) malloc(sizeof(Node));
    if (!node){
        return NULL;
    }

    node->key = key;
    node->items = 1;
    node->head = item;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    if (par){
        if (par->key < key){ par->right = node; }
        else { par->left = node; }
        node->parent = par;
    }
    item->info = info;
    item->next = NULL;
    return node;
}

/*
void rotate_left(Node* node){
    Node* parent = node->parent;
    Node* right = node->right;
    if (parent){
        if (parent->left == node){
            parent->left = right;
        } else {
            parent->right = right;
        }
    }
    Node* tmp = NULL;
    if (right){
        tmp = right->left;
        right->left = node;
    }
    node->right = tmp;
    node->parent = right;
    if (right) { right->parent = parent; }
    if (node->right){
        node->right->parent = node;
    }
}
 */

void rotate_left(Tree* const tree, Node* node){
    Node* y = node->right;
    Node* p = node->parent;

    if (y) {
        node->right = y->left;
        if (y->left) { y->left->parent = node; }
        y->parent = p;
    }

    if (!p){ tree->root = y; }
    else {
        if (p->left == node){ p->left = y; }
        else { p->right = y; }
    }

    if (y) { y->left = node; }
    node->parent = y;
}

void rotate_right(Tree* const tree, Node* node){
    Node* y = node->left;
    Node* p = node->parent;

    if (y) {
        node->left = y->right;
        if (y->right) { y->right->parent = node; }
        y->parent = p;
    }

    if (!p){ tree->root = y; }
    else {
        if (p->right == node){ p->right = y; }
        else { p->left = y; }
    }

    if (y) { y->right = node; }
    node->parent = y;
}

/*
void rotate_right(Tree* const tree, Node* node){
    Node* parent = node->parent;
    Node* left = node->left;
    if (parent){
        if (parent->right == node){
            parent->right = left;
        } else {
            parent->left = left;
        }
    }
    Node* tmp = NULL;
    if (left){
        tmp = left->right;
        left->right = node;
    }
    node->left = tmp;
    node->parent = left;
    if (left) { left->parent = parent; }
    if (node->left){
        node->left->parent = node;
    }
}
 */

void splay(Tree* const tree, Node* node){
    Node* p = node->parent;
    Node* g = NULL;
    while (p){
        g = p->parent;
        if (node == p->left){
            if (!g){
                rotate_right(tree, p);
            } else if (p == g->left){
                rotate_right(tree, g);
                p = node->parent;
                rotate_right(tree, p);
            } else {
                rotate_right(tree, p);
                p = node->parent;
                rotate_left(tree, p);
            }
        } else {
            if (!g){
                rotate_left(tree, p);
            } else if (p == g->right){
                rotate_left(tree, g);
                p = node->parent;
                rotate_left(tree, p);
            } else {
                rotate_left(tree, p);
                p = node->parent;
                rotate_right(tree, p);
            }
        }
        p = node->parent;
    }
}

int delete(Tree* const tree, Node* node, int ind){
    splay(tree, node);
    tree->root = node;
    if (node->items > 1){
        list_delete(node, ind);
        return RES_OK;
    }

    tree->root = merge(tree, node->left, node->right);
    free(node->head);
    free(node);
    return RES_OK;
}

Node* merge(Tree* const tree, Node* const left, Node* const right){
    if (left){ left->parent = NULL; }
    if (right){ right->parent = NULL; }
    if (!right){ return left; }
    if (!left){ return right; }
    Node* res = find_max_node(left);
    splay(tree, res);
    res->right = right;
    right->parent = res;
    return res;
}

Node* find_max_node(const Node* node){
    while (node->right){
        node = node->right;
    }
    return (Node*)node;
}

Node* find_min_node(const Node* node){
    while (node->left){
        node = node->left;
    }
    return (Node*)node;
}

void list_delete(Node* const node, int ind){
    Item* prev = NULL;
    Item* cur = node->head;
    for (int i = 0; i < ind; ++i) {
        prev = cur;
        cur = cur->next;
    }
    if (!prev){
        node->head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
    --(node->items);
}

void print_show(const Node* node){
    int* tabs = NULL;
    int arrlen = 0;

    while (node){
        if (arrlen){
            for (int i = 0; i < arrlen; ++i) {
                switch (tabs[i]) {
                    case 0:
                        printf("    ");
                        break;
                    case 1:
                        printf("│   ");
                        break;
                    case 2:
                        printf("└───");
                        break;
                    case 3:
                        printf("├───");
                        break;
                    default:
                        printf("Error in print_show()\n");
                        return;
                }
            }
        }
        printf("%u: ", node->key);
        print_info(node);

        if (!(node->left) && !(node->right)){
            node = find_traverse_successor(node);
            int i = arrlen-1;
            while (arrlen != 0 && i >= 0 && tabs[i] != 1 && tabs[i] != 3){
                --i;
            }

            if (arrlen && i >= 0){
                arrlen = i+1;
                tabs = (int*) realloc(tabs, arrlen*sizeof(int));
                if (!tabs){
                    printf("Error (print_show)\n");
                    return;
                }
                tabs[arrlen-1] = 2;
            } else if (tabs) {
                free(tabs);
                tabs = NULL;
            }
            continue;
        }

        ++arrlen;
        tabs = (int*) realloc(tabs, arrlen*sizeof(int));
        if (!tabs){
            printf("Error (print_show)\n");
            return;
        }

        if (node->right && node->left){
            tabs[arrlen-1] = 3;
        } else {
            tabs[arrlen-1] = 2;
        }

        if (arrlen >= 2){
            if (tabs[arrlen-2] == 3){
                tabs[arrlen-2] = 1;
            } else if (tabs[arrlen-2] == 2){
                tabs[arrlen-2] = 0;
            }
        }

        if (node->left){
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

void print_info(const Node* const node){
    Item* cur = node->head;
    while (cur){
        printf("%u ", cur->info);
        cur = cur->next;
    }
    printf("\n");
}

Node* find_traverse_successor(const Node* node){
    if (node->left){
        return node->left;
    }
    if (node->right){
        return node->right;
    }
    Node* par = node->parent;
    while (par){
        if (par->left == node && par->right){
            return par->right;
        }
        node = par;
        par = par->parent;
    }
}

void traverse(const Node *node, unsigned int decimal_places){
    if (!node){
        return;
    }
    if (count_decimal_places(node->key) == decimal_places){
        printf("key: %u; info: ", node->key);
        print_info(node);
    }
    traverse(node->left, decimal_places);
    traverse(node->right, decimal_places);
}

unsigned int count_decimal_places(unsigned int x){
    unsigned int res = 0;
    while (x){
        ++res;
        x /= 10;
    }
    return res;
}

void special_task(Tree* const tree, unsigned int key){
    Node* prev;
    Node* res = find(tree, key, &prev);

    if (res){
        res = find_next(res);
    } else if (prev && prev->key <= key) {
        prev = find_next(prev);
    }

    if (res){
        printf("key: %u; info: ", res->key);
        print_info(res);
        return;
    }
    if (prev && (prev->key != key)){
        printf("key: %u; info: ", prev->key);
        print_info(prev);
    }
}

Node* find_next(const Node* node){
    if (!node){
        printf("Error (findNext)\n");
        return NULL;
    }

    if (node->right){
        return (Node*) find_min_node(node->right);
    }

    Node* ptr = node->parent;
    while (ptr && (ptr->right == node)){
        node = ptr;
        ptr = node->parent;
    }
    return ptr;
}

int input_from_file(Tree* const tree, char* const filename){
    FILE* f = fopen(filename, "r");
    if (!f){
        printf("This file doesn't exist\n");
        return RES_OK;
    }

    while (!feof(f)){
        fgets(filename, BUFSIZE-1, f);
        unsigned int key = atoi(filename);
        if (!key){
            printf("Wrong input format. Skipping line \"%s\"\n", filename);
        }

        fgets(filename, BUFSIZE-1, f);
        unsigned int info = atoi(filename);
        if (!info){
            printf("Wrong input format. Skipping line \"%s\"\n", filename);
        }

        int res = add(tree, key, info);
        if (res == RES_ERR){
            printf("Error (D_Input_From_File)\n");
            return RES_ERR;
        }
    }
    fclose(f);
    return RES_OK;
}

void erase(Node* const node){
    if (!node){
        return;
    }
    erase(node->left);
    erase(node->right);
    Item* prev = node->head;
    Item* cur = prev->next;
    while (cur){
        free(prev);
        prev = cur;
        cur = cur->next;
    }
    free(prev);
    free(node);
}
