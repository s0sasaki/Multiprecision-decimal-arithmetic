#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

#define TEST_REPEATE 5

void test_bf_rand_linear_congruential_generator(){
	int i,j;
	int seed[NDIGIT];
	bf_rand_seed_set(seed, 10);
	for(i=0; i<TEST_REPEATE; i++){
        //printf("  ");
		for(j=0; j<NDIGIT; j++){
			//printf("%d", seed[j]);
		}
		//printf("\n");
		bf_rand_linear_congruential_generator(seed);
	}
}

void test_bf_rand(){
	big_float a;
	int i;
	char s[STR_SIZE_MAX];
	int seed[NDIGIT];
	bf_rand_seed_set(seed, 10);
	for(i=0; i<TEST_REPEATE; i++){
		a = bf_rand(seed);
		bf_to_s(a,s);
		//printf("  %s\n",s);
	}
}

void test_bf_rand_static(){
	big_float a;
	int i;
	char s[STR_SIZE_MAX];
	bf_rand_seed_set_static(10);
	for(i=0; i<TEST_REPEATE; i++){
		a = bf_rand_static();
		bf_to_s(a,s);
		//printf("  %s\n",s);
	}
}

void main(){
    //printf("test_bf_rand_linear_congruential_generator:\n");
	test_bf_rand_linear_congruential_generator();
    //printf("test_bf_rand:\n");
	test_bf_rand();
    //printf("test_bf_rand_static:\n");
	test_bf_rand_static();
    printf("------------------------------------------------------------\n");
    printf("Ran all functions.\n");
    printf("The functions should be tested at unittests of test_bigfloat.py.\n\n");
    printf("OK\n");
}


