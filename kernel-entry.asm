[bits 32]
[extern main] ; load kernel main function
call main
jmp $ ; loop