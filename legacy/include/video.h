
struct video {
    int cursor;
    char color;
};

void print_lenght(struct video *v,char* text,int len) ;

void print(struct video* vid, const char* text);

void printChar(struct video* vid,  char l);

void print_num(struct video *v,unsigned int num);

void print_hex(struct video *v,unsigned int num,unsigned char x);