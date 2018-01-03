
(print "define_a_and_f_at_scheme")
(define a 5)
(define f
    (lambda (n)
        (* n n)))
(print a)
(print (f 9))
(print "")
(python)

print("use a and f at python")
print(fetch_scheme("a"))
print(fetch_scheme("f")(9))
print("")
print("define and load b and g at python")
b = 5
def g(n):
    m = n*n - 3
    return m
print(b)
print(g(3))
print("")
load_to_scheme(g, "g")
load_to_scheme(b, "b")
scheme()

(print "use_b_and_g_at_scheme")
(print b)
(print (g 3))


