(list "Kolmogorov-Smirnov_test")
(list "ref:Numerical_Recipes_in_C")

(define probks
	(lambda (alam)
		(begin
			(define EPS1 0.00001)
			(define EPS2 0.0000000001)
			(define a2 (* -2 (* alam alam)))
			(define f
				(lambda (fac sum termbf i)
					(begin
						(define term (* fac (exp (* a2 (* i i)))))
						(if (< i 100) 
							(if (+  (<= (abs term) (* EPS1 termbf)) 
									(<= (abs term) (* EPS2 sum)))
								sum
								(f 
									(* -1 fac)
									(+ sum term)
									(abs term)
									(+ i 1)))
							1))))
			(f 2 0 0 1))))

(define kstest_one
	(lambda (data n cdf)
		(begin
			(define data_sorted (sort data))
			(define maxd 0)
			(define f
				(lambda (shortdata fo i)
					(begin 
						(define ff (cdf (car shortdata)))
						(define fn (/ i n))
						(define dt	(max (abs (- fo ff ))
										 (abs (- fn ff ))))
						(if (> dt maxd) 
							(set! maxd dt)
							0)
						(if (>= i n)
							0
							(f 
								(cdr shortdata)
								fn
								(+ i 1))))))
			(f data_sorted 0 1)
			(define en (sqrt n))
			(define a 
				(*	maxd
					(+ en (+ 0.12 (/ 0.11 en)))))
			(probks a))))

(python)

"""
(define cdf
	(lambda (x) x))

(print (kstest_one	(list 0.08 0.02 0.04 0.05 0.06) 5 cdf))	
(print (kstest_one	(list 0.8 0.02 0.4 0.5 0.06) 5 cdf))	
(print (kstest_one	(list 0.8 0.6 0.4 0.5 0.06) 5 cdf))	
(print (kstest_one	(list 0.8 0.2 0.4 0.5 0.6) 5 cdf))	
(print (kstest_one	(list 0.8 0.8 0.4 0.9 0.6) 5 cdf))	
"""
