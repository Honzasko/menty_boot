
#include <stdint.h>
struct video {
    uint16_t cursor;
    char color;
};

void print_lenght(struct video *v,char* text,int len) ;

void print(struct video* vid, const char* text);

void printChar(struct video* vid,  char l);

void print_num(struct video *v,unsigned int num);

void print_hex(struct video *v,unsigned int num,unsigned char x);

void print_char16(struct video *v,char16_t ch);

void print16_length(struct video *v,char16_t *text,int len);