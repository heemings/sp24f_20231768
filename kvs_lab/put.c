#include "kvs.h"

int put(kvs_t* kvs, const char* key, const char* value) {
    SkipListNode* current = kvs->header;
    SkipListNode* update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(update));

    for (int i = kvs->level; i >= 0; i--) {
        while (current->forward[i] && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    if (current && strcmp(current->key, key) == 0) {
        free(current->value);
        current->value = strdup(value);
        return 0;
    }

    int level = 0;
    while (level < MAX_LEVEL && rand() % 2 == 0) {
        level++;
    }

    if (level > kvs->level) {
        for (int i = kvs->level + 1; i <= level; i++) {
            update[i] = kvs->header;
        }
        kvs->level = level;
    }

    SkipListNode* new_node = (SkipListNode*)malloc(sizeof(SkipListNode));
    if (!new_node) return -1;
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->forward = (SkipListNode**)calloc(level + 1, sizeof(SkipListNode*));

    for (int i = 0; i <= level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }

    kvs->items++;
    return 0;
}