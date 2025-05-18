format PE64 console
entry start

include "../utf8.inc"
include "../lexer.inc"

section ".text" code readable executable
    start:
        sub rsp, 8 * 6 + 8

        call [GetProcessHeap]
        mov [_heap_handle], rax

        ; 파일 열기
        mov rcx, _file_name
        mov edx, 0x80000000
        mov r8d, 0x1
        xor r9d, r9d
        mov qword [rsp + 8 * 4], 0x3
        mov dword [rsp + 8 * 5], 0x80
        mov dword [rsp + 8 * 6], 0
        call [CreateFile]
        mov [_file_handle], rax

        ; 파일 크기 가져오기
        mov ecx, eax
        mov edx, _file_size
        call [GetFileSizeEx]

        ; 파일 공간 할당
        mov rcx, [_heap_handle]
        mov rdx, 0
        mov r8, rax
        call [HeapAlloc]
        mov [_file_content_addr], rax

        ; 파일 읽기
        mov rcx, [_file_handle]
        mov rdx, [_file_content_addr]
        mov r8, [_file_size]
        mov r9, 0
        mov qword [rsp + 8 * 4], 0
        call [ReadFile]

        ; 다코딩된 글자 수 구하기
        mov rcx, [_file_content_addr]
        mov rdx, [_file_size]
        mov r8, _text_length
        call get_utf8_text_length

        ; 디코딩할 텍스트 크기만큼 공간 할당
        mov rax, [_text_length]
        shl rax, 2
        mov rcx, [_heap_handle]
        mov rdx, 0
        mov r8, rax
        call [HeapAlloc]
        mov [_output_addr], rax

        ; 디코딩
        mov rcx, [_file_content_addr]
        mov rdx, [_file_size]
        mov r8, [_output_addr]
        call decode_utf8_list

        ; 메모리 해제
        mov rcx, [_heap_handle]
        mov rdx, 0
        mov r8, [_output_addr]
        call [HeapFree]

        mov rcx, [_heap_handle]
        mov rdx, 0
        mov r8, [_file_content_addr]
        call [HeapFree]

        mov ecx, 0
        call [ExitProcess]

section ".data" data readable writeable
    _file_name db "test/lexer.jwak", 0
    _file_handle dq 0
    _file_content_addr dq 0
    _file_size dq 0
    _text_length dq 0
    _output_addr dq 0
    _heap_handle dq 0

section ".idata" import data readable writeable
    dd 0, 0, 0, RVA kernel_name, RVA kernel_table
    dd 0, 0, 0, 0, 0

    kernel_name db "KERNEL32.DLL", 0
    kernel_table:
        ExitProcess dq RVA _ExitProcess
        GetProcessHeap dq RVA _GetProcessHeap
        HeapAlloc dq RVA _HeapAlloc
        HeapFree dq RVA _HeapFree
        CreateFile dq RVA _CreateFileA
        ReadFile dq RVA _ReadFile
        GetFileSizeEx dq RVA _GetFileSizeEx
        dq 0

    _ExitProcess dw 0
        db "ExitProcess", 0
    _GetProcessHeap dw 0
        db "GetProcessHeap", 0
    _HeapAlloc dw 0
        db "HeapAlloc", 0
    _HeapFree dw 0
        db "HeapFree", 0
    _CreateFileA dw 0
        db "CreateFileA", 0
    _ReadFile dw 0
        db "ReadFile", 0
    _GetFileSizeEx dw 0
         db "GetFileSizeEx", 0
