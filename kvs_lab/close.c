#include "kvs.h"
#include <stdlib.h>

int close(kvs_t* kvs)
{
    if (!kvs) {
        return -1;
    }

    // 파일 닫기
    if (kvs->query_file) fclose(kvs->query_file);
    if (kvs->answer_file) fclose(kvs->answer_file);

    // Skip List 메모리 해제
    SkipListNode* current = kvs->header;
    while (current) {
        SkipListNode* next_node = current->forward[0]; // 첫 번째 레벨의 다음 노드를 찾음
        free(current->key);
        free(current->value);
        free(current->forward);
        free(current);
        current = next_node;
    }

    free(kvs); // kvs 구조체 해제
    return 0;  // 성공적으로 종료
}
