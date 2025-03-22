decode_utf8_list:
    ; rcx - file(addr) -> r10
    ; rdx - file size
    ; r8 - result(addr)

    mov r10, rcx

    .decode_utf8_loop:
        movbe eax, dword [r10]
        mov ebx, eax
        mov ecx, eax
        sar ecx, 1
        and ebx, ecx
        sar ecx, 1
        and ebx, ecx
        shr ebx, 28
        or ebx, 0x8 ; 0b1000
        popcnt ecx, ebx
        sub rdx, rcx
        add r10, rcx
        shl eax, cl
        shr eax, cl
        not ebx
        and ebx, 0x7 ; 0b111
        popcnt ecx, ebx
        shl ecx, 3
        shr eax, cl

        mov ebx, eax
        and ebx, 0x3F
        shr eax, 8
        shl eax, 6
        or eax, ebx

        mov ebx, eax
        and ebx, 0xFFF
        shr eax, 14
        shl eax, 12
        or eax, ebx

        mov ebx, eax
        and ebx, 0x3FFFF
        shr eax, 20
        shl eax, 18
        or eax, ebx

        mov [r8], eax
        add r8, 4

        test rdx, rdx
        jne .decode_utf8_loop

    ret

get_utf8_text_length:
    ; rcx - file(addr) -> r10
    ; rdx - file size
    ; r8 - result(addr)

    mov r10, rcx

    .utf8_length_loop:
        movbe eax, dword [r10]
        mov ebx, eax
        mov ecx, eax
        sar ecx, 1
        and ebx, ecx
        sar ecx, 1
        and ebx, ecx
        shr ebx, 28
        or ebx, 0x8 ; 0b1000
        popcnt ecx, ebx
        sub rdx, rcx
        add r10, rcx

        add qword [r8], 1

        test rdx, rdx
        jne .utf8_length_loop

    ret
