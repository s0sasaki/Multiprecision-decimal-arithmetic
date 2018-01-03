
(define n 1)
(rand_seed 1)
(define rand_series 
    (lambda (n)
        (if (< n 1)
            0
            (begin 
                (print (rand))
                (rand_series (- n 1))))))

(list "note:_the_num_of_recursive_is_limited.")

(rand_series 100)

