(source_scheme "lib/rand_student.scm")

(define rep
    (lambda (i n) 
       (if (< i n)
           (begin 
               (print (rand_student 3))
               (rep (+ i 1) n))
           0)))

(rand_seed 20)

(rep 0 100) 
