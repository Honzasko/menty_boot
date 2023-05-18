#pragma once
#include "../include/video.h"

void print_lenght(struct video *v,char* text,int len) 
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
        vid_mem[in] = text[i] | vid->color << 8;
        in++;
        i++;
    }
    vid->cursor = in;
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

void print_hex(struct video *v,unsigned int num)
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
	print(v,"0x");
    print_lenght(v,&buffer[10-i+1],i);
}