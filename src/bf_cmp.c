#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

int bf_cmp_abs(big_float a, big_float b){
	int i;
    if((a.iszero==true)&&(b.iszero==true)) return 0;
    else if(a.iszero==true) return -1;
    else if(b.iszero==true) return 1;
	if(a.exp > b.exp) return 1;
	if(a.exp < b.exp) return -1;
	for(i=0; i<NDIGIT; i++){
		if(a.frac[i] > b.frac[i]) return 1;
		if(a.frac[i] < b.frac[i]) return -1;
	}
	return 0;
}

int bf_cmp(big_float a, big_float b){
	if((a.sign == POSITIVE)&&(b.sign == POSITIVE)) return bf_cmp_abs(a,b);
	if((a.sign == POSITIVE)&&(b.sign == NEGATIVE)) return 1;
	if((a.sign == NEGATIVE)&&(b.sign == POSITIVE)) return -1;
	if((a.sign == NEGATIVE)&&(b.sign == NEGATIVE)) return -1*bf_cmp_abs(a,b);
	sigfpe_error();
	return 0;
}

