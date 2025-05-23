format PE64 console
entry start

section ".text" code readable executable
    include "../memory.inc"

    start:
        sub rsp, 8 * 4 + 8

        call memory_init

        mov rcx, 0xFF + 1
        call m_alloc

        mov rcx, 0xFF
        .loop:
            mov [rax + rcx], cl
            sub rcx, 1
            test rcx, rcx
            jne .loop
        mov byte [rax], 0

        mov rcx, rax
        call m_free

        xor rax, rax
        call [ExitProcess]

section ".data" data readable writeable
    include "../data.inc"

section ".idata" import data readable writeable
    include "../import.inc"
