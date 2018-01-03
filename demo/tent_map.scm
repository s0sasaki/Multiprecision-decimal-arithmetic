(define tent_func
    (lambda (x)
        (if (< x 0.5)
            (* x 2)
            (- 2 (* x 2)))))
(define extend
    (lambda (L)
        (append L (list (tent_func (nth -1 L))))))
(define f
    (lambda (L n)
        (if (> (length L) n)
            L
            (f (extend L) n))))
(plot (f (list 0.1) 100))

