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
