#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_ln(big_float a){  
	big_float ans, ans_exp, ans_frac, x, xi, x2, prev, next, one, ln10;
	int i,j;
	if(a.iszero==true || a.sign==NEGATIVE){
		fprintf(stderr, "logarithm error!\n");
		sigfpe_error();
	}

	//exp part
	ln10 = s_to_bf("2.302585092 9940456840 1799145468\
                    4364207601 1014886287 7297603332\
                    7900967572 6096773524 8023599720 5089598298");
	ans_exp = bf_mul(i_to_bf(a.exp-Q), ln10); // if |a.exp|>10, it loses significant digits.

	//frac part
	a.exp  = Q;	// 1<a<10
	one = i_to_bf(1);
	x = bf_div(bf_sub(a, one), bf_add(a, one));	// x = (a-1)/(a+1)
	ans_frac  = x;
	prev      = x;
	xi        = x;
	x2        = bf_mul(x, x);
	for(i=0; i<100*NDIGIT*NDIGIT*N_ITER_FACTOR; i++){
		if(ans_exp.exp - prev.exp > NDIGIT+1  ) break;
		j = 2*i + 3;
		xi = bf_mul(xi, x2);
		next = bf_div(xi, i_to_bf(j));
		ans_frac  = bf_add(ans_frac, next);
		prev = next;
	}
	ans_frac = bf_mul(ans_frac, i_to_bf(2));	// ln(a) = 2{x + (x^3)/3 + (x^5)/5 + ..}

    ans = bf_add(ans_exp, ans_frac);
    if(bf_iszero(ans)==true) return bf_zero();
	
	return ans;
}
