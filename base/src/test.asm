
    bits 16
    cpu 286

segment code

global test_function_
test_function_:
    pusha
        xor ax, ax
        int 0x16
    popa
    ret

