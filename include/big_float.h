#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define POSITIVE 1
#define NEGATIVE 0

#ifndef CONTROL_FOR_CFFI
#define	NDIGIT	20
#define Q	10000
#define N_ITER_FACTOR 1
#define STR_SIZE_MAX 10000
#endif

typedef struct {
	bool         iszero;
	int          sign;
	unsigned int exp;
	int          frac[NDIGIT];
} big_float;

bool detect_overflow_add_uint(unsigned int, unsigned int);
bool detect_underflow_sub_uint(unsigned int, unsigned int);
void sigfpe_error(void);
void overflow_error(void);
void underflow_error(void);
void zerodiv_error(void);
unsigned int add_uint(unsigned int, unsigned int);
unsigned int sub_uint(unsigned int, unsigned int);
big_float norm_carryup(big_float, int);
big_float s_to_bf(char*);
big_float i_to_bf(unsigned int);
int bf_cmp_abs(big_float, big_float);
void bf_print(big_float);
void bf_to_s(big_float, char*);

bool bf_iszero(big_float);
big_float bf_zero(void);
big_float bf_add(big_float, big_float);
big_float bf_add_abs(big_float, big_float);
big_float bf_sub(big_float, big_float);
big_float bf_sub_abs(big_float, big_float);
big_float bf_mul(big_float, big_float);
big_float bf_mul_abs(big_float, big_float);
big_float bf_div(big_float, big_float); 
big_float bf_div_abs(big_float, big_float); 

big_float bf_sqrt(big_float);
big_float bf_exp(big_float);
big_float bf_ln(big_float);

int seed[NDIGIT];
void bf_rand_linear_congruential_generator(int*);
void bf_rand_seed_set(int*, int);
void bf_rand_seed_set_static(int);
big_float bf_rand(int*);
big_float bf_rand_static(void);

int  bf_cmp_if(big_float *, big_float *);
void bf_add_if(big_float *, big_float *, big_float *);
void bf_sub_if(big_float *, big_float *, big_float *);
void bf_mul_if(big_float *, big_float *, big_float *);
void bf_div_if(big_float *, big_float *, big_float *);
void bf_exp_if(big_float *, big_float *);
void bf_sqrt_if(big_float *, big_float *);
void bf_ln_if(big_float *, big_float *);
void s_to_bf_if(big_float *, char *);
void bf_rand_static_if(big_float *);

