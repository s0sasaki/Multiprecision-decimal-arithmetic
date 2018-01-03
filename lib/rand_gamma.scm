
(source_scheme "lib/rand_norm.scm")

(list "note:_alpha_must_be_greater_than_1.")
(define rand_gamma
	(lambda (alpha beta)
		(begin
			(define d (- alpha (/ 1 3)))
			(define c (/ 1 (sqrt (* 9 d))))
			(define gen_z 
				(lambda ()
					(begin 
						(define z (rand_norm))
						(define v (+ 1 (* c z)))
						(if (> v 0)
							z
							(gen_z)))))
			(define z (gen_z))
			(define v (+ 1 (* c z)))
			(define w (* v (* v v)))
			(define y (* d w))
			(define u (rand))
			(if (+ 	(<  u 
					  (- 1 (* 0.0331 (* (* z z) (* z z)))))
					(<= (ln u)
					  (+ (/ (* z z) 2) (+ (* d (ln w)) (- d y)))))
				(* beta y)
				(rand_gamma alpha beta)))))

