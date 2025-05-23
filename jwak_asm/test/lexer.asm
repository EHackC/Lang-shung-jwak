format PE64 console
entry start

section ".text" code readable executable
    include "../utf8.inc"
    include "../lexer.inc"
    include "../array.inc"
    include "../memory.inc"
    include "../file.inc"

    start:
        sub rsp, 8 * 6 + 8

        call memory_init

        ; 파일 열기
        mov rcx, _file_name
        call f_open
        mov [_file_handle], rax

        ; 파일 크기 가져오기
        mov ecx, eax
        mov edx, _file_size
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

        ; 다코딩된 글자 수 구하기
        mov rcx, [_file_content_addr]
        mov rdx, [_file_size]
        mov r8, _text_length
        call get_utf8_text_length

        ; 디코딩할 텍스트 크기만큼 공간 할당
        mov rcx, [_text_length]
        shl rcx, 2
        call m_alloc
        mov [_output_addr], rax

        ; 디코딩
        mov rcx, [_file_content_addr]
        mov rdx, [_file_size]
        mov r8, [_output_addr]
        call decode_utf8_list

        ; 렉싱
        mov rcx, [_output_addr]
        mov rdx, [_text_length]
        call lexing

        ; 파일 닫기
        mov rcx, [_file_handle]
        call f_close

        ; 메모리 해제
        mov rcx, [_output_addr]
        call m_free

        mov rcx, [_file_content_addr]
        call m_free

        mov ecx, 0
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
