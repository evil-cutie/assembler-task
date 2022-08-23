; file ps.as
; this is a test file

.extern L3
.extern W
MAIN: mov S1.1 W
add r2,STR
LOOP: jmp W 
macro r1
mov S1.2, r3
endmacro
prn #-5
macro r2
sub r1
inc K
endmacro
bne L3
END: hlt 
STR: .string "abcdef
LENGTH: .data 6,-9,15
K: .data 22
S1: .struct 8, "ab"