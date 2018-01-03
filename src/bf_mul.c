#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_mul(big_float a, big_float b){ 
	big_float ans;
	if(a.iszero==true) return bf_zero();
	if(b.iszero==true) return bf_zero();
	ans = bf_mul_abs(a,b);
	if(a.sign==POSITIVE && b.sign==POSITIVE){
		ans.sign = POSITIVE;
	}else if(a.sign==POSITIVE && b.sign==NEGATIVE){
		ans.sign = NEGATIVE;
	}else if(a.sign==NEGATIVE && b.sign==POSITIVE){
		ans.sign = NEGATIVE;
	}else if(a.sign==NEGATIVE && b.sign==NEGATIVE){
		ans.sign = POSITIVE;
	}
	return ans;
}

big_float bf_mul_abs(big_float u, big_float v){ 
	big_float ans;
	int carry;
	int i,j;
	int ufrac[NDIGIT];
	int vfrac[NDIGIT];
	int ansfrac[NDIGIT*2];
	for(i=0; i<NDIGIT; i++){
		ufrac[i] = u.frac[i];
		vfrac[i] = v.frac[i];
	}
	for(i=0; i<NDIGIT*2; i++){
		ansfrac[i] = 0;
	}
	ans.sign = POSITIVE;
	
	//multiplication (exp part)
	if(detect_overflow_add_uint(u.exp, v.exp)==0){
		ans.exp = sub_uint(add_uint(u.exp, v.exp), Q);
	}else if(detect_underflow_sub_uint(u.exp, Q)==0){
		ans.exp = add_uint(sub_uint(u.exp, Q), v.exp);
	}else{
		ans.exp = add_uint(sub_uint(v.exp, Q), u.exp);
	}

	//multiplication (frac part)
	for(i=NDIGIT-1; i>=0; i--){
		for(j=NDIGIT-1; j>=0; j--){
			ansfrac[i+j+1] += (ufrac[i] * vfrac[j])%10;
			if((ufrac[i] * vfrac[j])/100 >0){
				ansfrac[i+j-1] += (ufrac[i] * vfrac[j])/100;
			}
			if(((ufrac[i] * vfrac[j])%100)/10 >0){
				ansfrac[i+j] += ((ufrac[i] * vfrac[j])%100)/10;
			}
		}
	}

	//scale left
	for(i=0; i<NDIGIT*2; i++){
		if(ansfrac[i] != 0) break;	
	}
	if(i==0){
		ans.exp = add_uint(ans.exp, 1);
	}else if(i < NDIGIT*2){
		ans.exp = sub_uint(ans.exp, i-1);
		for(j=0; j<NDIGIT*2-i; j++){
			ansfrac[j] = ansfrac[j+i];
		}
		for(j=NDIGIT*2-i; j<NDIGIT*2; j++){
			ansfrac[j] = 0;
		}
	}
	
	//round
	if(ansfrac[NDIGIT] >= 5) carry = 1;
	else			 carry = 0;
	for(i=NDIGIT-1; i>=0; i--){
		ans.frac[i] = (ansfrac[i] + carry)%10;
		carry       = (ansfrac[i] + carry)/10;
	}
	ans = norm_carryup(ans, carry);
	
	if(bf_iszero(ans)==true) return bf_zero();
	else ans.iszero = false;
	return ans;
}
