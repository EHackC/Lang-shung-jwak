format PE64 console
entry start

section ".text" code readable executable
    start:
        sub rsp, 8 * 5

        mov ecx, 0
        call [ExitProcess]

section ".data" data readable writeable
    _utf8 dd

section ".idata" import data readable writeable
    dd 0, 0, 0, RVA kernel_name, RVA kernel_table
    dd 0, 0, 0, 0, 0

    kernel_name db "KERNEL32.DLL", 0
    kernel_table:
        ExitProcess dq RVA _ExitProcess
        dq 0

    _ExitProcess dw 0
        db "ExitProcess", 0
