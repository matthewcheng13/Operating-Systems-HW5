#include "list.h"

void *add_thread(void *argp) {
	struct args *add_args = (struct args*)argp;
	ll_add(add_args->ll, add_args->value);

	pthread_exit(NULL);
}

void *length_thread(void *argp) {
	struct args *length_args = (struct args*)argp;
	length_args->result = ll_length(length_args->ll);

	pthread_exit(NULL);
}

void *remove_thread(void *argp) {
	struct args *remove_args = (struct args*)argp;
	remove_args->result = ll_remove(remove_args->ll, remove_args->value);

	pthread_exit(NULL);
}

void *contains_thread(void *argp) {
	struct args *contains_args = (struct args*)argp;
	contains_args->result = ll_contains(contains_args->ll, contains_args->value);

	pthread_exit(NULL);
}

void *print_thread(void *argp) {
	struct args *print_args = (struct args*)argp;
	ll_print(print_args->ll);

	pthread_exit(NULL);
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
	printf("\n ");


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

	free(ll);
	printf("list: %d %d %d %d %d \n",ll->head->val,ll->head->next->val,ll->head->next->next->val,ll->head->next->next->next->val,ll->head->next->next->next->next->val);

	return 0;
}


int
main(void)
{
	add5();
	test_add_remove_add_add_remove();
	return 0;
	struct linked_list *ll;

	// ll_create
	ll = ll_create();
	free(ll);
	
	// ll_destroy empty
	ll = ll_create();
	int temp = ll_destroy(ll);
	if (temp == 0) {
		printf("fail 1\n");
	}

	// ll destroy with items
	ll = ll_create();
	ll_add(ll, 3);
	temp = ll_destroy(ll);
	if (temp == 1) {
		printf("fail 2\n");
	}
	free(ll);

	// ll_destroy emptied
	ll = ll_create();
	ll_add(ll, 3);
	ll_remove(ll,0);
	temp = ll_destroy(ll);
	if (temp == 0) {
		printf("fail 3\n");
	}

	// ll_destroy emptied and then added again
	ll = ll_create();
	ll_add(ll, 3);
	ll_remove(ll,0);
	ll_add(ll, 1);
	temp = ll_destroy(ll);
	if (temp == 1) {
		printf("fail 4\n");
	}
	free(ll);

	// ll_add empty
	ll = ll_create();
	ll_add(ll, 6);
	free(ll);

	// ll_add twice
	ll = ll_create();
	ll_add(ll, 3);
	ll_add(ll, 8);
	free(ll);
	
	// ll_add three times
	ll = ll_create();
	ll_add(ll, 2);
	ll_add(ll, 1);
	ll_add(ll, 9);
	free(ll);

	// ll_add add, remove, add
	ll = ll_create();
	ll_add(ll, 3);
	ll_remove(ll,0);
	ll_add(ll, 3);
	free(ll);

	// ll_length empty
	ll = ll_create();
	temp = ll_length(ll);
	if (temp != 0) {
		printf("fail 5\n");
	}
	free(ll);

	// ll_length one
	ll = ll_create();
	ll_add(ll, 6);
	temp = ll_length(ll);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 6\n");
	}
	free(ll);

	// ll_length two
	ll = ll_create();
	ll_add(ll,1);
	ll_add(ll,4);
	temp = ll_length(ll);
	if (temp != 2) {
		printf("%d ", temp);
		printf("fail 7\n");
	}
	free(ll);

	// ll_length add, remove
	ll = ll_create();
	ll_add(ll,7);
	ll_remove(ll,0);
	temp = ll_length(ll);
	if (temp != 0) {
		printf("fail 8\n");
	}
	free(ll);

	// ll_length add, remove, add
	ll = ll_create();
	ll_add(ll,7);
	ll_remove(ll,0);
	ll_add(ll,7);
	temp = ll_length(ll);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 9\n");
	}
	free(ll);

	// ll_length add, add, remove
	ll = ll_create();
	ll_add(ll,7);
	ll_add(ll,6);
	ll_remove(ll,0);
	temp = ll_length(ll);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 10\n");
	}
	free(ll);

	// remove empty
	ll = ll_create();
	bool tb = ll_remove(ll,0);
	if (tb != false) {
		printf("fail 11\n");
	}
	free(ll);

	// remove one
	ll = ll_create();
	ll_add(ll,5);
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 12\n");
	}
	free(ll);

	// remove twice not empty
	ll = ll_create();
	ll_add(ll,5);
	ll_add(ll,-1);
	ll_add(ll,8);
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 13\n");
	}
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 14\n");
	}
	free(ll);

	// remove twice empty
	ll = ll_create();
	ll_add(ll,9);
	ll_add(ll,-3);
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 15\n");
	}
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 16\n");
	}
	free(ll);

	// remove remove, add, remove
	ll = ll_create();
	tb = ll_remove(ll,0);
	if (tb != false) {
		printf("fail 17\n");
	}
	ll_add(ll,15);
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 18\n");
	}
	free(ll);

	// remove twice with only one
	ll = ll_create();
	ll_add(ll,-7);
	tb = ll_remove(ll,0);
	if (tb != true) {
		printf("fail 19\n");
	}
	tb = ll_remove(ll,0);
	if (tb != false) {
		printf("fail 20\n");
	}
	free(ll);

	// contains empty 0
	ll = ll_create();
	temp = ll_contains(ll,0);
	if (temp != 0) {
		printf("fail 21\n");
	}
	free(ll);

	// contains empty non-0
	ll = ll_create();
	temp = ll_contains(ll,3);
	if (temp != 0) {
		printf("fail 22\n");
	}
	free(ll);

	// contains one true
	ll = ll_create();
	ll_add(ll,6);
	temp = ll_contains(ll,6);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 23\n");
	}
	free(ll);

	// contains one false
	ll = ll_create();
	ll_add(ll,4);
	temp = ll_contains(ll,1);
	if (temp != 0) {
		printf("fail 24\n");
	}
	free(ll);

	// contains two same
	ll = ll_create();
	ll_add(ll,3);
	ll_add(ll,3);
	temp = ll_contains(ll,3);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 25\n");
	}
	free(ll);

	// contains two different first
	ll = ll_create();
	ll_add(ll,5);
	ll_add(ll,10);
	temp = ll_contains(ll,10);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 26\n");
	}
	free(ll);

	// contains two different second
	ll = ll_create();
	ll_add(ll,8);
	ll_add(ll,-3);
	temp = ll_contains(ll,8);
	if (temp != 2) {
		printf("%d ", temp);
		printf("fail 27\n");
	}
	free(ll);

	// contains add, remove
	ll = ll_create();
	ll_add(ll,4);
	ll_remove(ll,0);
	temp = ll_contains(ll,4);
	if (temp != 0) {
		printf("fail 28\n");
	}
	free(ll);

	// contains one after removal same
	ll = ll_create();
	ll_add(ll,4);
	ll_add(ll,4);
	ll_remove(ll,0);
	temp = ll_contains(ll,4);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 29\n");
	}
	free(ll);

	// contains one after removal different true
	ll = ll_create();
	ll_add(ll,4);
	ll_add(ll,7);
	ll_remove(ll,0);
	temp = ll_contains(ll,4);
	if (temp != 1) {
		printf("%d ", temp);
		printf("fail 30\n");
	}
	free(ll);

	// contains one after removal different false
	ll = ll_create();
	ll_add(ll,4);
	ll_add(ll,7);
	ll_remove(ll,0);
	temp = ll_contains(ll,7);
	if (temp != 0) {
		printf("fail 31\n");
	}
	free(ll);

	ll = ll_create();
	ll_add(ll,3);
	ll_add(ll,6);
	ll_add(ll,5);
	ll_remove(ll,0);
	ll_add(ll,-9);
	ll_remove(ll,0);
	ll_add(ll,19);
	ll_add(ll,8);
	ll_add(ll,8);
	ll_add(ll,3);
	ll_add(ll,4);
	ll_remove(ll,0);
	ll_add(ll,1);
	ll_print(ll);
	
	return 0;
}
