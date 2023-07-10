#include "timing.h"

int timing(unsigned int min_elems, unsigned int max_elems, unsigned int step, unsigned int trees){
    unsigned int* keys_arr = NULL;
    int cur_key_ind = 0;
    unsigned int new_key = 0;
    Tree tree = {NULL};
    int res = 0;
    Node* find_res = NULL;
    double avg_time[4] = {0, 0, 0}; //add, find, delete
    double cur_time[4] = {0, 0, 0}; //add, find, delete
    clock_t begin = 0, end = 0;
    FILE* add_file = fopen(add_timing_filename, "w");
    FILE* find_file = fopen(find_timing_filename, "w");
    FILE* delete_file = fopen(delete_timing_filename, "w");

    for (int i = min_elems; i <= max_elems ; i += step) {
        srand(time(0));
        cur_key_ind = rand()%(i-1);
        keys_arr = (unsigned int*) realloc(keys_arr, i*sizeof(unsigned int));
        if (!keys_arr){
            printf("Error (keys_arr in timing)\n");
            return RES_ERR;
        }
        for (int j = 0; j < i; ++j) { keys_arr[j] = 0; }

        res = add_rand_elems(i, &tree, keys_arr);
        if (res == RES_ERR){
            printf("Error (add_rand_elems in timing)\n");
            return RES_ERR;
        }

        for (int j = 0; j < trees; ++j) {
            new_key = MIN_KEY + rand() % (MAX_KEY-MIN_KEY+1);

            begin = clock();
            res = add(&tree, new_key, 1);
            if (res == RES_ERR){
                printf("Error (add in timing)\n");
                return RES_ERR;
            }
            end = clock();
            cur_time[0] += (end-(double)begin)/CLOCKS_PER_SEC;

            while (!(keys_arr[cur_key_ind])){ cur_key_ind = rand()%(i-1); }

            begin = clock();
            find_res = find(&tree, keys_arr[cur_key_ind], NULL);
            if (!find_res){
                printf("Error (find in timing)\n");
                return RES_ERR;
            }
            splay(&tree, find_res);
            tree.root = find_res;
            end = clock();
            cur_time[1] += (end-(double)begin)/CLOCKS_PER_SEC;

            begin = clock();
            res = delete(&tree, find_res, 0);
            if (res == RES_ERR){
                printf("Error (delete in timing)\n");
                return RES_ERR;
            }
            end = clock();
            cur_time[2] += (end-(double)begin)/CLOCKS_PER_SEC;
            keys_arr[cur_key_ind] = 0;
        }
        erase(tree.root);
        tree.root = NULL;

        for (int j = 0; j < 4; ++j) {
            avg_time[j] = cur_time[j]/trees;
        }
        printf("Avg version (%d size):\n Add: %f s; Find: %f s; Delete: %f s\n", i,
               avg_time[0]*1000000, avg_time[1]*1000000, avg_time[2]*1000000);
        fprintf(add_file, "%d %f\n", i, avg_time[0]*1000000);
        fprintf(find_file, "%d %f\n", i, avg_time[1]*1000000);
        fprintf(delete_file, "%d %f\n", i, avg_time[2]*1000000);
        for (int j = 0; j < 4; ++j) {
            avg_time[j] = 0;
            cur_time[j] = 0;
        }
    }
    free(keys_arr);
    fclose(add_file);
    fclose(find_file);
    fclose(delete_file);
    return RES_OK;
}

int add_rand_elems(const int elems, Tree* const tree, unsigned int* const keys){
    unsigned int new_key = 0;
    unsigned int prev_key = 0;
    int res = 0;
    for (int i = 0; i < elems; ++i) {
        while (new_key == prev_key){ new_key = MIN_KEY + rand() % (MAX_KEY - MIN_KEY + 1); }

        res = add(tree, new_key, 1);
        if (res == RES_ERR){
            printf("Error (add_rand_elems)\n");
            return RES_ERR;
        }

        keys[i] = new_key;
        prev_key = new_key;
    }
    return RES_OK;
}
