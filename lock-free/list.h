#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>

struct node {
    int val;
    struct node *next;
};

struct linked_list {
    _Atomic(struct node *) head;
};

static inline struct linked_list *
ll_create(void)
{
    struct linked_list *ll;

    ll = (struct linked_list *) malloc(sizeof(struct linked_list));
	atomic_store(&ll->head, NULL);
    return ll;
}

static inline int
ll_destroy(struct linked_list *ll)
{
    struct node *old_head = atomic_load(&ll->head);
    if (old_head == NULL) {
        free(ll);
        return 1;
    }
    free(old_head);
    return 0;
}

static inline void
ll_add(struct linked_list *ll, int value)
{
    struct node *new_node = (struct node*) malloc(sizeof(struct node));

    new_node->val = value;
    new_node->next = ll->head;

    struct node *old_head;
    do {
        old_head = atomic_load(&ll->head);
        new_node->next = old_head;
    } while (!atomic_compare_exchange_weak(&ll->head, &old_head, new_node));
    free(old_head);
}

static inline int
ll_length(struct linked_list *ll)
{
    /*if (!ll->head) {
        return 0;
    }*/
    int len = 0;

    struct node *curr = atomic_load(&ll->head);
    while (curr) {
        len++;
        curr = curr->next;
    }

	return len;
}

static inline bool
ll_remove_first(struct linked_list *ll)
{
    /*if (ll->head == NULL) {
        return false;
    }*/
    struct node *old_head;
    do {
        old_head = atomic_load(&ll->head);
        if (old_head == NULL) {
            return false;
        }
    } while (!atomic_compare_exchange_weak(&ll->head,old_head,old_nead->next));

    free(old_head);
	return true;
}

static inline int
ll_contains(struct linked_list *ll, int value)
{
    /*if (!ll->head) {
        return 0;
    }*/

    struct node *curr = atomic_load(&ll->head);
    int pos = 1;

    while (curr) {
        if (curr->val == value) {
            return pos;
        }
        pos++;
        curr = curr->next;
    }

    return 0;
}

static inline void
ll_print(struct linked_list *ll)
{
    struct node *curr = atomic_load(&ll->head);

    while (curr) {
        printf("%d ",curr->val);
        curr = curr->next;
    }
}

#endif
