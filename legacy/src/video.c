#include "../include/asm.h"
#include <stdint.h>
#include <uchar.h>
#include "../include/video.h"

void print_lenght(struct video *v,char* text,int len) 
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int i = 0;
    int in = v->cursor;
    while(i != len)
    {
        vid_mem[in] = text[i] & 0xFF | v->color << 8;
        i++;
        in++;
    }
    v->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void print(struct video* vid, const char* text)
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int in = vid->cursor;
    int i = 0;
    while(text[i] != 0)
    {
        if(text[i] == '\n') {
            in += 80 - in % 80;
            i++;
            continue;
        }
        vid_mem[in] = text[i] & 0xFF | vid->color << 8;
        in++;
        i++;
    }
    vid->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void printChar(struct video* vid,  char l)
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int in = vid->cursor;
    if(l == '\n')
    {
        in += 80 - in % 80;
        return;
    }
    vid_mem[in] = l & 0xFF | vid->color << 8;
    in++;
    vid->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void print_num(struct video *v,unsigned int num) {
	char buffer[11];
	int i = 0;
	while(num != 0)
	{
		buffer[10-i] = '0' + (num % 10);
		num /= 10;
		i++;
	}
    print_lenght(v,&buffer[10-i+1],i);
}

void print_hex(struct video *v,unsigned int num,uint8_t x)
{
	char buffer[11];
	int i = 0;
	while(num != 0)
	{
		buffer[10-i] = '0';
		if((num % 16) > 9)
		{
			buffer[10-i] = 'A' +(num % 16) - 10;
		}
		else {
			buffer[10-i] = '0' + num % 16;
		}
		num /= 16;
		i++;
	}
	if(x == 1)
    {
        print(v,"0x");
    }
    print_lenght(v,&buffer[10-i+1],i);
}

void print_char16(struct video *v,char16_t ch)
{
    printChar(v, ch & 0xFF);
}

void print16_length(struct video *v,char16_t *text,int len)
{
    for(int i = 0;i < len;i++)
    {
        print_char16(v, text[i]);
    }

}