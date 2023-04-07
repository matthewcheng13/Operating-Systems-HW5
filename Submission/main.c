#include "list.h"

/****************************************
THREADS

These are functions being used by the
threads. There is one for each of the
linked list methods.
****************************************/

void *destroy_thread(void *argp) {
    struct args *destroy_args = (struct args*)argp;
    if (destroy_args == NULL) {
        return NULL;
    }
    ll_destroy(destroy_args->ll);

    return NULL;
}

void *add_thread(void *argp) {
	struct args *add_args = (struct args*)argp;
	ll_add(add_args->ll, add_args->value);

	return NULL;
}

void *length_thread(void *argp) {
	struct args *length_args = (struct args*)argp;
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = ll_length(length_args->ll);

	return iptr;
}

void *remove_thread(void *argp) {
	struct args *remove_args = (struct args*)argp;
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = ll_remove(remove_args->ll, remove_args->value);
	
	return iptr;
}

void *contains_thread(void *argp) {
	struct args *contains_args = (struct args*)argp;
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = ll_contains(contains_args->ll, contains_args->value);

	return iptr;
}

void *print_thread(void *argp) {
	struct args *print_args = (struct args*)argp;
	ll_print(print_args->ll);

	return NULL;
}

/****************************************
LINKED LIST TESTS

These are threadless tests that ensure
the linked list still behaves as 
intended. This section is condensed
from hw0.
****************************************/

int test_add() {
	struct linked_list *ll;

	ll = ll_create();

	printf("Running Add Test\n");

	ll_add(ll,5);
	ll_print(ll); // should print 5
	if (ll->head->val != 5) {
		printf("Add Test Failed\n");
		return 0;
	}
	ll_add(ll,7);
	ll_add(ll,3);
	ll_add(ll,1);
	ll_print(ll); // should print 1 3 7 5
	int arr1[4] = {1,3,7,5};
	struct node *curr = ll->head;
	int i = 0;
	while (curr && i < 4) {
		if (curr->val != arr1[i]) {
			printf("Add Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	ll_add(ll,2);
	ll_add(ll,0);
	ll_add(ll,14);
	ll_print(ll); // should print 14 0 2 1 3 7 5
	int arr2[7] = {14,0,2,1,3,7,5};
	curr = ll->head;
	i = 0;
	while (curr && i < 7) {
		if (curr->val != arr2[i]) {
			printf("Add Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	printf("Add Test Passed\n");
	return 0;
}

int test_length() {
	struct linked_list *ll;

	ll = ll_create();

	printf("Running Length Test\n");

	ll_add(ll,5);
	if (ll_length(ll) != 1) {
		printf("Length Test Failed\n");
		return 0;
	}
	ll_add(ll,7);
	ll_add(ll,3);
	ll_add(ll,1);
	if (ll_length(ll) != 4) {
		printf("Length Test Failed\n");
		return 0;
	}
	ll_add(ll,2);
	ll_add(ll,0);
	ll_add(ll,14);
	if (ll_length(ll) != 7) {
		printf("Length Test Failed\n");
		return 0;
	}
	printf("Length Test Passed\n");
	return 0;
}

int test_remove() {
	struct linked_list *ll;

	ll = ll_create();

	printf("Running Remove Test\n");

	ll_add(ll,5);
	ll_add(ll,7);
	ll_remove(ll,0);
	ll_print(ll); // should print 5
	if (ll->head->val != 5) {
		printf("Remove Test Failed\n");
		return 0;
	}
	ll_add(ll,3);
	ll_add(ll,1);
	ll_remove(ll,1);
	ll_print(ll); // should print 1 5
	int arr1[2] = {1,5};
	struct node *curr = ll->head;
	int i = 0;
	while (curr && i < 2) {
		if (curr->val != arr1[i]) {
			printf("Remove Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	ll_add(ll,2);
	ll_add(ll,0);
	ll_add(ll,14);
	ll_remove(ll,3);
	ll_remove(ll,3);
	ll_remove(ll,1);
	ll_print(ll); // should print 14 2
	int arr2[2] = {14,2};
	curr = ll->head;
	i = 0;
	while (curr && i < 2) {
		if (curr->val != arr2[i]) {
			printf("Remove Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	printf("Remove Test Passed\n");
	return 0;
}

int test_contains() {
	struct linked_list *ll;

	ll = ll_create();

	printf("Running Contains Test\n");

	if (ll_contains(ll,0) != 0) {
		printf("Contains Test Failed\n");
		return 0;
	}
	if (ll_contains(ll,5) != 0) {
		printf("Contains Test Failed\n");
		return 0;
	}
	ll_add(ll,5);
	if (ll_contains(ll,5) != 1) {
		printf("Contains Test Failed\n");
		return 0;
	}
	ll_add(ll,7);
	ll_add(ll,3);
	ll_add(ll,1);
	ll_remove(ll,3);
	if (ll_contains(ll,5) != 0) {
		printf("Contains Test Failed\n");
		return 0;
	}
	int arr1[3] = {1,3,7};
	struct node *curr = ll->head;
	int i = 0;
	ll_print(ll);
	while (curr && i < 3) {
		if (ll_contains(ll,arr1[i]) != i+1) {
			printf("Contains Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	ll_add(ll,2);
	ll_add(ll,0);
	ll_add(ll,14);
	ll_remove(ll,0);
	ll_remove(ll,3);
	if (ll_contains(ll,14) != 0) {
		printf("Contains Test Failed\n");
		return 0;
	}
	if (ll_contains(ll,3) != 0) {
		printf("Contains Test Failed\n");
		return 0;
	}
	int arr2[4] = {0,2,1,7};
	curr = ll->head;
	i = 0;
	ll_print(ll);
	while (curr && i < 4) {
		if (ll_contains(ll,arr2[i]) != i+1) {
			printf("Contains Test Failed\n");
			return 0;
		}
		curr = curr->next;
		i++;
	}
	printf("Contains Test Passed\n");
	return 0;
}

int test_destroy() {
	struct linked_list *ll;

	ll = ll_create();

	printf("Running Destroy Test\n");

	if (!ll_destroy(ll)) {
		printf("Destroy Test Failed\n");
		return 0;
	}
	ll = ll_create();
	ll_add(ll,5);
	if (ll_destroy(ll)) {
		printf("Destroy Test Failed\n");
		return 0;
	}
	ll_remove(ll,0);
	if (!ll_destroy(ll)) {
		printf("Destroy Test Failed\n");
		return 0;
	}
	ll = ll_create();
	ll_add(ll,7);
	ll_add(ll,3);
	ll_remove(ll,1);
	if (ll_destroy(ll)) {
		printf("Destroy Test Failed\n");
		return 0;
	}
	ll_remove(ll,0);
	if (!ll_destroy(ll)) {
		printf("Destroy Test Failed\n");
		return 0;
	}
	printf("Destroy Test Passed\n");
	return 0;
}

/****************************************
THREAD TESTS
****************************************/

int test_add_remove() {
	struct linked_list *ll;
	pthread_t tid[2];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 5; // value we are adding

	struct args *remove_args2 = (struct args *)malloc(sizeof(struct args));
	remove_args2->ll = ll;
	remove_args2->value = 0; // value we are removing at index

	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, remove_thread, (void *)remove_args2);

	// and then we join all of them to the main thread
	for (int i = 0; i < 2; i++) {
		pthread_join(tid[i], NULL);
	}
	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");


	free(ll);

	return 0;
}

int test_add_add_remove1_remove0() {
	struct linked_list *ll;
	pthread_t tid[4];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *add_args2 = (struct args *)malloc(sizeof(struct args));
	add_args2->ll = ll;
	add_args2->value = 7; // value we are removing at index
	
	struct args *remove_args3 = (struct args *)malloc(sizeof(struct args));
	remove_args3->ll = ll;
	remove_args3->value = 1; // value we are adding

	struct args *remove_args4 = (struct args *)malloc(sizeof(struct args));
	remove_args4->ll = ll;
	remove_args4->value = 0; // value we are adding



	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, add_thread, (void *)add_args2);
	pthread_create(&tid[2], NULL, remove_thread, (void *)remove_args3);
	pthread_create(&tid[3], NULL, remove_thread, (void *)remove_args4);

	// and then we join all of them to the main thread
	for (int i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
	}
	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");


	free(ll);

	return 0;
}


int test_add_length_add_length() {
	struct linked_list *ll;
	pthread_t tid[4];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *length_args2 = (struct args *)malloc(sizeof(struct args));
	length_args2->ll = ll;
	
	struct args *add_args3 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 6; // value we are adding

	struct args *length_args4 = (struct args *)malloc(sizeof(struct args));
	length_args4->ll = ll;



	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, length_thread, (void *)length_args2);
	pthread_create(&tid[2], NULL, add_thread, (void *)add_args3);
	pthread_create(&tid[3], NULL, length_thread, (void *)length_args4);

	// and then we join all of them to the main thread
	int *val1;
	int *val2;
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], (void*)&val1);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], (void*)&val2);
	printf("len of thread2: %d \n",*val1);
	printf("len of thread4: %d \n",*val2);

	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");

	free(cur);
	free(ll);

	return 0;
}


int test_add_remove_add_add_remove() {
	struct linked_list *ll;
	pthread_t tid[5];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *remove_args2 = (struct args *)malloc(sizeof(struct args));
	remove_args2->ll = ll;
	remove_args2->value = 0; // value we are removing at index
	
	struct args *add_args3 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 7; // value we are adding

	struct args *add_args4 = (struct args *)malloc(sizeof(struct args));
	add_args4->ll = ll;
	add_args4->value = 9; // value we are adding

	struct args *remove_args5 = (struct args *)malloc(sizeof(struct args));
	remove_args5->ll = ll;
	remove_args5->value = 1; // value we are removing at index

	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, remove_thread, (void *)remove_args2);
	pthread_create(&tid[2], NULL, add_thread, (void *)add_args3);
	pthread_create(&tid[3], NULL, add_thread, (void *)add_args4);
	pthread_create(&tid[4], NULL, remove_thread, (void *)remove_args5);

	// and then we join all of them to the main thread
	for (int i = 0; i < 5; i++) {
		pthread_join(tid[i], NULL);
	}
	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");
	free(cur);

	free(ll);

	return 0;
}

int add5() {
	struct linked_list *ll;
	pthread_t tid[5];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *add_args2 = (struct args *)malloc(sizeof(struct args));
	add_args2->ll = ll;
	add_args2->value = 2; // value we are adding
	
	struct args *add_args3 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 7; // value we are adding

	struct args *add_args4 = (struct args *)malloc(sizeof(struct args));
	add_args4->ll = ll;
	add_args4->value = 9; // value we are adding

	struct args *add_args5 = (struct args *)malloc(sizeof(struct args));
	add_args5->ll = ll;
	add_args5->value = 12; // value we are adding

	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, add_thread, (void *)add_args2);
	pthread_create(&tid[2], NULL, add_thread, (void *)add_args3);
	pthread_create(&tid[3], NULL, add_thread, (void *)add_args4);
	pthread_create(&tid[4], NULL, add_thread, (void *)add_args5);

	// and then we join all of them to the main thread
	for (int i = 0; i < 5; i++) {
		pthread_join(tid[i], NULL);
	}

	
	printf("list: ");
	struct node *cur = ll->head;
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}

	printf("\n");

	free(cur);
	free(ll);
	return 0;
}

int test_add_contains_add_contains() {
	struct linked_list *ll;
	pthread_t tid[4];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *contains_args2 = (struct args *)malloc(sizeof(struct args));
	contains_args2->ll = ll;
	contains_args2->value = 3;
	
	struct args *add_args3 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 6; // value we are adding

	struct args *contains_args4 = (struct args *)malloc(sizeof(struct args));
	contains_args4->ll = ll;
	contains_args4->value = 6;



	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, contains_thread, (void *)contains_args2);
	pthread_create(&tid[2], NULL, add_thread, (void *)add_args3);
	pthread_create(&tid[3], NULL, contains_thread, (void *)contains_args4);

	// and then we join all of them to the main thread
	int *val1;
	int *val2;
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], (void*)&val1);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], (void*)&val2);
	printf("contains 3 at position: %d \n",*val1);
	printf("contains 6 at position: %d \n",*val2);

	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");

	free(cur);
	free(ll);

	return 0;
}

int test_add_destroy_remove_destroy() {
	struct linked_list *ll;
	pthread_t tid[4];

	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *destroy_args2 = (struct args *)malloc(sizeof(struct args));
	destroy_args2->ll = ll;
	
	struct args *remove_args3 = (struct args *)malloc(sizeof(struct args));
	remove_args3->ll = ll;
	remove_args3->value = 0; // index we are removing

	struct args *destroy_args4 = (struct args *)malloc(sizeof(struct args));
	destroy_args4->ll = ll;

	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, destroy_thread, (void *)destroy_args2);
	pthread_create(&tid[2], NULL, remove_thread, (void *)remove_args3);
	pthread_create(&tid[3], NULL, destroy_thread, (void *)destroy_args4);

	// and then we join all of them to the main thread
	int *val1;
	int *val2;
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], (void*)&val1);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], (void*)&val2);
	printf("success of destroy: %d \n",*val1);
	printf("succsss of destroy: %d \n",*val2);


	printf("list: ");
	if (*val1 || *val2) {
		struct node *cur = ll->head;
		while (cur!=NULL) {
			printf(" %d",cur->val);
			cur=cur->next;
			
		}
		free(cur);
	}
	printf("\n");

	free(ll);

	return 0;
}

int test_add_remove_print() {
	struct linked_list *ll;
	pthread_t tid[9];

	// example for calling thread functions
	ll = ll_create();

	struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 3; // value we are adding

	struct args *print_args2 = (struct args *)malloc(sizeof(struct args));
	print_args2->ll = ll;

	struct args *remove_args3 = (struct args *)malloc(sizeof(struct args));
	remove_args3->ll = ll;
	remove_args3->value = 0; // index we are removing
	
	struct args *add_args4 = (struct args *)malloc(sizeof(struct args));
	add_args4->ll = ll;
	add_args4->value = 7; // value we are adding

	struct args *print_args5 = (struct args *)malloc(sizeof(struct args));
	print_args5->ll = ll;

	struct args *add_args6 = (struct args *)malloc(sizeof(struct args));
	add_args6->ll = ll;
	add_args6->value = 2; // value we are adding

	struct args *print_args7 = (struct args *)malloc(sizeof(struct args));
	print_args7->ll = ll;

	struct args *remove_args8 = (struct args *)malloc(sizeof(struct args));
	remove_args8->ll = ll;
	remove_args8->value = 0; // index we are removing

	struct args *print_args9 = (struct args *)malloc(sizeof(struct args));
	print_args9->ll = ll;

	// we need to first create each thread
	pthread_create(&tid[0], NULL, add_thread, (void *)add_args1);
	pthread_create(&tid[1], NULL, print_thread, (void *)print_args2);
	pthread_create(&tid[2], NULL, remove_thread, (void *)remove_args3);
	pthread_create(&tid[3], NULL, add_thread, (void *)add_args4);
	pthread_create(&tid[4], NULL, print_thread, (void *)print_args5);
	pthread_create(&tid[5], NULL, add_thread, (void *)add_args6);
	pthread_create(&tid[6], NULL, print_thread, (void *)print_args7);
	pthread_create(&tid[7], NULL, remove_thread, (void *)remove_args8);
	pthread_create(&tid[8], NULL, print_thread, (void *)print_args9);

	// and then we join all of them to the main thread
	for (int i = 0; i<9; i++) {
		pthread_join(tid[i], NULL);
	}

	struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
		
	}
	printf("\n");

	free(cur);
	free(ll);

	return 0;
}

int test_overload() {
	struct linked_list *ll;
	pthread_t tid[37];

	// example for calling thread functions
	ll = ll_create();

	struct args *thread_structs[37];

	// initialize each arg struct
	for (int i = 0; i<37; i++) {
		thread_structs[i] = (struct args *)malloc(sizeof(struct args));
		thread_structs[i]->ll = ll;
		thread_structs[i]->value = 0;
	}

	// then we set the values we will be adding
	for (int i = 0; i<10; i++) {
		thread_structs[i]->value = i;
	}

	// then we set the values we will be searching for
	thread_structs[25]->value = 1;
	thread_structs[26]->value = 3;
	thread_structs[27]->value = 5;
	thread_structs[28]->value = 7;
	thread_structs[29]->value = 4;

	/*struct args *add_args1 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 1; // value we are adding

	struct args *add_args2 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 2; // value we are adding
	
	struct args *add_args3 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 3; // value we are adding

	struct args *add_args4 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 4; // value we are adding

	struct args *add_args5 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 5; // value we are adding

	struct args *add_args6 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 6; // value we are adding

	struct args *add_args7 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 7; // value we are adding
	
	struct args *add_args8 = (struct args *)malloc(sizeof(struct args));
	add_args3->ll = ll;
	add_args3->value = 8; // value we are adding

	struct args *add_args9 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 9; // value we are adding

	struct args *add_args10 = (struct args *)malloc(sizeof(struct args));
	add_args1->ll = ll;
	add_args1->value = 10; // value we are adding

	struct args *remove_args1 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from

	struct args *remove_args2 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from
	
	struct args *remove_args3 = (struct args *)malloc(sizeof(struct args));
	remove_args3->ll = ll;
	remove_args3->value = 0; // index we are removing from

	struct args *remove_args4 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 1; // index we are removing from

	struct args *remove_args5 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from

	struct args *remove_args6 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 1; // index we are removing from

	struct args *remove_args7 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from
	
	struct args *remove_args8 = (struct args *)malloc(sizeof(struct args));
	remove_args3->ll = ll;
	remove_args3->value = 0; // index we are removing from

	struct args *remove_args9 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from

	struct args *remove_args10 = (struct args *)malloc(sizeof(struct args));
	remove_args1->ll = ll;
	remove_args1->value = 0; // index we are removing from

	struct args *length_args1 = (struct args *)malloc(sizeof(struct args));
	length_args1->ll = ll;

	struct args *length_args2 = (struct args *)malloc(sizeof(struct args));
	length_args1->ll = ll;
	
	struct args *length_args3 = (struct args *)malloc(sizeof(struct args));
	length_args3->ll = ll;

	struct args *length_args4 = (struct args *)malloc(sizeof(struct args));
	length_args1->ll = ll;

	struct args *length_args5 = (struct args *)malloc(sizeof(struct args));
	length_args1->ll = ll;

	struct args *contains_args1 = (struct args *)malloc(sizeof(struct args));
	contains_args1->ll = ll;
	contains_args1->value = 1; // value we are containsing

	struct args *contains_args2 = (struct args *)malloc(sizeof(struct args));
	contains_args1->ll = ll;
	contains_args1->value = 3; // value we are containsing
	
	struct args *contains_args3 = (struct args *)malloc(sizeof(struct args));
	contains_args3->ll = ll;
	contains_args3->value = 5; // value we are containsing

	struct args *contains_args4 = (struct args *)malloc(sizeof(struct args));
	contains_args1->ll = ll;
	contains_args1->value = 7; // value we are containsing

	struct args *contains_args5 = (struct args *)malloc(sizeof(struct args));
	contains_args1->ll = ll;
	contains_args1->value = 4; // value we are containsing

	struct args *print_args1 = (struct args *)malloc(sizeof(struct args));
	print_args1->ll = ll;

	struct args *print_args2 = (struct args *)malloc(sizeof(struct args));
	print_args1->ll = ll;
	
	struct args *print_args3 = (struct args *)malloc(sizeof(struct args));
	print_args3->ll = ll;

	struct args *print_args4 = (struct args *)malloc(sizeof(struct args));
	print_args1->ll = ll;

	struct args *print_args5 = (struct args *)malloc(sizeof(struct args));
	print_args1->ll = ll;

	struct args *destroy_args1 = (struct args *)malloc(sizeof(struct args));
	destroy_args1->ll = ll;

	struct args *destroy_args2 = (struct args *)malloc(sizeof(struct args));
	destroy_args1->ll = ll;*/

	/*struct args *add_structs[10] = {add_args1,add_args2,add_args3,add_args4,add_args5,
									add_args6,add_args7,add_args8,add_args9,add_args10};
	struct args *remove_structs[10] = {remove_args1,remove_args2,remove_args3,remove_args4,remove_args5,
									remove_args6,remove_args7,remove_args8,remove_args9,remove_args10};
	struct args *length_structs[10] = {length_args1,length_args2,length_args3,length_args4,length_args5};
	struct args *contains_structs[10] = {contains_args1,contains_args2,contains_args3,contains_args4,contains_args5};
	struct args *print_structs[10] = {print_args1,print_args2,print_args3,print_args4,print_args5};
	struct args *destroy_structs[10] = {destroy_args1,destroy_args2};	*/

	// we need to first create each thread
	/*for (int i = 0; i<10; i++) {
		pthread_create(&tid[i], NULL, add_thread, (void *)thread_structs[i]);
	}
	for (int i = 10; i<20; i++) {
		pthread_create(&tid[i], NULL, remove_thread, (void *)thread_structs[i]);
	}
	for (int i = 20; i<25; i++) {
		pthread_create(&tid[i], NULL, length_thread, (void *)thread_structs[i]);
	}
	for (int i = 25; i<30; i++) {
		pthread_create(&tid[i], NULL, contains_thread, (void *)thread_structs[i]);
	}
	for (int i = 30; i<35; i++) {
		pthread_create(&tid[i], NULL, print_thread, (void *)thread_structs[i]);
	}
	for (int i = 35; i<37; i++) {
		pthread_create(&tid[i], NULL, destroy_thread, (void *)thread_structs[i]);
	}*/

	// and then we join all of them to the main thread
	/*for (int i = 0; i<37; i++) {
		pthread_join(tid[i], NULL);
	}*/

	/*struct node *cur = ll->head;
	printf("list: ");
	while (cur!=NULL) {
		printf(" %d",cur->val);
		cur=cur->next;
	}
	printf("\n");*/

	//free(cur);
	//free(ll);

	return 0;
}

int
main(void)
{
	printf("Code for main.c | mutex \n");

	printf("\nRunning Linked List Test Cases:\n");
	test_add();
	test_length();
	test_remove();
	test_contains();
	test_destroy();

	printf("\nRunning Thread Test Cases:\n");
	printf("Testing Add -> Remove\n");
	for(int i=0;i<10;i++) {
		test_add_remove(); // Running this 10 times will allow 2 possibilities to happen: add -> remove or remove -> add
	}
	printf("Testing Add x 5\n");
	for(int i=0;i<5;i++) {
		add5(); // Running this 5 times will allow the nodes to sometimes be added in different orders
	}
	printf("Testing Add (3) -> remove (0) -> add (7) -> add (9) -> remove (1) \n");
	for(int i=0;i<5;i++) {
		test_add_remove_add_add_remove(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add -> add -> remove (1) -> remove (0)\n");
	for(int i=0;i<10;i++) {
		test_add_add_remove1_remove0(); // Running this 10 times will show different results depending on thread run time order
	}
	printf("Testing Add (3) -> length -> add (6) -> length\n");
	for(int i=0;i<5;i++) {
		test_add_length_add_length(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add (3) -> contains (3) -> add (6) -> contains (6)\n");
	for(int i=0;i<5;i++) {
		test_add_contains_add_contains(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add (3) -> Destroy -> Remove (0) -> Destroy\n");
	for(int i=0;i<5;i++) {
		test_add_destroy_remove_destroy(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add (3) -> Print -> Remove (0) -> Add (7) -> Print -> Add (2) -> Print -> Remove (0) -> Print\n");
	for(int i=0;i<5;i++) {
		test_add_remove_print(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Overload [Addx10,Removex10,Lengthx5,Containsx5,Printx5,Destroyx2]\n");
	for(int i=0;i<1;i++) {
		printf("Iteration %d:",i);
		test_overload(); // Running this 5 times will show different results depending on thread run time order
	}
	return 0;
	
}
