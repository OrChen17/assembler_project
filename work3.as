.entry K
.entry LOOP
.extern W
.extern R
MAIN: mov r0,r1
      cmp #-5,K
      sub S.2, W
      not K
LOOP:   jmp R
	inc r3
	prn K	
	jsr S.2
	cmp #2,S.1
	get W
END: hlt
K: .data -1
S: .struct 2,"ab"
