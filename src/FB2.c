#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "charstr.h"
#include "cp.h"

char *xml_GetParam(const char *par,const char *str)
//!Получение значегия xml параметра
{
	int l=strlen(par);
	char *tmp=new char[l+1+3];
	memset(tmp,0,sizeof(char)*(l+1+3));
	char *tmp2=new char[l+1];
	memset(tmp2,0,sizeof(char)*(l+1));
	int i,j;
	strcat(tmp,"</");
	strcpy_m(tmp2,1,l,par);
	strcat(tmp,tmp2);
	i=pos(par,str);
	if(i==-1){
        delete[] tmp;
        delete[] tmp2;
	    return 0;
    }
	j=pos(tmp,str);
	char *q=new char[strlen(str)];
	memset(q,0,sizeof(char)*strlen(str));
	strcpy_m(q,i+l,j-1,str);
	delete[] tmp;
	delete[] tmp2;
	char *r=new char[strlen(q)+1];
	strcpy(r,q);
	delete[] q;
	return r;
}

int LoadFile(const char *fn,byte *&file)
//!Загрука файла в оперативную память, возвращает размер или -1 если файл не удалось открыть
{
    FILE *f=fopen(fn,"r");
    if(f==NULL){fclose(f);return -1;}
    fseek(f,0,SEEK_END);
    int len=ftell(f);
    fseek(f,0,SEEK_SET);
    if(len==0){fclose(f);return 0;}
    file=new byte[len];
    fread(file,len,1,f);
    fclose(f);
    return len;
}

int LoadFile(const char *fn,char *&file)
//!Загрука файла в оперативную память, возвращает размер или -1 если файл не удалось открыть
{
    FILE *f=fopen(fn,"r");
    if(f==NULL){fclose(f);return -1;}
    fseek(f,0,SEEK_END);
    int len=ftell(f);
    fseek(f,0,SEEK_SET);
    if(len==0){fclose(f);return 0;}
    file=new char[len];
    fread(file,len,1,f);
    fclose(f);
    return len;
}

int FB2Load(const char *fn,char *&book)
//!Главная функция загрузки книги в память в кодировке UTF-8
//!Возвращает код ошибки или 0 если всё нормально
{
    byte *file;
    int len=LoadFile(fn,file);
    if(len<1){delete[] file;return 1;};
    int cp=getCP(file,len);

    if(cp==UTF8){
        book=bytetochar(file,len);
        delete[] file;
        return 0;
    }
    if(cp==win1251){
        book=cp1251bytetochar(file,len);
        delete[] file;
        return 0;
    }
    if(cp==UTF16){
        book=u16filetochar(file,len);
        delete[] file;
        return 0;
    }
    if(cp==UTF32){
        book=u32filetochar(file,len);
        delete[] file;
        return 0;
    }
    delete[] file;
    return 2;
}

