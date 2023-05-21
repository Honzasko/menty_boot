[bits 16]
[org 0x7c00]

jmp enter32


loadSecond:
xor ax,ax
mov ds,ax
mov ah,42h
mov dl,byte [diskinfo.bootdrive]
mov si,dap
int 13h
jc .error
ret
.error:
mov byte [error],ah
ret

enable_a20:
  mov al, 0xd1 
  out 0x64, al 
  nop         
wait_input:
  in al, 0x64 
  test al, 0x2
  jnz wait_input
  mov al, 0xdf
  out 0x60, al 
  ret      


code16:
mov ax,0
mov ds,ax
mov fs,ax
mov es,ax
mov ss,ax


enter32:
mov byte [diskinfo.bootdrive],dl
mov al,0x03
mov ah,0 
int 0x10
mov ax,2401h  
int 15h
call loadSecond
cli ;enabling a20 line
call enable_a20
lgdt [gdtr] ;entering protected mode
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
mov esp,0x00000500 ;set stack for protected mode
cmp byte [error],0 ;check if there was disk reading error
jne .errno
push diskinfo ;add basic structure for second stage
call 0x00007E00 ;call main function of second stage 
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

;disk address packet
dap:
  .size db 10h
  .unused db 0
  .sectors_to_read dw 6
  .segment dw 0
  .offset  dw 0x7E00
  .start_sector dq 35


diskinfo:
    .bootdrive db 0

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


