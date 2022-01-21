global load_gdt

; load_gdt - load struct in GDT
; stack: [esp + 4] struct pointer

load_gdt:
    lgdt [esp + 4]       ; get the struct pointer
    ret                  ; return to the calling function
