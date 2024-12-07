
#include <stdint.h>
struct video_info {
    uint16_t cursor;
    char color;
};

namespace video {
void print_lenght(struct video_info *v,char* text,int len) ;

void print(struct video_info* vid, const char* text);

void printChar(struct video_info* vid,  char l);

void print_num(struct video_info *v,unsigned int num);

void print_hex(struct video_info *v,unsigned int num,unsigned char x);

void print_char16(struct video_info *v,char16_t ch);

void print16_length(struct video_info *v,char16_t *text,int len);
}