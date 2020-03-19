; p6.scm
;
;Program #6
;Recursive Functions for odds, evenrev, penultimate and palindrome
;CS320-01
;12/11/2019
;@author Christian Cortez II cssc0468
;
;
;
; Edit this file to add your documentation and function definitions.
; Leave the rest of this file unchanged.
; To run this file, you would start scheme at edoras command line prompt:
; scheme --load p6.scm, where the file is in the current directory
; and then in scheme type the load command (from the '%' prompt):
;(load "p6.scm")
;
; Defined LISTS for use with testing your functions.
(DEFINE list0 (LIST 'j 'k 'l 'm 'n 'o 'j) )
(DEFINE list1 (LIST 'a 'b 'c 'd 'e 'f 'g) )
(DEFINE list2 (LIST 's 't 'u 'v 'w 'x 'y 'z) )
(DEFINE list3 (LIST 'j 'k 'l 'm 'l 'k 'j) )
(DEFINE list4 (LIST 'n 'o 'p 'q 'q 'p 'o 'n) )
(DEFINE list5 '((a b) c (d e d) c (a b)) )
(DEFINE list6 '((h i) (j k) l (m n)) ) 
(DEFINE list7 '(f (a b) c (d e d) (b a) f) )
;
; Here is a typical function definition from Sebesta Ch. 15
(DEFINE (adder lis)
        (COND
         ((NULL? lis) 0)
         (ELSE (+ (CAR lis) (adder (CDR lis))))
         ))
; The above five lines are the sort of definition you would need to add to
; this file if asked to define an ADDER function.
; Uncomment and complete the following four definitions. At least have ODDS
; so the program can be tested.

(define (odds lst)
  (cond
    ((not(list? lst)) (display "USAGE: (odds {list}"))
    ((null? lst) '())
    ((null? (cdr lst)) lst)
    (else (cons (ca
                 64
                 r lst) (odds (cddr lst)))))
  )

(define (evenrev lst)
  (cond
    ((not(list? lst)) (display "USAGE: (evenrev {list}"))
    ((null? lst) '())
    ((null? (cdr lst)) lst)
    (else (append (evenrev(cddr lst)) (list(cadr lst)))))

  )

(define (penultimate lst)
  (cond
    ((not(list? lst)) (display "USAGE: (penultimate {list}"))
    ((null? lst) '())
    ((null? (cdr lst)) lst)
    ((null? (cddr lst)) (list(car lst)))
    (else(list(car(penultimate(cdr lst))))))
  )

(define (palindrome lst)
  (cond ((list? lst)
         (cond ((null? lst) #t)
               ((null? (cdr lst)) #t)
               ((equal? (car lst) (rev(car(rev(cdr lst))))) (palindrome(cdr(rev(cdr lst)))))
               (else #f)))
        ((not(list? lst)) (display "USAGE: (penultimate {list}")) )
)

(define (rev lst)
  (cond ((list? lst)
         (cond
           ((null? lst) lst)
           ((null? (cdr lst)) lst)
           (else (append (rev (cdr lst)) (list (car lst)) )) ) )
        (else lst) )
  )
