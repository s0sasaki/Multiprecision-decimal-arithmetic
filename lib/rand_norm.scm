
(define rand_norm
    (lambda ()
        (begin 
            (define rand_s
                (lambda ()
                     (- (* 2 (rand)) 1)))
            (define u (rand_s))
            (define v (rand_s))
            (define w 
                (+ (* u u) (* v v)))
            (if (< w 1)
                (* u
                   (sqrt (/ (* -2 (ln w))
                            w)))
                (rand_norm)))))

