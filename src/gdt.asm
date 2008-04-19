global init_gdt

bits 32
align 32

init_gdt:
	lgdt [gdtr]

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov gs,ax
	mov fs,ax
	mov ss,ax
	
	jmp 0x08:gdt_return

gdt_return:
	ret

section .data

align 8

gdt_begin:
	dd 0
	dd 0

	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0

	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
gdt_end:

gdtr:
	dw gdt_end-gdt_begin-1
	dd gdt_begin
