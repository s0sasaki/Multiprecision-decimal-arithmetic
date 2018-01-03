#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_exp(big_float a){ 
	big_float ans, prev, next, one;
	int i;
	one = i_to_bf(1);
	if(a.iszero==true) return one;
	if(a.sign==NEGATIVE){
		a.sign = POSITIVE;
		ans = bf_exp(a);
		ans = bf_div(one, ans);
		return ans;
	}
	ans = one;
	prev = one;
	for(i=1; i<10*NDIGIT*N_ITER_FACTOR; i++){
		if(ans.exp - prev.exp > NDIGIT+1 ) break;
		next = bf_div(bf_mul(prev, a), i_to_bf(i));
		ans  = bf_add(ans, next);
		prev = next;
	}
	return ans;
}
