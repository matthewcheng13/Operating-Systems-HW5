#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int val;
    struct node *next;
};

struct linked_list {
    struct node *head;
};

static inline struct linked_list *
ll_create(void)
{
    struct linked_list *ll;

    ll = (struct linked_list *) malloc(sizeof(struct linked_list));
	return ll;
}

static inline int
ll_destroy(struct linked_list *ll)
{
    if (ll->head == NULL) {
        free(ll);
        return 1;
    }
    return 0;
}

static inline void
ll_add(struct linked_list *ll, int value)
{
    struct node *new_node = (struct node*) malloc(sizeof(struct node));

    new_node->val = value;
    new_node->next = ll->head;
    ll->head = new_node;
}

static inline int
ll_length(struct linked_list *ll)
{
    if (!ll->head) {
        return 0;
    }

    struct node *curr = ll->head;
    int len = 1;

    while (curr->next) {
        len++;
        curr = curr->next;
    }

	return len;
}

static inline bool
ll_remove_first(struct linked_list *ll)
{
    if (ll->head == NULL) {
        return false;
    }
    ll->head = ll->head->next;

	return true;
}

static inline int
ll_contains(struct linked_list *ll, int value)
{
    if (!ll->head) {
        return 0;
    }

    struct node *curr = ll->head;
    int pos = 1;

    while (curr->val != value && curr->next) {
        pos++;
        curr = curr->next;
    }

    if (curr->val == value) {
        return pos;
    }

    return 0;
}

static inline void
ll_print(struct linked_list *ll)
{
    struct node *curr = ll->head;

    while (curr) {
        printf("%d ",curr->val);
        curr = curr->next;
    }
}

#endif
