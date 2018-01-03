#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_sqrt(big_float a){  // Newton's method 
	big_float x_old, x_new, two;
	int i;
	if(a.iszero==true) return bf_zero();
	if(a.sign==NEGATIVE){
		fprintf(stderr, "sqrt_error!\n");
		sigfpe_error();
	}
	two   = i_to_bf(2);
	x_old = a;
	for(i=0; i<10*NDIGIT*N_ITER_FACTOR; i++){
		x_new = bf_div(bf_add(x_old, bf_div(a, x_old)),two);
		x_old = x_new;
	}
	return x_new;
}
