
(source_scheme "lib/rand_norm.scm")
(source_scheme "lib/rand_gamma.scm")

(list "note:_r_must_be_greater_than_2.")
(define rand_student
	(lambda (r)
		(begin
			(define rdiv2 (/ r 2))
			(define d     (sqrt rdiv2))
			(/ (* d (rand_norm))
			   (sqrt (rand_gamma rdiv2 1))))))
(python)
"""
(rand_seed 100)
(print (rand_student 3))
(print (rand_student 3))
(print (rand_student 3))
(print (rand_student 3))
(print (rand_student 3))
"""

