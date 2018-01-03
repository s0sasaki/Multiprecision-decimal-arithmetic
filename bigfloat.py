from cffi import FFI

NDIGIT        = 50
Q             = 10000
N_ITER_FACTOR = 1
STR_SIZE_MAX  = 1000 

def set_csource_and_compile():

    # These are what we can use in _big_float module.
    _CDEF = r"""
    typedef struct {
    	bool         iszero;
    	int	         sign;
    	unsigned int exp;
    	int          frac["""+str(NDIGIT)+r"""];
    } big_float;
    
    int  bf_cmp_if(big_float *a,   big_float *b);
    void bf_add_if(big_float *ans, big_float *a, big_float *b);
    void bf_sub_if(big_float *ans, big_float *a, big_float *b);
    void bf_mul_if(big_float *ans, big_float *a, big_float *b);
    void bf_div_if(big_float *ans, big_float *a, big_float *b);
    void bf_exp_if(big_float *ans, big_float *a);
    void bf_sqrt_if(big_float *ans, big_float *a);
    void bf_ln_if(big_float *ans, big_float *a);
    void s_to_bf_if(big_float *ans, char *s);
    void bf_to_s_if(char *s, big_float *a);
    void bf_rand_static_if(big_float *a);
    void bf_rand_seed_set_static(int n);
    """
    
    # These are compiled to make _big_float module.
    _C = r"""
    #define	NDIGIT          """+str(NDIGIT       )+r"""
    #define Q               """+str(Q            )+r"""
    #define N_ITER_FACTOR 	"""+str(N_ITER_FACTOR)+r"""
    #define STR_SIZE_MAX 	"""+str(STR_SIZE_MAX )+r"""
    
    #define CONTROL_FOR_CFFI
    #include "include/big_float.h"
    #include "src/bf_util.c"
    #include "src/bf_add.c"
    #include "src/bf_cmp.c"
    #include "src/bf_sub.c"
    #include "src/bf_mul.c"
    #include "src/bf_div.c"
    #include "src/bf_sqrt.c"
    #include "src/bf_io.c"
    #include "src/bf_exp.c"
    #include "src/bf_ln.c"
    #include "src/bf_rand.c"
    #include "src/bf_if.c"
    """
    
    ffi = FFI()
    ffi.cdef(_CDEF)
    ffi.set_source("_big_float",_C)
    ffi.compile(verbose = False)

#-----------------------------------------

set_csource_and_compile()
from _big_float import ffi, lib

class Number(object):
    def __init__(self, s="0"):
        #try:
        #    self.cdata = ffi.new("big_float[]", [(1, 1, Q, [0 for i in range(NDIGIT)])])
        #except:
        #    raise ValueError 
        self.cdata = ffi.new("big_float[]", [(1, 1, Q, [0 for i in range(NDIGIT)])])
        if s != "0":
            try:
                lib.s_to_bf_if(self.cdata, s.encode("utf-8"))
            except:
                raise
 
    def get_iszero(self):
        return self.cdata[0].iszero
    def get_sign(self):
        return self.cdata[0].sign
    def get_exp(self):
        return self.cdata[0].exp
    def get_frac(self):
        return [self.cdata[0].frac[i] for i in range(NDIGIT)]
    def set_iszero(self, b):
        self.cdata[0].iszero = b
    def set_sign(self, i):
        self.cdata[0].sign = i
    def set_exp(self, u):
        self.cdata[0].exp = u
    def set_frac(self, v):
        self.cdata[0].frac = [v[i] for i in range(NDIGIT)]

    def __str__(self):
        #s = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx".encode()     #tmp
        s = ""
        for i in range(STR_SIZE_MAX):
            s += "x"
        s = s.encode()
        lib.bf_to_s_if(s, self.cdata)
        s = s.decode()
        s = s.replace("\x00", "")
        s = s.replace("x", "")
        return s

    def __add__(self, other):
        c = Number()
        if not isinstance(other, Number):
            other = Number(str(other))
        lib.bf_add_if(c.cdata, self.cdata, other.cdata)
        return c
    def __sub__(self, other):
        c = Number()
        if not isinstance(other, Number):
            other = Number(str(other))
        lib.bf_sub_if(c.cdata, self.cdata, other.cdata)
        return c
    def __mul__(self, other):
        c = Number()
        if not isinstance(other, Number):
            other = Number(str(other))
        lib.bf_mul_if(c.cdata, self.cdata, other.cdata)
        return c
    def __truediv__(self, other):
        c = Number()
        if not isinstance(other, Number):
            other = Number(str(other))
        lib.bf_div_if(c.cdata, self.cdata, other.cdata)
        return c
    __radd__ = __add__
    __rmul__ = __mul__
    def __rsub__(self, other):
        return Number(str(other)) - self
    def __rtruediv__(self, other):
        return Number(str(other)) / self


    def __eq__(self, other):
        if not isinstance(other, Number):
            other = Number(str(other))
        if lib.bf_cmp_if(self.cdata, other.cdata) == 0:
            return True
        else:
            return False
    def __gt__(self, other):
        if not isinstance(other, Number):
            other = Number(str(other))
        if lib.bf_cmp_if(self.cdata, other.cdata) == 1:
            return True
        else:
            return False
    def __lt__(self, other):
        if not isinstance(other, Number):
            other = Number(str(other))
        if lib.bf_cmp_if(self.cdata, other.cdata) == -1:
            return True
        else:
            return False
    def __ne__(self, other):
        return not self.__eq__(other)
    def __ge__(self, other):
        return not self.__lt__(other)
    def __le__(self, other):
        return not self.__gt__(other)

    def __float__(self):
        b = 0.0
        for i in range(NDIGIT):
            b += self.get_frac()[i]*(10**(self.get_exp()-Q-i))
        if self.get_sign() == 0:
            b *= -1
        return b

    def __int__(self):
        return int(float(self))

def exp(a):
    b = Number()
    if not isinstance(a, Number):
        a = Number(str(a))
    lib.bf_exp_if(b.cdata, a.cdata)
    return b

def ln(a):
    b = Number()
    if not isinstance(a, Number):
        a = Number(str(a))
    lib.bf_ln_if(b.cdata, a.cdata)
    return b 

def sqrt(a):
    b = Number()
    if not isinstance(a, Number):
        a = Number(str(a))
    lib.bf_sqrt_if(b.cdata, a.cdata)
    return b

def rand_seed(a=Number()):
    n = int(float(a))
    lib.bf_rand_seed_set_static(n)

def rand():
    b = Number()
    lib.bf_rand_static_if(b.cdata)
    return b

