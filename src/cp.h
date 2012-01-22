typedef unsigned char byte;

#define win1251 1
#define UTF8     2
#define UTF16   3
#define UTF32   4

char *u16filetochar(byte *file, int len);
char *u32filetochar(byte *file, int len);
char *cp1251bytetochar(byte *file,int len);
char* RusAnsiiToDos(char *buf);
char *bytetochar(const byte *data,int len);
int getCPbom(const byte *file);
int getCPzero(const byte *file,const int len);
int getCP(const byte *file,const int len);
