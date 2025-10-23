#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list_init(list_t *list) {
    list->head = NULL;
    list->size = 0;
}

void list_add(list_t *list, const char *data) {
    node_t *point = list->head;
    while (point != NULL && point->next != NULL) {
        point = point->next;
    }
    node_t *new_node = malloc(sizeof(node_t));
    strncpy(new_node->data, data, MAX_LEN);
    new_node->next = NULL;
    if (point == NULL) {
        list->head = new_node;
    } else {
        point->next = new_node;
    }
    list->size++;
}

int list_size(const list_t *list) {
    return list->size;
}

char *list_get(const list_t *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    node_t *point = list->head;
    int i = 0;
    while (point != NULL && i < index) {
        point = point->next;
        i++;
    }
    if (point == NULL) {
        return NULL;
    }
    return point->data;
}

void list_clear(list_t *list) {
    node_t *point = list->head;
    while (point != NULL) {
        node_t *next = point->next;
        free(point);
        point = next;
    }
    list->head = NULL;
    list->size = 0;
}


int list_contains(const list_t *list, const char *query) {
    node_t *point = list->head;
    while (point != NULL) {
        if (strcmp(point->data, query) == 0) {
            return 1;
        }
        point = point->next;
    }
    return 0;
}

void list_print(const list_t *list) {
    int i = 0;
    node_t *current = list->head;
    while (current != NULL) {
        printf("%d: %s\n", i, current->data);
        current = current->next;
        i++;
    }
}
