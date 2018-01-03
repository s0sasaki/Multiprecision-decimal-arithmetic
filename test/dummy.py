
a0 = 3
def f0(n):
    return n*3

load_to_scheme(a0, "a0")
load_to_scheme(f0, "f0")

assert(fetch_scheme("a1")==4)
assert(fetch_scheme("f1")(5)==20)
