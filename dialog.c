#include "dialog.h"

int D_Add(Tree* const tree){
    unsigned int key = 0;
    unsigned int info = 0;

    printf("Enter key:\n");
    if (getUInt(&key) == RES_EOF){
        return RES_EOF;
    }

    printf("Enter info:\n");
    if (getUInt(&info) == RES_EOF){
        return RES_EOF;
    }

    int res = add(tree, key, info);
    if (res == RES_ERR){
        printf("Error (D_Add)\n");
        return RES_ERR;
    }
    printf("OK\n");
    return RES_OK;
}

int D_Find(Tree* const tree){
    unsigned int key = 0;
    printf("Enter key:\n");
    if (getUInt(&key) == RES_EOF){
        return RES_EOF;
    }

    Node* res = find(tree, key, NULL);
    if (!res){
        printf("No elements found with this key\n");
        return RES_OK;
    }
    printf("key: %u; info: ", res->key);
    print_info(res);
    splay(tree, res);
    tree->root = res;
    printf("OK\n");
    return RES_OK;
}

int D_Delete(Tree* const tree){
    unsigned int key = 0;
    int ind = 0;
    printf("Enter key to delete:\n");
    if (getUInt(&key) == RES_EOF){
        return RES_EOF;
    }

    Node* node = find(tree, key, NULL);
    if (!node){
        printf("Element with this key doesn't exist\n");
    }

    if (node->items == 1){
        int res = delete(tree, node, 0);
        return res;
    }
    printf("Found next info: ");
    print_info(node);
    printf("Which info would you like to delete? (1-%d)\n", node->items);
    if (getIntInInterval(&ind, 1, node->items)){
        return RES_EOF;
    }

    int res = delete(tree, node, ind-1);
    printf("OK\n");
    return res;
}

int D_Traverse(Tree* const tree){
    unsigned int places = 0;
    printf("Enter number of decimal places:\n");
    if (getUInt(&places) == RES_EOF){
        return RES_EOF;
    }

    traverse(tree->root, places);
    printf("OK\n");
    return RES_OK;
}

int D_Show(Tree* const tree){
    print_show(tree->root);
    printf("OK\n");
    return RES_OK;
}

int D_Special(Tree* const tree){
    unsigned int key = 0;
    int ind = 0;
    printf("Enter key:\n");
    if (getUInt(&key) == RES_EOF){
        return RES_EOF;
    }

    special_task(tree, key);
    printf("OK\n");
    return RES_OK;
}

int D_InputFromFile(Tree* const tree){
    getchar();
    char* filename = myreadline(NULL, "Enter file name:\n");

    int res = input_from_file(tree, filename);
    if (res == RES_ERR){
        printf("Error (D_Input_From_File)\n");
    }

    free(filename);
    return res;
}

int D_Timing(Tree* const tree){
    unsigned int min_elems = 0;
    unsigned int max_elems = 0;
    unsigned int step = 0;
    unsigned int trees = 0;

    printf("Enter min_elems:\n");
    if (getUInt(&min_elems) == RES_EOF){ return RES_EOF; }

    printf("Enter max_elems:\n");
    if (getUInt(&max_elems) == RES_EOF){ return RES_EOF; }

    printf("Enter step:\n");
    if (getUInt(&step) == RES_EOF){ return RES_EOF; }

    printf("Enter number of trees:\n");
    if (getUInt(&trees) == RES_EOF){ return RES_EOF; }

    int res = timing(min_elems, max_elems, step, trees);
    if (res == RES_ERR){
        printf("Error (D_Timing)\n");
    }
    return res;
}
