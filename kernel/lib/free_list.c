//
// Created by Frityet on 2021-10-15.
//

#include "free_list.h"

void list_new(freelist_t *list)
{
    list->previous = list;
    list->next = list;
}

void list_push(freelist_t *list, freelist_t *item)
{
    item->previous = list->previous;
    item->next = list;
    item->previous = item;
    list->previous->next = item;
}

void list_remove(freelist_t *item)
{
    item->previous->next = item->next;
    item->next->previous = item->previous;
}


