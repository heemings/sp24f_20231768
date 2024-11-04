#include "kvs.h"
char* get(kvs_t* kvs, const char* key)
{
    SkipListNode* current = kvs->header;

    // Skip List의 최대 레벨에서 시작
    for (int i = kvs->level; i >= 0; i--) {
        // 현재 레벨에서 다음 노드로 이동
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
    }

    // 현재 노드의 다음 노드가 찾고자 하는 키와 같은지 확인
    current = current->forward[0]; // 0 레벨의 다음 노드로 이동
    if (current != NULL && strcmp(current->key, key) == 0) {
        return strdup(current->value); // 키가 존재하면 해당 value 반환 (strdup으로 복사)
    }

    return NULL; // 키가 존재하지 않으면 NULL 반환
}
