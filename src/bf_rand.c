#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

void bf_rand_linear_congruential_generator(int* x){ //period: 5*10^(NDIGIT-2)
	int A[NDIGIT];
	int tmp[NDIGIT*2];
	int i,j,carry;

	for(i=0; i<NDIGIT*2; i++){
		tmp[i] = 0;
	}
	for(i=0; i<NDIGIT; i++){ 	//A = 171 or 117 (mod 200)
		if(i%2==0) A[i] = 1;
		if(i%2==1) A[i] = 7;
	}

	//multiplication
	for(i=NDIGIT-1; i>=0; i--){
		for(j=NDIGIT-1; j>=0; j--){
			tmp[i+j+1] += (x[i] * A[j])%10;
			if((x[i] * A[j])/100 >0){
				tmp[i+j-1] += (x[i] * A[j])/100;
			}
			if(((x[i] * A[j])%100)/10 >0){
				tmp[i+j] += ((x[i] * A[j])%100)/10;
			}
		}
	}
	carry = 0;
	for(i=2*NDIGIT-1; i>=0; i--){
		tmp[i] = (tmp[i] + carry)%10;
		carry  = (tmp[i] + carry)/10;
	}
	
	//mod 10^NDIGIT
	for(i=0; i<NDIGIT; i++){
		x[i] = tmp[i+NDIGIT];
	}
}

void bf_rand_seed_set(int* seed, int n){
	int i;
	for(i=0; i<NDIGIT; i++)	seed[i] = 1;
	for(i=0; i<n; i++) 	bf_rand_linear_congruential_generator(seed);
}

big_float bf_rand(int* seed){
	big_float a;
	int i,j;
	a.iszero = false;
	a.sign   = POSITIVE;
	a.exp    = Q-1;

	bf_rand_linear_congruential_generator(seed);
	for(i=0; i<NDIGIT; i++) a.frac[i] = seed[i];
	for(i=0; i<NDIGIT; i++){
		if(a.frac[i]!=0) break;
	}
	if(i==NDIGIT){
		return bf_zero();
	}else if(i>0){
		a.exp = sub_uint(a.exp, i);
		for(j=0;      j+i<NDIGIT; j++) a.frac[j]=a.frac[j+i];
		for(j=NDIGIT; j  <NDIGIT; j++) a.frac[j]=0;
	}
	return a;
}

void bf_rand_seed_set_static(int n){
    bf_rand_seed_set(seed, n);
}

big_float bf_rand_static(void){
    return bf_rand(seed);
}

void bf_rand_static_if(big_float *a){
    *a = bf_rand_static();
}

