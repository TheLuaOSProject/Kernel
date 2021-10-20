//
// Created by Frityet on 2021-10-15.
//

#ifndef LUAOS_FREE_LIST
#define LUAOS_FREE_LIST

typedef struct freelist {
    struct freelist *next, *previous;
} freelist_t;

void list_new(freelist_t *list);
void list_push(freelist_t *list, freelist_t *item);
void list_remove(freelist_t *item);


#endif //LUAOS_FREE_LIST
