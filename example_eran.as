;HELLO: lea
sme "something,"
macro m1
 inc r2
 mov A,r1
endmacro
add #1 , r4
;lea #1, r2
m1
add #1,     #2
macro m2
 sub 1,1
 mul 5,4
endmacro
;mul     r2, #31
sub r5, r7
;add r0, S5
add r3, S4.1
m1
add S1.1,HELLO.2
;LABEL: ABC
m2
mov S1,HELLO.2
add S1, #123