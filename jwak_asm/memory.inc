memory_init:
    push rbp
    mov rbp, rsp

    call [GetProcessHeap]
    mov [_heap_handle], rax

    pop rbp
    ret

m_alloc:
    ; rcx - size
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 4

    mov r8, rcx
    xor rdx, rdx
    mov rcx, [_heap_handle]
    call [HeapAlloc]

    add rsp, 8 * 4
    pop rbp
    ret

m_free:
    ; rcx - addr
    push rbp
    mov rbp, rsp
    sub rsp, 8 * 4

    mov r8, rcx
    xor rdx, rdx
    mov rcx, [_heap_handle]
    call [HeapFree]

    add rsp, 8 * 4
    pop rbp
    ret
