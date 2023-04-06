#include "list.h"

/****************************************
THREADS
****************************************/

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

	pthread_exit(NULL);
}

/****************************************
TESTS
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


int
main(void)
{
	printf("Testing Add -> Remove\n");
	for(int i=0;i<10;i++) {
		test_add_remove(); // Running this 10 times will allow 2 possibilities to happen: add -> remove or remove -> add
	}
	printf("Testing Add x 5\n");
	for(int i=0;i<5;i++) {
		add5(); // Running this 5 times will allow the nodes to sometimes be added in different orders
	}
	printf("Testing Add -> remove -> add -> add -> remove \n");
	for(int i=0;i<5;i++) {
		test_add_remove_add_add_remove(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add -> add -> remove -> remove \n");
	for(int i=0;i<10;i++) {
		test_add_add_remove1_remove0(); // Running this 10 times will show different results depending on thread run time order
	}
	printf("Testing Add -> length -> add -> length\n");
	for(int i=0;i<5;i++) {
		test_add_length_add_length(); // Running this 5 times will show different results depending on thread run time order
	}
	printf("Testing Add -> contains (3) -> add -> contains (6)\n");
	for(int i=0;i<5;i++) {
		test_add_contains_add_contains(); // Running this 5 times will show different results depending on thread run time order
	}
	return 0;
	
}
