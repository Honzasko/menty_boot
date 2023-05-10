#include <stdint.h>

struct video {
    int cursor;
    char color;
};

struct video v;

int in = 0;

int strlen(const char* text)
{
    int len = 0;
    while(text[len] != 0) len++;
    return len;
}

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


void boot_Main(uint32_t entry16)
{
    if(entry16 == 0) return;
    v.cursor = 0;
    v.color = 0x0f;
    print(&v, "Test\nnum:");
	print_num(&v,123456);
}
