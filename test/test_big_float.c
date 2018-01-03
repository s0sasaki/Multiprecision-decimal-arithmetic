#ifndef CONTROL_FOR_CFFI
#include "big_float.h"
#endif

int main(void){
	big_float a,b,c;
	char *s, *s1, *s2;
	char s3[STR_SIZE_MAX];
	int i;

	//printf("s_to_bf--------------------------------------------\n");
	s = "1";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "-123.456789012";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "123456789012345";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "0.1";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "0.001234567890";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "0. 00000 00000 00000 12345 00001";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	s = "0. 00000";
	//printf("%s:\n", s);
	a = s_to_bf(s);
	//bf_print(a);

	//printf("bf_cmp--------------------------------------------\n");
	s1 = "12.3";
	s2 = "0.0456";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	//bf_print(a);
	//bf_print(b);
	i = bf_cmp(a,b);
	//printf("=> %s > %s: %d\n", s1, s2, i);
	i = bf_cmp(b,a);
	//printf("=> %s < %s: %d\n", s1, s2, i);
	
	s1 = "1";
	s2 = "2";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	//bf_print(a);
	//bf_print(b);
	i = bf_cmp(a,b);
	//printf("=> %s > %s: %d\n", s1, s2, i);
	i = bf_cmp(b,a);
	//printf("=> %s < %s: %d\n", s1, s2, i);
	
	s1 = "9.99";
	s2 = "9.99";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	i = bf_cmp(a,b);
	//bf_print(a);
	//bf_print(b);
	//printf("=> %s > %s: %d\n", s1, s2, i);
	
	s1 = "-12.3";
	s2 = "0.0456";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	//bf_print(a);
	//bf_print(b);
	i = bf_cmp(a,b);
	//printf("=> %s > %s: %d\n", s1, s2, i);
	i = bf_cmp(b,a);
	//printf("=> %s < %s: %d\n", s1, s2, i);
	
	//printf("bf_add--------------------------------------------\n");
	s1 = "12.3";
	s2 = "0.0456";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1";
	s2 = "2";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "9.99";
	s2 = "9.99";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1.111 111 111";
	s2 = "0.111 111 1115";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "9.900 000 099";
	s2 = "0.100 000 000 9";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);


	s1 = "9.111 111 111";
	s2 = "0.888 888 8885";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	//printf("bignum + bignum :\n");
	a.exp = UINT_MAX;
	b.exp = UINT_MAX;
	a.frac[0] = 5;
	b.frac[0] = 5;
	//c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	////bf_print(c);

	s1 = "9.111 111 111";
	s2 = "0.888 888 8885";
	//printf("%s(bignum) + %s(bignum):\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = UINT_MAX;
	b.exp = UINT_MAX-1;
	//c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	////bf_print(c);

	s1 = "2";
	s2 = "-5";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "-2";
	s2 = "5";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "-2";
	s2 = "-5";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "0";
	s2 = "0";
	//printf("%s + %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_add(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);


	//printf("bf_sub-------------------------------------------\n");
	s1 = "12.3";
	s2 = "0.0456";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1.000 000 002";
	s2 = "1.000 000 001";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1.000 000 001";
	s2 = "1.000 000 001";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1.000 000 002(smallnum)";
	s2 = "1.000 000 001(smallnum)";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = 0;
	b.exp = 0;
	//bf_print(a);
	//bf_print(b);
	//c = bf_sub(a,b);
	////bf_print(c);

	s1 = "2";
	s2 = "-5";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "-2";
	s2 = "5";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "-2";
	s2 = "-5";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "0";
	s2 = "0";
	//printf("%s - %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_sub(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);


	//printf("bf_mul-------------------------------------------\n");
	s1 = "998";
	s2 = "9.89";
	//printf("%s * %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_mul(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "9.9";
	s2 = "9.000 000 009";
	//printf("%s * %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_mul(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "0";
	s2 = "0";
	//printf("%s * %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_mul(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);


	s1 = "9.999 999 999(big)";
	s2 = "1";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = UINT_MAX;
	//printf("%s * %s:\n", s1, s2);
	//bf_print(a);
	//bf_print(b);
	c = bf_mul(a,b);
	//bf_print(c);

	s1 = "9.999 999 999(big)";
	s2 = "2";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = UINT_MAX;
	//printf("%s * %s:\n", s1, s2);
	//bf_print(a);
	//bf_print(b);
	//c = bf_mul(a,b);
	////bf_print(c);

	s1 = "9.999 999 999(small)";
	s2 = "1";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = 0;
	//printf("%s * %s:\n", s1, s2);
	//bf_print(a);
	//bf_print(b);
	c = bf_mul(a,b);
	//bf_print(c);

	s1 = "9.999 999 999(small)";
	s2 = "0.1";
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	a.exp = 0;
	//printf("%s * %s:\n", s1, s2);
	//bf_print(a);
	//bf_print(b);
	//c = bf_mul(a,b);
	////bf_print(c);
	
	//printf("bf_div--------------------------------------------\n");
	s1 = "1.0";
	s2 = "0.5";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1";
	s2 = "2";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1";
	s2 = "3";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1231232";
	s2 = "3";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "0";
	s2 = "3";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);

	s1 = "1";
	s2 = "0";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	//c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	////bf_print(c);

	s1 = "0";
	s2 = "0";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	//c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	////bf_print(c);


	s1 = "2.896878";
	s2 = "7.8";
	//printf("%s / %s:\n", s1, s2);
	a = s_to_bf(s1);
	b = s_to_bf(s2);
	c = bf_div(a,b);
	//bf_print(a);
	//bf_print(b);
	//bf_print(c);
		
	//printf("bf_sqrt--------------------------------------------\n");
	s1 = "2000000";
	//printf("sqrt %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_sqrt(a);
	//bf_print(a);
	//bf_print(b);

	s1 = "3";
	//printf("sqrt %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_sqrt(a);
	//bf_print(a);
	//bf_print(b);

	s1 = "0.00000005";
	//printf("sqrt %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_sqrt(a);
	//bf_print(a);
	//bf_print(b);

	//printf("bf_exp--------------------------------------------\n");
	s1 = "1";
	//printf("exp %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_exp(a);
	//bf_print(a);
	//bf_print(b);
	bf_to_s(b, s3);
	//printf("%s\n", s3);

	s1 = "30000";
	//printf("exp %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_exp(a);
	//bf_print(a);
	//bf_print(b);
	bf_to_s(b, s3);
	//printf("%s\n", s3);

	s1 = "0.00001";
	//printf("exp %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_exp(a);
	//bf_print(a);
	//bf_print(b);
	bf_to_s(b, s3);
	//printf("%s\n", s3);

	//printf("bf_ln--------------------------------------------\n");
	s1 = "1";
	//printf("ln %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_ln(a);
	//bf_print(a);
	//bf_print(b);
	bf_to_s(b, s3);
	//printf("%s\n", s3);

	s1 = "30000";
	//printf("ln %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_ln(a);
	//bf_print(a);
	//bf_print(b);
	bf_to_s(b, s3);
	//printf("%s\n", s3);

	s1 = "0.00001";
	//printf("ln %s:\n", s1);
	a = s_to_bf(s1);
	b = bf_ln(a);
	//bf_print(a);
	//bf_print(b);
	//bf_to_s(b, s3);
	////printf("%s\n", s3);
    
    printf("------------------------------------------------------------\n");
    printf("Ran all functions.\n");
    printf("The functions should be tested at unittests of test_bigfloat.py.\n\n");
    printf("OK\n");
	return 0;
}
