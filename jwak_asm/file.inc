f_open:
    ; rcx - file name
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 8

    mov rdx, 0x80000000
    mov r8, 0x1
    xor r9, r9
    mov dword [rsp + 8 * 4], 0x3
    mov dword [rsp + 8 * 5], 0x80
    mov dword [rsp + 8 * 6], 0
    call [CreateFile]

    add rsp, 8 * 8
    pop rbp
    ret

f_close:
    ; rcx - file handle
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 4

    call [CloseHandle]

    add rsp, 8 * 4
    pop rbp
    ret

f_read:
    ; rcx - file handle
    ; rdx - file content addr
    ; r8 - file size
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 6

    xor r9, r9
    mov qword [rsp + 8 * 4], 0
    call [ReadFile]

    add rsp, 8 * 6
    pop rbp
    ret

f_get_file_size:
    ; rcx - file handle
    ; rdx - file size addr
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 4

    call [GetFileSizeEx]

    add rsp, 8 * 4
    pop rbp
    ret
