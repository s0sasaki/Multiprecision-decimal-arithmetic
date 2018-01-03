
(define a1 4)
(define f1
	(lambda (n)
		(* n 4)))
(python)

a1 =  fetch_scheme("a1")
f1 =  fetch_scheme("f1")
assert(a1==4)
assert(f1(3)==12)

a2 = 4
def f2(n):
	return n*4

load_to_scheme(a2, "a2")
load_to_scheme(f2, "f2")

scheme()

(assertEqual a2 4)
(assertEqual (f2 2) 8)



