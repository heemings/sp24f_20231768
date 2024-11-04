#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvs.h"

int main() {
    kvs_t* kvs = open();
    if (!kvs) {
        fprintf(stderr, "Failed to open KVS.\n");
        return 1;
    }

    FILE *query_file = fopen("query.dat", "r");
    FILE *answer_file = fopen("answer.dat", "w");
    if (!query_file || !answer_file) {
        fprintf(stderr, "Failed to open query.dat or answer.dat.\n");
        close(kvs);
        if (query_file) fclose(query_file);
        if (answer_file) fclose(answer_file);
        return 1;
    }

    char operation[10], key[100], value[100];
    while (fscanf(query_file, "%[^,],%[^,],%s\n", operation, key, value) != EOF) {
        // Debug output (optionally comment this out)
        printf("Operation: %s, Key: %s, Value: %s\n", operation, key, value);

        if (strcmp(operation, "put") == 0 || strcmp(operation, "set") == 0) {
            if (put(kvs, key, value) < 0) {
                fprintf(stderr, "Failed to put key: %s\n", key);
            }
        } else if (strcmp(operation, "get") == 0) {
            char *result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "%s\n", result); // 값 기록
                free(result); // 동적 메모리 해제
            } else {
                fprintf(answer_file, "-1\n"); // 키가 없을 경우 -1 기록
            }
        }
    }

    fclose(query_file);
    fclose(answer_file);
    close(kvs);
    return 0;
}
