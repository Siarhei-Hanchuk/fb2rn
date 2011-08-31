#include <string.h>
#include "charstr.h"

#include "cp.h"

//!!CONVERT CP

char *u16filetochar(byte *file, int len)
//!кодирование содержимого utf16 файла в char utf8
{
    char *r=new char[len];memset(r,0,len);
    int i=0,t;
    int e=0;
    while(i<len){
        t=file[i]+file[i+1]*256;
        if(t<128){r[e]=t;}else
        if(t<2048){
            //r[e]='!';
            r[e]=t/64+128+64;e++;
            r[e]=t%64+128;
        }else{
            r[e]=t/(64*64)+128+64+32;e++;
            r[e]=(t%(64*64))/64+128;e++;
            r[e]=(t%(64*64))%64+128;
        }
        e++;
        i+=2;
    }
    return r;
}

char *u32filetochar(byte *file, int len)
//!кодирование содержимого utf32 файла в char utf8
{
    char *r=new char[len];memset(r,0,len);
    int i=0,t;
    int e=0;
    while(i<len){
        t=file[i]+file[i+1]*256+file[i+2]*256*256+file[i+3]*256*256*256;
        if(t<128){r[e]=t;}else
        if(t<2048){
            //r[e]='!';
            r[e]=t/64+128+64;e++;
            r[e]=t%64+128;
        }else{
            r[e]=t/(64*64)+128+64+32;e++;
            r[e]=(t%(64*64))/64+128;e++;
            r[e]=(t%(64*64))%64+128;
        }
        e++;
        i+=4;
    }
    return r;
}

char *cp1251bytetochar(byte *file,int len)
//!Кодирование _содержимого_ файла из cp1251 в UTF-8
{
    char *r=new char[len*2];
    memset(r,0,len*2);
    int j=0;
    for(int i=0;i<len;i++){
        if(file[i]<128){
            r[j]=file[i];
            j++;
        }
        else{
            if((0xC0<=file[i])&&(file[i]<=0xEF)){
                r[j]=0xD0;r[j+1]=file[i]-0x30;
                j+=2;
                continue;
            }else
            if((0xF0<=file[i])&&(file[i]<=0xFF)){
                r[j]=0xD1;r[j+1]=file[i]-0x70;
                j+=2;
                continue;
            }else
            switch(file[i]){
            case 0x80:
                r[j]=-48;
                r[j+1]=-126;
                break;
            case 0x81:
                r[j]=-48;
                r[j+1]=-125;
                break;
            case 0x82:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-102;
                j++;
                break;
            case 0x83:
                r[j]=-47;
                r[j+1]=-109;
                break;
            case 0x84:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-98;
                j++;
                break;
            case 0x85:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-90;
                j++;
                break;
            case 0x86:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-96;
                j++;
                break;
            case 0x87:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-95;
                j++;
                break;
            case 0x88:
                r[j]=-30;
                r[j+1]=-126;
                r[j+2]=-84;
                j++;
                break;
            case 0x89:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-80;
                j++;
                break;
            case 0x8a:
                r[j]=-48;
                r[j+1]=-119;
                break;
            case 0x8b:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-71;
                j++;
                break;
            case 0x8c:
                r[j]=-48;
                r[j+1]=-118;
                break;
            case 0x8d:
                r[j]=-48;
                r[j+1]=-116;
                break;
            case 0x8e:
                r[j]=-48;
                r[j+1]=-117;
                break;
            case 0x8f:
                r[j]=-48;
                r[j+1]=-113;
                break;

            case 0x90:
                r[j]=-47;
                r[j+1]=-110;
                break;
            case 0x91:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-104;
                j++;
                break;
            case 0x92:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-103;
                j++;
                break;
            case 0x93:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-100;
                j++;
                break;
            case 0x94:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-99;
                j++;
                break;
            case 0x95:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-94;
                j++;
                break;
            case 0x96:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-109;
                j++;
                break;
            case 0x97:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-108;
                j++;
                break;
            case 0x99:
                r[j]=-30;
                r[j+1]=-124;
                r[j+2]=-94;
                j++;
                break;
            case 0x9a:
                r[j]=-47;
                r[j+1]=-103;
                break;
            case 0x9b:
                r[j]=-30;
                r[j+1]=-128;
                r[j+2]=-70;
                j++;
                break;
            case 0x9c:
                r[j]=-47;
                r[j+1]=-102;
                break;
            case 0x9d:
                r[j]=-47;
                r[j+1]=-100;
                break;
            case 0x9e:
                r[j]=-47;
                r[j+1]=-101;
                break;
            case 0x9f:
                r[j]=-47;
                r[j+1]=-97;
                break;

            case 0xA0:
                r[j]=-62;
                r[j+1]=-96;
                break;
            case 0xA1:
                r[j]=-48;
                r[j+1]=-114;
                break;
            case 0xA2:
                r[j]=-47;
                r[j+1]=-98;
                break;
            case 0xA3:
                r[j]=-48;
                r[j+1]=-120;
                break;
            case 0xA4:
                r[j]=-62;
                r[j+1]=-92;
                break;
            case 0xA5:
                r[j]=-46;
                r[j+1]=-112;
                break;
            case 0xA6:
                r[j]=-62;
                r[j+1]=-90;
                break;
            case 0xA7:
                r[j]=-62;
                r[j+1]=-89;
                break;
            case 0xA8:
                r[j]=-48;
                r[j+1]=-127;
                break;
            case 0xA9:
                r[j]=-62;
                r[j+1]=-87;
                break;
            case 0xAa:
                r[j]=-48;
                r[j+1]=-124;
                break;
            case 0xAb:
                r[j]=-62;
                r[j+1]=-85;
                break;
            case 0xAc:
                r[j]=-62;
                r[j+1]=-84;
                break;
            case 0xAd:
                r[j]=-62;
                r[j+1]=-83;
                break;
            case 0xAe:
                r[j]=-62;
                r[j+1]=-82;
                break;
            case 0xAf:
                r[j]=-48;
                r[j+1]=-121;
                break;

            case 0xB0:
                r[j]=-62;
                r[j+1]=-80;
                break;
            case 0xB1:
                r[j]=-62;
                r[j+1]=-79;
                break;
            case 0xB2:
                r[j]=-48;
                r[j+1]=-122;
                break;
            case 0xB3:
                r[j]=-47;
                r[j+1]=-106;
                break;
            case 0xB4:
                r[j]=-46;
                r[j+1]=-111;
                break;
            case 0xB5:
                r[j]=-62;
                r[j+1]=-75;
                break;
            case 0xB6:
                r[j]=-62;
                r[j+1]=-74;
                break;
            case 0xB7:
                r[j]=-62;
                r[j+1]=-73;
                break;
            case 0xB8:
                r[j]=-47;
                r[j+1]=-111;
                break;
            case 0xB9:
                r[j]=-30;
                r[j+1]=-124;
                r[j+2]=-106;
                j++;
                break;
            case 0xBa:
                r[j]=-47;
                r[j+1]=-108;
                break;
            case 0xBb:
                r[j]=-62;
                r[j+1]=-69;
                break;
            case 0xBc:
                r[j]=-47;
                r[j+1]=-104;
                break;
            case 0xBd:
                r[j]=-48;
                r[j+1]=-123;
                break;
            case 0xBe:
                r[j]=-47;
                r[j+1]=-107;
                break;
            case 0xBf:
                r[j]=-47;
                r[j+1]=-105;
                break;

            default:
                break;
            }
            j+=2;
        }
    }
    return r;
}

char* RusAnsiiToDos(char *buf)
{
///А -128 Я -97
///а -96 п -81
///р -32 я -17
	char *res=new char[1024];
	memset(res,0,14);
	int l,i;
	l=strlen(buf);
	for(i=0;i<=l;i++){
		if(buf[i]<0){
			res[i]=buf[i]-64;
		}if(buf[i]>-17){res[i]=buf[i]-16;}
	}
	res[i-1]=0;
	return res;
}

char *bytetochar(const byte *data,int len)
//!Содержимое utf8 файла(byte) в строку char
{
    char *res=new char[len+1];
    for(int i=0;i<len;i++){
        res[i]=data[i];
    }
    res[len]=0;
	return res;
}

//!!GET CP

int getCPbom(const byte *file)
//!Получени кодировки из BOM
{
    if((file[0]==0xFF)&&(file[1]==0xFE)&&(file[2]==0x00)&&(file[3]==0x00)){return UTF32;}
    if((file[0]==0xFF)&&(file[1]==0xFE)){return UTF16;}
	if((file[0]==0xEF)&&(file[1]==0xBB)&&(file[2]==0xBF)){return UTF8;}
	return 0;
}

int getCPzero(const byte *file,const int len)
//!Получени кодировки из нулей
{
    if((file[2]==0)&&(file[3]==0)&&(file[5]==0)&&(file[6]==0)&&(file[7]==0)){return UTF32;}
    int l=len;
    if(len>100){l=100;}
    int z=0;
    for(int i=0;i<l;i++){
        if(file[i]==0){z++;}
    }
    if(z>0){return UTF16;}
    return UTF8;
}

int xml_getCP(const char *str)
//!Получение кодировки из xml
{
	int l=pos("encoding=",str);
	if(l==0){return UTF8;}
	char *tmp=new char[100];memset(tmp,0,100);
	strcpy_m(tmp,l+9+1,l+9+1+20,str);
	int e=pos("\"",tmp);
	char *r=new char[100];memset(r,0,100);
	strcpy_m(r,0,e-1,tmp);
	//std::cout<<strlwr(r)<<std::endl;
	delete[] tmp;
	if(strcmp(strlwr(r),"utf-8")==0){delete[] r; return UTF8;}
	if(strcmp(strlwr(r),"utf-16")==0){delete[] r; return UTF16;}
	if(strcmp(strlwr(r),"utf-32")==0){delete[] r; return UTF32;}
	if(strcmp(strlwr(r),"windows-1251")==0){delete[] r; return win1251;}
	return 0;
}

int getCP(const byte *file,const int len)
//!Получение кодировки, Сначала через BOM, если не удалось то через нули, и в конец через xml
{
    int c=0;
    c=getCPbom(file);
    if(c==0){c=getCPzero(file,len);}
        else{return c;}
    if((c==UTF16)||(c==UTF32)){return c;}else{
        char *btc=bytetochar(file,len);
        int xgp=xml_getCP(btc);
        delete[] btc;
        return xgp;
    }
}
