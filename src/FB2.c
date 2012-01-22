#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "charstr.h"
#include "cp.h"

char *xml_GetParam(const char *par,const char *str)
//!Получение значегия xml параметра
{
	int l=strlen(par);
	char *tmp=(char *)malloc(sizeof(char)*(l+1+3));
	memset(tmp,0,sizeof(char)*(l+1+3));
	char *tmp2=(char *)malloc(sizeof(char)*(l+1));
	memset(tmp2,0,sizeof(char)*(l+1));
	int i,j;
	strcat(tmp,"</");
	strcpy_m(tmp2,1,l,par,0);
	strcat(tmp,tmp2);
	i=pos(par,str);
	if(i==-1){
        free(tmp);
        free(tmp2);
	    return 0;
    }
	j=pos(tmp,str);
	char *q=(char *)malloc(sizeof(char)*(strlen(str)));
	memset(q,0,sizeof(char)*strlen(str));
	strcpy_m(q,i+l,j-1,str,0);
	free(tmp);
	free(tmp2);
	char *r=(char *)malloc(sizeof(char)*(strlen(q)+1));
	strcpy(r,q);
	free(q);
	return r;
}

int LoadFile(const char *fn,char **file)
//!Загрука файла в оперативную память, возвращает размер или -1 если файл не удалось открыть
{
    FILE *f=fopen(fn,"r");
    if(f==NULL){
        fclose(f);
        return -1;
    }
    fseek(f,0,SEEK_END);
    int len=ftell(f);
    fseek(f,0,SEEK_SET);
    if(len==0){
        fclose(f);
        return 0;
    }
    char *tmp=(char *)malloc(sizeof(char)*len+1);
    tmp[len]=0;
    fread(tmp,len,1,f);
    *file=tmp;
    fclose(f);
    return len;
}

int FB2Load(const char *fn,char **book)
//!Главная функция загрузки книги в память в кодировке UTF-8
//!Возвращает код ошибки или 0 если всё нормально
{
    char *file;
    int len=LoadFile(fn,&file);
    if(len<1){
        free(file);
        return 1;
    };
    int cp=getCP(file,len);
    if(cp==UTF8){
        *book=file;
        return 0;
    }
    if(cp==win1251){
        _Bool err;
        *book=cp1251bytetoutf8(file,len,&err);
        free(file);
        if(err)
            return 3;
        return 0;
    }
    if(cp==UTF16){
        *book=utf16filetoutf8(file,len);
        free(file);
        return 0;
    }
    if(cp==UTF32){
        *book=utf32filetoutf8(file,len);
        free(file);
        return 0;
    }
    free(file);
    return 2;
}

