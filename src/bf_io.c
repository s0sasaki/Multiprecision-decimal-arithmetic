#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

void bf_print(big_float a){
	int i;
	if(a.sign == NEGATIVE) printf("sign:-\t");
	if(a.sign == POSITIVE) printf("sign:+\t");
	printf("exp:%u \tfrac:", a.exp);
	for(i=0; i<NDIGIT; i++) printf("%d", a.frac[i]);
	printf("\n");
}

void bf_to_s(big_float a, char* s){
	int i;
	char s_sign[2];
	char s_int[STR_SIZE_MAX];
	char s_frac[STR_SIZE_MAX];
	if(a.exp > STR_SIZE_MAX+Q-2) {
		fprintf(stderr, "too big to bf_to_s !\n");
		sigfpe_error();
	}
	if(Q+NDIGIT+2 > STR_SIZE_MAX+a.exp){
		fprintf(stderr, "too small to bf_to_s !\n");
		sigfpe_error();
	}
	
	if (a.sign==POSITIVE) s_sign[0]='+';
	if (a.sign==NEGATIVE) s_sign[0]='-';
	s_sign[1] = '\0';

	if(a.exp>Q+NDIGIT-2){
		for(i=0; i<NDIGIT; i++)       s_int[i]=a.frac[i]+'0';
		for(i=NDIGIT; (unsigned int)i<a.exp-Q+1; i++) s_int[i]='0';
		s_int[a.exp-Q+1] = '\0';
		s_frac[0] = '0';
		s_frac[1] = '\0';
	}else if(Q <= a.exp && a.exp <= Q+NDIGIT-2){
		for(i=0; (unsigned int)i<a.exp-Q+1; i++)      s_int[i]=a.frac[i]+'0';
		s_int[a.exp-Q+1] = '\0';
		for(i=a.exp-Q+1; i<NDIGIT; i++) s_frac[i-a.exp+Q-1]= a.frac[i]+'0';
		s_frac[NDIGIT-a.exp+Q-1] = '\0';
	}else if(a.exp < Q){
		s_int[0] = '0';
		s_int[1] = '\0';
		for(i=0; (unsigned int)i<Q-a.exp-1; i++) s_frac[i]='0';
		for(i=Q-a.exp-1; (unsigned int)i<NDIGIT+Q-a.exp-1; i++) s_frac[i]= a.frac[i-Q+a.exp+1]+'0'; //; -1;
		s_frac[NDIGIT+Q-a.exp-1] = '\0'; //fixedsign and -1
	}
	sprintf(s, "%c%s.%s", s_sign[0], s_int, s_frac);
}

big_float s_to_bf(char *s){
	big_float a;
	char *p;
	int i;
	int flag_exp;
	a.sign = POSITIVE;
	a.exp  = Q-1;
	for(i=0; i<NDIGIT; i++) a.frac[i] = 0;

	flag_exp = 1;
	i = 0;
	p = s;
	if(*p == '-'){
		a.sign	= NEGATIVE;
		p++;
	}else if(*p == '+'){
		p++;
	}
	if('1' <= *p && *p <= '9'){
		for(; *p != '\0'; p++){
			if('0' <= *p && *p <= '9'){
				if(i < NDIGIT){
					a.frac[i] = *p - '0';
					i++;
				}
				if(flag_exp) a.exp++;
			}
			if(*p == '.') flag_exp = 0;
		}
	}else if(*p == '0'){
		p++; // skip '0'
        if(*p == '\0') return bf_zero();
		if(*p != '.' ){
			fprintf(stderr,"s_to_b() format error! Start with 0.?\n");
			sigfpe_error();
		}
		if(*p == '.' ) p++; // skip '.'
		for(; *p != '\0'; p++){
			if('1' <= *p && *p <= '9') flag_exp = 0;
			if('0' <= *p && *p <= '9'){
				if(!flag_exp){
					if(i < NDIGIT){
						a.frac[i] = *p - '0';
						i++;
					}
				}else{
					a.exp--;
				}
			}
		}
	}
	
	if(bf_iszero(a)==true) return bf_zero();
	else a.iszero = false;
	
	return a; // zero check!
}

big_float i_to_bf(unsigned int i){
	char s[64*NDIGIT]; 
	sprintf(s, "%d", i);
	return s_to_bf(s);
}


