#lang racket


; átomo pode ser um número, um símbolo ou uma string
(define (atom? x)
  (or (number? x)
      (or (symbol? x)
          (string? x))))

; variável livre tem a forma (? v)
(define (var? e)
  (and (pair? e) (eq? (car e) '?)) )

; átomo e constante são a mesma coisa
(define constant? atom?)
(define =_constant? equal?)

; frame é o conjunto de associações (environment)
; é uma lista de pares (var valor)
(define make-binding cons)
(define binding-in-frame assoc) ; assoc busca um elemento em uma lista de pares e o retorna
(define binding-value cdr)      ; valor do par
(define (extend var val frame)
  (cons (make-binding var val) frame))

;unificação
; unifica p1 com p2  dadas as associações em frame
(define (unify p1 p2 frame)
  (cond
    ((eq? frame #f) #f) ;[1] precisamos de um frame
    ((var? p1) (unify_var p1 p2 frame)) ;[2] se p1 é livre, unifica com p2
    ((var? p2) (unify_var p2 p1 frame)) ;[3] se p2 é livre, unifica com p1
    ((constant? p1) ;[4] se forem constantes, vale o frame, falso caso contrário
     (if (constant? p2)
         (if (=_constant? p1 p2)
             frame
             #f)
         #f))
    ((constant? p2) #f) ;sabemos que p1 não é constante
    ((null? p1)(if (null? p2) frame #f)) ; se ambos nulos, ok
    (else ;[6] operador
     ;(begin (display "p1:")(display p1)(display "p2:")(display p1) (newline)
     (unify (cdr p1) ;[6.1] unifica valores
            (cdr p2)
            (unify ;[6.2] adiciona a unificação dos nomes no frame, se possível
             (car p1)
             (car p2) frame)))));)


; unificação de variável com valor
(define (unify_var var val frame)
  (if (equal? var val) ;[1] já é o valor
      frame ;[1.1]
      ; caso contrário
      (let ((value-cell (binding-in-frame var frame))) ; valor da variável
        (if (not value-cell) ;não definida no frame
            (if (freefor? var val frame) ;[3.1] variavel está livre?
                (extend var val frame) ;[3.2] unifico com o valor
                #f) ;[3.3] redefinição, não aceita
            ; definida, unifica
            (unify (binding-value value-cell) ;[4]
                   val
                   frame)))))

; verifica se a var está em exp e atualiza
(define (freefor? var exp frame)
  (letrec (
           (freewalk (lambda (e)
                       (cond
                         ((constant? e) #t) ;[1] expressão constante, ok
                         ((empty? e) #t) ; expressão vazia
                         ((var? e) ;[2] expressão é variável livre
                          (if (equal? var e) ; são a mesma
                              #f ;[2.1] não é possível resolver
                              (let ((b (binding-in-frame e frame))) ;[2.2] b é o valor de e
                                (if (not b) ; se e não estiver no frame
                                    #t ;[2.3] ok, variável livre
                                    (freewalk (binding-value b)))))) ;[2.4] b existe, avançamos recursivamente
                         ( (freewalk (car e)) (freewalk (cdr e))) ;[3] expressão composta, avalia por partes
                         (else #f)) ;[4]
                       ) ;endlambda
                     ) ; end freewalk binding
           ) ;end letrec bindings
    (freewalk exp)
    ) ;end letrec
  )


;Exemplos
 (freefor? '(? x) '(f (? x)) '()) ;#f
 (unify 'Liz 'Phil '()) ; #f
 (unify '(+ a b) '(+ a b) '()) ; '()
 (unify '(+ a 2) '(+ a b) '()); #f
 (unify '(+ (? a) 4) '(+ b 4) '()) ;'(((? a) . b))
 (unify '(+ (? a) (? a)) '(+ b b) '()) ;'(((? a) . b))
 (unify '(+ (? a) (? a)) '(+ 4 3) '()); #f
 (unify '(+ (? a) 7) '(+ 4 (? b)) '()) ;'(((? b) . 7) ((? a) . 4))
 (unify '(+ (? a) 4 ) '(+ 5 (? b)) '()); '(((? b) . 4) ((? a) . 5))