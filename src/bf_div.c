#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_div(big_float a, big_float b){ 
	big_float ans;
	if(b.iszero==true) zerodiv_error();
	if(a.iszero==true) return bf_zero();
	ans = bf_div_abs(a,b);
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

big_float bf_div_abs(big_float u, big_float v){ 
	big_float ans;
	int carry;
	bool u_gt_v_flag;
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

	for(i=0; i<NDIGIT*2; i++){
		ansfrac[i] = 0;
	}
	ans.sign = POSITIVE;
	
	//division (exp part)
	if(detect_overflow_add_uint(u.exp, Q)==0){
		ans.exp = sub_uint(add_uint(u.exp, Q), v.exp);
	}else if(detect_underflow_sub_uint(u.exp, v.exp)==0){
		ans.exp = add_uint(sub_uint(u.exp, v.exp), Q);
	}else{
		ans.exp = add_uint(sub_uint(Q, v.exp), u.exp);
	}

	//division (frac part)
	for(i=0; i<NDIGIT+2; i++){
		for(;;){ 
			//ufrac >= vfrac ?
			u_gt_v_flag = true;
			for(j=0; j<NDIGIT*2; j++){
				if(ufrac[j]>vfrac[j]){
					break;
				}else if(ufrac[j]<vfrac[j]){
					u_gt_v_flag =false;
					break;
				}
			}
			
			//if ufrac >= vfrac, 
			if(u_gt_v_flag==true){
				
				ansfrac[i] += 1;

				// ufrac = ufrac - ufrac
				carry    = 0;
				for(j=NDIGIT*2-1; j>=0; j--){
					if(ufrac[j] - vfrac[j] -carry >=0){
						ufrac[j] = ufrac[j] - vfrac[j] -carry;
						carry      = 0;
					}else{
						ufrac[j] = ufrac[j] - vfrac[j] -carry +10;
						carry      = 1;
					}
				}
			}else{ 
				//if ufrac < vfrac,
				break;
			}
		}
		
		//vfrac >> 1;
		for(j=NDIGIT*2-1; j>0; j--){
			vfrac[j] = vfrac[j-1];
		}
		vfrac[0] = 0;
	}

	//for(j=0; j<NDIGIT*2; j++){ printf("%d", vfrac[j]); } printf("\n");
	//for(j=0; j<NDIGIT*2; j++){ printf("%d", ansfrac[j]); } printf("\n");

	//scale left
	if(ansfrac[0]==0){
		for(j=0; j<NDIGIT*2; j++){
			ansfrac[j] = ansfrac[j+1];
		}
		ans.exp = sub_uint(ans.exp, 1);
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
