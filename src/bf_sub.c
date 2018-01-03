#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif


big_float bf_sub(big_float a, big_float b){ 
	big_float ans;
	if(b.iszero==true) return a;
	else if(a.iszero==true){
		ans = b;
		if(b.sign==POSITIVE)  ans.sign = NEGATIVE;
		else                  ans.sign = POSITIVE;
		return ans;
	}
	if(a.sign==POSITIVE && b.sign==NEGATIVE){
		ans = bf_add_abs(a,b);	
		ans.sign = POSITIVE;
	}else if(a.sign==NEGATIVE && b.sign==POSITIVE){
		ans = bf_add_abs(a,b);	
		ans.sign = NEGATIVE;
	}else if(a.sign==POSITIVE && b.sign==POSITIVE){
		if(bf_cmp_abs(a,b)>NEGATIVE){
			ans = bf_sub_abs(a,b);
			ans.sign = POSITIVE;
		}else{
			ans = bf_sub_abs(b,a);
			ans.sign = NEGATIVE;
		}
	}else if(a.sign==NEGATIVE && b.sign==NEGATIVE){
		if(bf_cmp_abs(a,b)>NEGATIVE){
			ans = bf_sub_abs(a,b);
			ans.sign = NEGATIVE;
		}else{
			ans = bf_sub_abs(b,a);
			ans.sign = POSITIVE;
		}
	}
	return ans;
}

big_float bf_sub_abs(big_float u, big_float v){ // u>v>0
	big_float ans;
	int carry;
	int i,j;
	int ufrac[NDIGIT*2];
	int vfrac[NDIGIT*2];
	int ansfrac[NDIGIT*2];
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

	//subduction
	ans.sign = POSITIVE;
	ans.exp  = u.exp;
	carry    = 0;
	for(i=NDIGIT*2-1; i>=0; i--){
		if(ufrac[i] - vfrac[i] -carry >=0){
			ansfrac[i] = ufrac[i] - vfrac[i] -carry;
			carry      = 0;
		}else{
			ansfrac[i] = ufrac[i] - vfrac[i] -carry +10;
			carry      = 1;
		}
	}

	//scale left
	for(i=0; i<NDIGIT*2; i++){
		if(ansfrac[i] != 0) break;	
	}
	ans.exp = sub_uint(ans.exp, i);
	if(i<NDIGIT*2){
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
	//ans = norm_carryup(ans, carry);

	if(bf_iszero(ans)==true) return bf_zero();
	else ans.iszero = false;
	return ans;
}
