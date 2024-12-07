#include "../include/asm.hpp"
#include <stdint.h>
#include "../include/video.hpp"

void video::print_lenght(struct video_info *v,char* text,int len) 
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int i = 0;
    int in = v->cursor;
    while(i != len)
    {
        vid_mem[in] = text[i] | v->color << 8;
        i++;
        in++;
    }
    v->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void video::print(struct video_info* vid, const char* text)
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
        vid_mem[in] = text[i]| vid->color << 8;
        in++;
        i++;
    }
    vid->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void video::printChar(struct video_info* vid,  char l)
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int in = vid->cursor;
    if(l == '\n')
    {
        in += 80 - in % 80;
        return;
    }
    vid_mem[in] = l | vid->color << 8;
    in++;
    vid->cursor = in;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (in & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((in >> 8) & 0xFF));
}

void video::print_num(struct video_info *v,unsigned int num) {
	char buffer[11];
	int i = 0;
    unsigned int n = num;
	while(n != 0)
	{
		buffer[10-i] = '0' + (n % 10);
		n /= 10;
		i++;
	}
     if(num == 0) {
        video::printChar(v, '0');
        return;
    }
    video::print_lenght(v,&buffer[10-i+1],i);
}

void video::print_hex(struct video_info *v,unsigned int num,uint8_t x)
{
	char buffer[11];
	int i = 0;
    unsigned int n = num;
	while(n != 0)
	{
		buffer[10-i] = '0';
		if((n % 16) > 9)
		{
			buffer[10-i] = 'A' +(n % 16) - 10;
		}
		else {
			buffer[10-i] = '0' + n % 16;
		}
		n /= 16;
		i++;
	}
	if(x == 1)
    {
        video::print(v,"0x");
    }
    if(num == 0) {
        video::printChar(v, '0');
        return;
    }
    video::print_lenght(v,&buffer[10-i+1],i);
}

void video::print_char16(struct video_info *v,char16_t ch)
{
    video::printChar(v, ch & 0xFF);
}

void video::print16_length(struct video_info *v,char16_t *text,int len)
{
    for(int i = 0;i < len;i++)
    {
        video::print_char16(v, text[i]);
    }

}