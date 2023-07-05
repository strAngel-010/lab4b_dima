#include <stdio.h>
#include "dialog.h"
#include "splay.h"

int init();
int dialog(const char* msgs[], int N);

int main() {
    if (init()){
        printf("Program finished with errors\n");
    } else {
        printf("Program finished successfully\n");
    }
    return 0;
}

int init(){
    const char* msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Traverse", "5. Show", "6. Special", "7. Input from file", "8. Timing"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int (*fptr[])(Tree* const) = {NULL, D_Add, D_Find, D_Delete, D_Traverse, D_Show,
                                  D_Special, D_InputFromFile, D_Timing};
    Tree tree = {NULL, 0, 0, 0};
    int res = 0;
    int rc = 0;

    while (rc = dialog(msgs, NMsgs)){
        if (rc >= NMsgs || rc < 0){
            printf("Wrong input format\n");
            continue;
        }
        res = fptr[rc](&tree);
        if (res == RES_ERR || res == EOF){
            break;
        }
    }

    erase(tree.root);
    return res == RES_ERR ? RES_ERR : RES_OK;
}

int dialog(const char* msgs[], const int N){
    int rc, res;
    for (int i = 0; i < N; ++i) {
        puts(msgs[i]);
    }
    printf("Make your choice:\n");
    res = getUInt(&rc);
    if (res == RES_EOF){
        rc = 0;
    }
    return rc;
}
