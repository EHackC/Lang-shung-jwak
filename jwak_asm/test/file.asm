format PE64 console
entry start

section ".text" code readable executable
    include "../memory.inc"
    include "../file.inc"

    start:
        sub rsp, 8 * 4 + 8

        call memory_init

        ; 파일 열기
        mov rcx, _file_name
        call f_open
        mov [_file_handle], rax

        ; 파일 크기 가져오기
        mov rcx, rax
        mov rdx, _file_size
        call f_get_file_size

        ; 파일 공간 할당
        mov rcx, rax
        call m_alloc
        mov [_file_content_addr], rax

        ; 파일 읽기
        mov rcx, [_file_handle]
        mov rdx, [_file_content_addr]
        mov r8, [_file_size]
        call f_read

        ; 파일 닫기
        mov rcx, [_file_handle]
        call f_close

        ; 메모리 해제
        mov rcx, [_file_content_addr]
        call m_free

        xor rax, rax
        call [ExitProcess]

section ".data" data readable writeable
    _file_name db "test/lexer.jwak", 0
    _file_handle dq 0
    _file_content_addr dq 0
    _file_size dq 0
    _text_length dq 0
    _output_addr dq 0
    include "../data.inc"

section ".idata" import data readable writeable
    include "../import.inc"
