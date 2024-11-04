#ifndef KVS_H
#define KVS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Skip List의 최대 레벨 정의
#define MAX_LEVEL 16

// Skip List의 노드 구조체
typedef struct SkipListNode {
    char *key;                         // key 값
    char *value;                       // value 값
    struct SkipListNode **forward;    // 레벨별로 다음 노드를 가리키는 포인터 배열
} SkipListNode;

// Skip List 구조체 (kvs)
typedef struct kvs_t {
    SkipListNode *header;             // 헤더 노드
    int level;                         // 현재 Skip List의 최대 레벨
    int items;                         // 저장된 key-value 쌍의 개수
    FILE* query_file;                 // query.dat 파일 포인터
    FILE* answer_file;                // answer.dat 파일 포인터
} kvs_t;

// 함수 프로토타입
kvs_t* open();                                   // kvs 초기화 함수
int close(kvs_t* kvs);                           // kvs 메모리 해제 함수
int put(kvs_t* kvs, const char* key, const char* value);  // key-value 추가 함수
char* get(kvs_t* kvs, const char* key);          // key로 value 검색 함수

#endif // KVS_H
