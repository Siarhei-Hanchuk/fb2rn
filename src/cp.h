#define win1251 1
#define UTF8    2
#define UTF16   3
#define UTF32   4

char *utf16filetoutf8(char *file, int len);
char *utf32filetoutf8(char *file, int len);
char *cp1251bytetoutf8(char *file,int len, _Bool *err);
int getCPbom(const char *file);
int getCPzero(const char *file,const int len);
int getCP(const char *file,const int len);
