#include "kvs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

kvs_t* open() {
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));
    if (!kvs) {
        fprintf(stderr, "Error: Failed to allocate memory for KVS.\n");
        return NULL;
    }

    // Skip List 초기화
    kvs->header = (SkipListNode*)malloc(sizeof(SkipListNode));
    if (!kvs->header) {
        fprintf(stderr, "Error: Failed to allocate memory for Skip List header.\n");
        free(kvs);
        return NULL;
    }
    
    // key와 value 초기화
    kvs->header->key = NULL;
    kvs->header->value = NULL;

    kvs->header->forward = (SkipListNode**)calloc(MAX_LEVEL + 1, sizeof(SkipListNode*));
    if (!kvs->header->forward) {
        fprintf(stderr, "Error: Failed to allocate memory for Skip List forward pointers.\n");
        free(kvs->header);
        free(kvs);
        return NULL;
    }

    kvs->level = 0;
    kvs->items = 0;
    kvs->query_file = fopen("query.dat", "r");
    kvs->answer_file = fopen("answer.dat", "w");

    if (!kvs->query_file || !kvs->answer_file) {
        fprintf(stderr, "Error: Could not open data files.\n");
        if (kvs->query_file) fclose(kvs->query_file);
        if (kvs->answer_file) fclose(kvs->answer_file);
        free(kvs->header->forward);
        free(kvs->header);
        free(kvs);
        return NULL;
    }

    srand((unsigned)time(NULL)); // 랜덤 시드 설정
    return kvs;
}
