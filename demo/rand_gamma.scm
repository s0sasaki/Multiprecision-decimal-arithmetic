
(source_scheme "lib/rand_gamma.scm")

(define rep
    (lambda (i n) 
       (if (< i n)
           (begin 
               (print (rand_gamma 2 1))
               (rep (+ i 1) n))
           0)))

(rand_seed 20)

(rep 0 100) 

