#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

struct node {
    int val;
    _Atomic(struct node *) next;
};

struct linked_list {
    _Atomic(struct node *) head;
};

struct args {
    struct linked_list *ll;
    int value;
    int result;
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
    if (ll == NULL) {
        return 0;
    }
    struct node *old_head = atomic_load(&ll->head);
    if (old_head == NULL) {
        free(ll);
        ll = NULL;
        return 1;
    }
    return 0;
}

static inline void
ll_add(struct linked_list *ll, int value)
{
    struct node * new_node = (struct node*) malloc(sizeof(struct node));

    new_node->val = value;

    struct node *old_head;
    do {
        old_head = atomic_load(&ll->head);
        new_node->next = old_head;
    } while (!atomic_compare_exchange_strong(&ll->head, &old_head, new_node));
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
ll_remove(struct linked_list *ll, int index)
{
    struct node *prev = NULL;
    struct node *curr = atomic_load(&ll->head);

    if (curr == NULL) {
        return 0;
    }  

    int pos = 0;

    while (curr && pos < index) {
        prev = curr;
        curr = curr->next;
        pos++;
    }

    if (curr == NULL) {
        return false;
    }

    if (prev == NULL) {
        // this is for removing the first node
        struct node *old_head;
        do {
            old_head = atomic_load(&ll->head);
            if (old_head == NULL) {
                return false;
            }
        } while (!atomic_compare_exchange_strong(&ll->head,&old_head,old_head->next));

    } else {
        // removing any other node
        struct node *old_next;
        do {
            old_next = atomic_load(&curr->next);
            if (old_next == NULL) {
                return false;
            }
        } while (!atomic_compare_exchange_strong(&prev->next, &curr, old_next));
    }
    
	return true;
}

static inline int
ll_contains(struct linked_list *ll, int value)
{
    struct node *curr = atomic_load(&ll->head);

    if (curr == NULL) {
        return 0;
    }

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
    printf("\n");
}

#endif
