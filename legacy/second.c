#include <stdint.h>
void boot_Main(uint32_t entry16);
void print_lenght(char* text,int len); 
void print(const char* text);
void print_num(int base,uint32_t num);
int strlen(const char* text);
void print_char(char c);

void boot_Main(uint32_t entry16)
{
    print("Hello,world\n");
}


int in= 0;
void print_num(int base,uint32_t num)
{
    char cache[32];
    int i = 0;
    while(num != 0)
    {
        cache[31-i] = 48 + num % base;
        num /= base;
        i++;
    }
    if (base == 16) print("0x");
    print_lenght(&cache[31-i+1], i);
}

int strlen(const char* text)
{
    int len = 0;
    while(text[len] != 0) len++;
    return len;
}

void print_lenght(char* text,int len) 
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int i = 0;
    while(i != len)
    {
        vid_mem[in] = text[i] | 0x0f << 8;
        i++;
        in++;
    }
}
void print_char(char c)
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    vid_mem[in] = c | 0x0f << 8;
    in++;
}

void print(const char* text)
{
    unsigned short *vid_mem = (unsigned short *)0xb8000;
    int i = 0;
    while(text[i] != 0)
    {
        vid_mem[in] = text[i] | 0x0f << 8;
        in++;
        i++;
    }
}