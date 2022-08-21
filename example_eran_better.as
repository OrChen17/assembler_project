macro m1
 ;add     r2, #31
 add r5, r7
 ;add r0, S5
 ;add r3, S4.1
endmacro
;HELLO: lea
;sme "something," , 

add #1  , r4
;lea #1, r2
;add #1,     #2
;add #-10, S3
;add #-1, S3.2

m1

;add S1.1,HELLO.2
;add S1.1, #123
;add S1.1, r3
;add S1.1, HELLO

macro m2
 mov r1, r2
 add r2, r3
 sub r4, r5
endmacro

;add S1,HELLO.2
;add S1, #123
;add S1, r3
;add S1, HELLO

m2

;sme
;Hello: jsr,    something