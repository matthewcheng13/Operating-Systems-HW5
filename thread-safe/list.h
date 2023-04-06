#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

struct node {
    int val;
    struct node *next;
};

struct linked_list {
    struct node *head;
    pthread_mutex_t lock;
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
    pthread_mutex_init(&ll->lock, NULL);
    ll->head = NULL;
	return ll;
}

static inline int
ll_destroy(struct linked_list *ll)
{
    pthread_mutex_lock(&ll->lock);
    if (ll->head == NULL) {
        pthread_mutex_unlock(&ll->lock);
        pthread_mutex_destroy(&ll->lock);
        free(ll);
        return 1;
    }
    pthread_mutex_unlock(&ll->lock);
    return 0;
}

static inline void
ll_add(struct linked_list *ll, int value)
{
    pthread_mutex_lock(&ll->lock);
    struct node *new_node = (struct node*) malloc(sizeof(struct node));

    new_node->val = value;
    new_node->next = ll->head;
    ll->head = new_node;
    pthread_mutex_unlock(&ll->lock);
}

static inline int
ll_length(struct linked_list *ll)
{
    pthread_mutex_lock(&ll->lock);
    if (!ll->head) {
        pthread_mutex_unlock(&ll->lock);
        return 0;
    }

    struct node *curr = ll->head;
    int len = 1;

    while (curr->next) {
        len++;
        curr = curr->next;
    }

    pthread_mutex_unlock(&ll->lock);

	return len;
}

static inline int
ll_remove(struct linked_list *ll, int index) // Remove the node at specified index
{
    pthread_mutex_lock(&ll->lock);

    if (ll->head == NULL) {
        pthread_mutex_unlock(&ll->lock);
        return 0;
    }

    if (index == 0) {
        ll->head = ll->head->next;
        pthread_mutex_unlock(&ll->lock);
        return 1;
    }

    struct node *prev = ll->head;
    struct node *curr = prev->next;

    int i = 1;

    while (curr && i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (curr && i == index) {
        prev->next = curr->next;
        free(curr);
        pthread_mutex_unlock(&ll->lock);
        return 1;
    }    

    pthread_mutex_unlock(&ll->lock);
	return 0;
}

static inline int
ll_contains(struct linked_list *ll, int value)
{
    pthread_mutex_lock(&ll->lock);
    if (!ll->head) {
        pthread_mutex_unlock(&ll->lock);
        return 0;
    }

    struct node *curr = ll->head;
    int pos = 1;

    while (curr->val != value && curr->next) {
        pos++;
        curr = curr->next;
    }

    if (curr->val == value) {
        pthread_mutex_unlock(&ll->lock);
        return pos;
    }

    pthread_mutex_unlock(&ll->lock);

    return 0;
}

static inline void
ll_print(struct linked_list *ll)
{
    printf("\n");
    pthread_mutex_lock(&ll->lock);
    struct node *curr = ll->head;

    while (curr) {
        printf("%d ",curr->val);
        curr = curr->next;
    }
    pthread_mutex_unlock(&ll->lock);
    printf("\n");
}

#endif
