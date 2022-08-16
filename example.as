A1: .data 22
HELLO: lea S4.3, r2
;sme "something," ,

S4: .data 2

mov r2, r6
HELLO2: add r3, r1

S2: hlt

lea S2.1, r2

LABEL: .data 6, -9,15
STR: .string "acvd"
strct8: .struct 8, "xyz"
; .data 3,4,5

.entry STR 

add HELLO1, S5.3

HI: add #4, r1


HLT: hlt

.extern 	K1

add K1.2,H.2
;add S3.2, HELLO

.extern  H
.extern HELLO1
.extern S5	

inc HI

;Hello3: jsr    something