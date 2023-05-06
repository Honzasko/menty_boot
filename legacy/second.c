#include <stdint.h>

struct video {
    int cursor;
    char color;
};

struct conversion {
    char buffer[11];
    int len;
};

void boot_Main(uint32_t entry16);
void print_lenght(struct video *v,char* text,int len); 
void print(struct video *v, const char* text);
void unsigned_int_to_string(unsigned int num, char* str);
int strlen(const char* text);
void print_char(char c);

int in = 0;
void boot_Main(uint32_t entry16)
{
    if(entry16 == 0) return;
    struct video v;
    v.cursor = 0;
    v.color = 0x0f;
    print(&v, "Test\nnum: ");
    unsigned int num = 123456789;
    char str[20];
    unsigned_int_to_string(num, str);
    int len = strlen(str);
    print_lenght(&v, "Length: ", 8);
    print_lenght(&v, str, len);

}

int strlen(const char* text)
{
    int len = 0;
    while(text[len] != 0) len++;
    return len;
}

void unsigned_int_to_string(unsigned int num, char* str) {
    int i = 0;
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num != 0);
    str[i] = '\0';
    
    // reverse the string
    int j = i - 1;
    i = 0;
    while (i < j) {
        char temp = str[i];
        str[i++] = str[j];
        str[j--] = temp;
    }
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


