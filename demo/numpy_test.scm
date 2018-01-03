
(define f3
	(lambda (n)
		(* n n)))

(python)

import numpy

load_to_scheme(numpy.ones,  "np.ones")
load_to_scheme(numpy.array, "np.array")

scheme()

(print (np.ones (int 6)))
(define a 
	(* (int 3)
		(+ (int 2)
			(np.ones (int 7)))))
(print (* a a))

(define ar
	(np.array
		(list (int 3) (int 4) (int 5) (int 6))))
(print ar)
(print (f3 ar))

(import_scheme  "scipy")

