#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

int bf_cmp_if(big_float *a, big_float *b){
	return bf_cmp(*a, *b);
}


void bf_add_if(big_float *ans, big_float *a, big_float *b){
	*ans = bf_add(*a, *b);
}

void bf_sub_if(big_float *ans, big_float *a, big_float *b){
	*ans = bf_sub(*a, *b);
}

void bf_mul_if(big_float *ans, big_float *a, big_float *b){
	*ans = bf_mul(*a, *b);
}

void bf_div_if(big_float *ans, big_float *a, big_float *b){
	*ans = bf_div(*a, *b);
}

void bf_exp_if(big_float *ans, big_float *a){
	*ans = bf_exp(*a);
}

void bf_sqrt_if(big_float *ans, big_float *a){
	*ans = bf_sqrt(*a);
}

void bf_ln_if(big_float *ans, big_float *a){
	*ans = bf_ln(*a);
}

void s_to_bf_if(big_float *ans, char *s){
	*ans = s_to_bf(s);
}

void bf_to_s_if(char *s, big_float *a){
	bf_to_s(*a, s);
}

//memo
//bf_rand_static_if is at bf_rand.c
//
//void bf_rand_static_if(big_float *a){
//    *a = bf_rand_static();
//}

