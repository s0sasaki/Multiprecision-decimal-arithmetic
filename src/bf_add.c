#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_add(big_float a, big_float b){
	big_float ans;
	if(a.iszero==true) return b;
	if(b.iszero==true) return a;
	if(a.sign==POSITIVE && b.sign==POSITIVE){
		ans = bf_add_abs(a,b);	
		ans.sign = POSITIVE;
	}else if(a.sign==NEGATIVE && b.sign==NEGATIVE){
		ans = bf_add_abs(a,b);	
		ans.sign = NEGATIVE;
	}else if(a.sign==POSITIVE && b.sign==NEGATIVE){
		if(bf_cmp_abs(a,b)>0){
			ans = bf_sub_abs(a,b);
			ans.sign = POSITIVE;
		}else{
			ans = bf_sub_abs(b,a);
			ans.sign = NEGATIVE;
		}
	}else if(a.sign==NEGATIVE && b.sign==POSITIVE){
		if(bf_cmp_abs(a,b)>0){
			ans = bf_sub_abs(a,b);
			ans.sign = NEGATIVE;
		}else{
			ans = bf_sub_abs(b,a);
			ans.sign = POSITIVE;
		}
	}
	return ans;
}


big_float bf_add_abs(big_float a, big_float b){
	big_float u,v,ans;
	int carry;
	int i;
	int ufrac[NDIGIT*2];
	int vfrac[NDIGIT*2];
	int ansfrac[NDIGIT*2];
	if(a.exp > b.exp){
		u = a;
		v = b;
	}else{
		u = b;
		v = a;
	}
	for(i=0; i<NDIGIT; i++){
		ufrac[i] = u.frac[i];
		vfrac[i] = v.frac[i];
	}
	for(i=NDIGIT; i<NDIGIT*2; i++){
		ufrac[i] = 0;
		vfrac[i] = 0;
	}
	
	//scale right
	if( u.exp != v.exp){
		if( u.exp-v.exp < NDIGIT*2){
			for(i=NDIGIT*2-1; (unsigned int)i>=(u.exp-v.exp); i--){
				vfrac[i] = vfrac[i - (u.exp-v.exp)];
			}
			for(;i>=0; i--){
				vfrac[i] = 0;
			}
		}else{
			for(i=0; i<NDIGIT*2; i++){
				vfrac[i] = 0;
			}
		}
	}

	//addition
	ans.sign = POSITIVE;
	ans.exp  = u.exp;
	carry    = 0;
	for(i=NDIGIT*2-1; i>=0; i--){
		ansfrac[i] = (ufrac[i] + vfrac[i] + carry)%10;
		carry      = (ufrac[i] + vfrac[i] + carry)/10;
	}
	if(carry>0){
		for(i=NDIGIT*2-1; i>0; i--){
			ansfrac[i] = ansfrac[i-1];
		}
		ansfrac[0] = carry;
		ans.exp = add_uint(ans.exp, 1);
	}

	//round
	if(ansfrac[NDIGIT] >= 5) carry = 1;
	else			 carry = 0;
	for(i=NDIGIT-1; i>=0; i--){
		ans.frac[i] = (ansfrac[i] + carry)%10;
		carry       = (ansfrac[i] + carry)/10;
		if(i==0) break;
	}
	ans = norm_carryup(ans, carry);

	if(bf_iszero(ans)==true) return bf_zero();
	else ans.iszero = false;
	return ans;
}
