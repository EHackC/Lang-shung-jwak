decode_utf8_list:
    ; rcx - file(addr) -> r10
    ; rdx - file size
    ; r8 - result(addr)
    push rbp
    mov rbp, rsp

    mov r10, rcx

    ; rdx는 루프를 끝내는 조건으로 사용됨
    .decode_utf8_loop:
        ; var = 1110 ????
        ; 위에꺼에서 맨 왼쪽에 있는 1의 개수를 구해야 됨
        movbe eax, dword [r10]
        mov ebx, eax
        mov ecx, eax
        ; 10??로 시작하는 경우를 대비해서 ??부분을 00으로 바꾸는 코드(var & (var >> 1) | 여기서 >>는 부호 있는 쉬프트 | 두 번 반복)
        sar ecx, 1
        and ebx, ecx
        sar ecx, 1
        and ebx, ecx
        shr ebx, 28 ; 오른쪽으로 쉬프트 해서 맨 왼쪽 4비트만 남겨둠
        ; utf8은 아스키코드와의 호환을 위해 0000으로 시작하는 경우가 1바이트 문자로 지정했으니 or로 맨 앞에 1 추가
        or ebx, 0x8 ; 0b1000
        popcnt ecx, ebx ; popcnt -> 비트 1의 개수를 구하는 명령어
        sub rdx, rcx
        add r10, rcx
        ; 맨 왼쪽에 있는 1??0 <- 이거 제거
        shl eax, cl
        shr eax, cl
        ; 쉬프트를 통해 문자 하나에 해당하는 바이트가 아닌 부분 제거
        not ebx
        and ebx, 0x7 ; 0b111
        popcnt ecx, ebx
        shl ecx, 3
        shr eax, cl

        ; ???? ???? 10?? ???? 10?? ???? 10?? ????
        ; 여기서 10에 해당되는 부분 제거
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

        ; 값 수정 및 rdx가 0이 아닌 경우 반복
        mov [r8], eax
        add r8, 4

        test rdx, rdx
        jne .decode_utf8_loop

    pop rbp
    ret

get_utf8_text_length:
    ; rcx - file(addr) -> r10
    ; rdx - file size
    ; r8 - result(addr)
    push rbp
    mov rbp, rsp

    mov r10, rcx

    .utf8_length_loop:
        ; decode_utf8_list 함수에서 바이트 수 세는 코드 그대로 가져옴
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

    pop rbp
    ret
