#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define INCRE 10

char alpha_to_num[] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', 0, '7', '7', '8', '8', '8', '9', '9', '9'};

typedef struct {
    char *number;
    unsigned long count;
} Number;

typedef struct {
    Number *list;
    unsigned long length;
    unsigned long capacity;
} List;

char* convert(char *input) {
    int i = 0;
    char *this = calloc(9, sizeof(char));
    while (*input != '\0') {
        if (i == 3) {
            this[i++] = '-';
            continue;
        }
        if (*input >= 'A') {
            this[i++] = alpha_to_num[*input - 'A'];
        } else if (*input >= '0') {
            this[i++] = *input;
        }
        input++;
    }
    this[i] = '\0';
    return this;
}

Number *new_number(char *num) {
    Number *new = calloc(1, sizeof(Number));
    new->number = num;
    new->count = 1;
    return new;
}

int add_to_table(List table[], char *this) {
    unsigned long i, j;
    int compare_result;
    List *list = &table[(this[0] - '0') * 10 + this[1] - '0'];
    if (!list->list) {
        list->list = calloc(INCRE, sizeof(Number));
        list->length = 0;
        list->capacity = INCRE;
    }
    for (i = 0; i < list->length; i++) {
        compare_result = strncmp(this, list->list[i].number, 9);
        if (compare_result < 0) {
            if (list->length == list->capacity) {
                list->capacity *= 2;
                list->list = realloc(list->list, list->capacity * sizeof(Number));
            }
            for (j = list->length; j > i; j--) {
                list->list[j] = list->list[j-1];
            }
            list->list[i].number = this;
            list->list[i].count = 1;
            list->length++;
            return TRUE;
        } else if (compare_result == 0) {
            list->list[i].count++;
            return FALSE;
        }
    }
    if (list->length == list->capacity) {
        list->capacity *= 2;
        list->list = realloc(list->list, list->capacity * sizeof(Number));
    }
    list->list[list->length].number = this;
    list->list[list->length].count = 1;
    list->length++;
    return TRUE;
}

int main() {
    unsigned long i, j;
    unsigned long count;
    char input[100];
    char *this;
    int flag = 0;
    List table[100] = {{0, 0, 0}};
    scanf("%lu", &count);
    for (i = 0; i < count; i++) {
        scanf("%s", input);
        this = convert(input);
        if (!add_to_table(table, this)) {
            free(this);
        }
    }
    for (i = 0; i < 100; i++) {
        if (table[i].length) {
            for (j = 0; j < table[i].length; j++) {
                if (table[i].list[j].count > 1) {
                    printf("%s %lu\n", table[i].list[j].number, table[i].list[j].count);
                    flag = 1;
                }
            }
        }
    }
    if (!flag) {
        printf("No duplicates.");
    }
}
