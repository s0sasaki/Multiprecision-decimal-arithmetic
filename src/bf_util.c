#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

big_float bf_zero(){
	int i;
	big_float a;
	a.iszero = true;
	a.sign = POSITIVE;
	a.exp  = Q;
	for(i=0; i<NDIGIT; i++){
		a.frac[i] = 0;
	}
	return a;
}

bool bf_iszero(big_float a){
	int i;
	for(i=0; i<NDIGIT; i++){
		if(a.frac[i] != 0) return false;
	}
	return true;
}

void sigfpe_error(){
	union sigval value;
	pid_t pid;
	pid = getpid();
	sigqueue(pid, SIGFPE, value);
}

void overflow_error(){
	fprintf(stderr, "overflow error!\n");
	sigfpe_error();
}

void underflow_error(){
	fprintf(stderr, "underflow error!\n");
	sigfpe_error();
}

void zerodiv_error(){
	fprintf(stderr, "division-by-zero error!\n");
	sigfpe_error();
}


bool detect_underflow_sub_uint(unsigned int a, unsigned int b){
	if(a < b)	return true;
	else 		return false;
}

bool detect_overflow_add_uint(unsigned int a, unsigned int b){
	if(UINT_MAX - a >= b)	return false;
	else 			return true;
}


unsigned int add_uint(unsigned int a, unsigned int b){
	if(detect_overflow_add_uint(a,b)==true){
		overflow_error();
	}
	return a+b;
}

unsigned int sub_uint(unsigned int a, unsigned int b){
	if(detect_underflow_sub_uint(a,b)==true){
		underflow_error();
	}
	return a-b;
}

big_float norm_carryup(big_float a, int carry){
	big_float b;
	int i;
	if(carry > 0){
		b.sign = a.sign;
		b.exp  = add_uint(a.exp,1);
		for(i=NDIGIT-1; i>0; i--){
			b.frac[i] = a.frac[i-1];	
		}	
		b.frac[0] = carry;
	}else{
		b = a;
	}
	return b;
}



