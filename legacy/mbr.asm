[bits 16]
[org 0x7c00]

jmp enter32


loadSecond:
mov ax,0
mov es,ax
mov ah,0x02
mov  al, 4
mov  bx, 0x7E00
mov  cx, 0x0002
mov  dl, byte [bootdrive]
xor  dh, dh
int 13h
jc .error
ret
.error:
mov byte [error],ah
ret

code16:
mov ax,0
mov ds,ax
mov fs,ax
mov es,ax
mov ss,ax

enter32:
mov byte [bootdrive],dl
mov al,0x03
mov ah,0 
int 0x10
mov ax,2401h  
int 15h
call loadSecond
cli
lgdt [gdtr]
mov eax,cr0
or al,1
mov cr0,eax
mov ax,dataseg
mov ds,ax
mov fs,ax
mov es,ax
mov ss,ax
jmp codeseg:main32

[bits 32]
main32:
mov esp,0x00000500
cmp byte [error],0
jne .errno
mov edi,0
mov edi,enter16
push edi
call 0x00007E00
hlt
.errno:
mov al,byte [error]
add al,48
or ax,0x0f << 8
mov word [0xb8000],ax
hlt

print_num:
mov ebx,10
.loop:
mov edx,0
mov ecx,10
div ecx
add edx,48
mov byte [cache+ebx],dl
dec ebx
cmp eax,0
jne .loop
mov esi,cache
add esi,ebx
mov ecx,10
sub ecx,ebx
call print_string
ret

print_string:
mov edi,0
mov ebx,dword [index]
.loop:
lodsb
or ax, 0x0f << 8
mov word [0xb8000+ebx],ax
add ebx,2
inc edi
cmp edi,ecx
jl .loop
mov dword [index],ebx
ret

enter16:
mov eax,dataseg16
mov ds,eax
mov fs,eax
mov es,eax
mov ss,eax
lgdt [gdtr16]
jmp 0:code16

bootdrive db 0
error db 0
index dd 0
message: db "Test msg"
failed_load: db "Failed to load second stage:"
cache: times 10 db 0
max_cylinders dw 0 
max_heads dw 0
max_sectors dw 0


gdtr:
dw gdt32_end-gdt32 - 1
dq gdt32

gdt32:
.null_seg:dq 0 ;zero entry
.codeseg: dq 0x00cf9a000000ffff
.dseg: dq 0x00cf93000000ffff
gdt32_end:

codeseg equ gdt32.codeseg - gdt32
dataseg equ gdt32.dseg - gdt32

gdtr16:
dw gdt32_end-gdt32 - 1
dq gdt32

gdt16:
.null_seg:dq 0 ;zero entry
.codeseg: dq 0x00009a000000ffff
.dseg: dq 0x000093000000ffff
gdt16_end:

codeseg16 equ gdt16.codeseg - gdt16
dataseg16 equ gdt16.dseg - gdt16

times 510-($-$$) db 0
dw 0xaa55 ;bootable device signature
