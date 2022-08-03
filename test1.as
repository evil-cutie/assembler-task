MAIN: mov S1.1 ,LENGTH
add r2,STR
LOOP: jmp END
macro r1
inc K
mov S1.2 ,r3
endmacro
prn #-5
sub r1, r4
m1
bne LOOP
macro bla
this is bla macro
endmacro
END: 
bla
STR: .string "abcdef"
macro m2
this is m2 macro
endmacro
LENGTH: .data 6,-9,15
K: .data 22
bla
m2
S1: .struct 8, "ab"