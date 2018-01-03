(define f 
    (lambda (a b)
        (if (= a (+ a b))
            0
            (+ (f a (/ b 10))
               1))))

(print (int (f 1 1)))

