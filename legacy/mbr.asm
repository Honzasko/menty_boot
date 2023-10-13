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
push diskinfo ;add basic structure for second stage
call 0x00007E00 ;call main function of second stage 
hlt


dap:
  .size db 10h
  .unused db 0
  .sectors_to_read dw 15
  .segment dw 0
  .offset  dw 0x7E00
  .start_sector dq 35

stack32 dd 0

diskinfo:
    .bootdrive db 0
    .read_disk_ptr dd 0

error db 0
index dd 0
cache: times 10 db 0


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

