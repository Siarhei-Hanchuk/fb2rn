#include <string.h>
#include <stdlib.h>

#include "charstr.h"
#include "cp.h"

unsigned char *chartouchar(char *data,int len)
{
    unsigned char *res=(unsigned char *)malloc(sizeof(unsigned char)*(len+1));
    for(int i=0;i<len;i++){
        res[i]=data[i];
    }
    res[len]=0;
	return res;
}

char *utf16filetoutf8(char *file_, int len)
{
    unsigned char *file=chartouchar(file_,len);
    char *r=(char *)malloc(sizeof(char)*(len));
    memset(r,0,len);
    int i=0,t;
    int e=0;
    while(i<len){
        t=file[i]+file[i+1]*256;
        if(t<128){
            r[e]=t;
        }else
        if(t<2048){
            r[e]=t/64+128+64;
            e++;
            r[e]=t%64+128;
        }else{
            r[e]=t/(64*64)+128+64+32;
            e++;
            r[e]=(t%(64*64))/64+128;
            e++;
            r[e]=(t%(64*64))%64+128;
        }
        e++;
        i+=2;
    }
    free(file);
    return r;
}

char *utf32filetoutf8(char *file_, int len)
{
    unsigned char *file=chartouchar(file_,len);
    char *r=(char *)malloc(sizeof(char)*(len));
    memset(r,0,len);
    int i=0,t;
    int e=0;
    while(i<len){
        t=file[i]+file[i+1]*256+file[i+2]*256*256+file[i+3]*256*256*256;
        if(t<128){
            r[e]=t;
        }else
        if(t<2048){
            r[e]=t/64+128+64;
            e++;
            r[e]=t%64+128;
        }else{
            r[e]=t/(64*64)+128+64+32;
            e++;
            r[e]=(t%(64*64))/64+128;
            e++;
            r[e]=(t%(64*64))%64+128;
        }
        e++;
        i+=4;
    }
    free(file);
    return r;
}

char *cp1251bytetoutf8(char *file,int len,_Bool *err)
{
    *err=0;
    char *r=(char *)malloc(sizeof(char)*(len*3));
    memset(r,0,len*3);
    int j=0;
    for(int i=0;i<len;i++){
        if(file[i]>0){
            r[j]=file[i];
            j++;
            continue;
        }
        if((-64<=file[i])&&(file[i]<=-17)){
                r[j]=0xD0;r[j+1]=file[i]-0x30;
                j+=2;
                continue;
        }
        if((-16<=file[i])&&(file[i]<=-1)){
            r[j]=0xD1;r[j+1]=file[i]-0x70;
            j+=2;
            continue;
        }
        switch(file[i]){
        case -128:
            r[j]=-48;
            r[j+1]=-126;
            break;
        case -127:
            r[j]=-48;
            r[j+1]=-125;
            break;
        case -126:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-102;
            j++;
            break;
        case -125:
            r[j]=-47;
            r[j+1]=-109;
            break;
        case -124:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-98;
            j++;
            break;
        case -123:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-90;
            j++;
            break;
        case -122:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-96;
            j++;
            break;
        case -121:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-95;
            j++;
            break;
        case -120:
            r[j]=-30;
            r[j+1]=-126;
            r[j+2]=-84;
            j++;
            break;
        case -119:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-80;
            j++;
            break;
        case -118:
            r[j]=-48;
            r[j+1]=-119;
            break;
        case -117:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-71;
            j++;
            break;
        case -116:
            r[j]=-48;
            r[j+1]=-118;
            break;
        case -115:
            r[j]=-48;
            r[j+1]=-116;
            break;
        case -114:
            r[j]=-48;
            r[j+1]=-117;
            break;
        case -113:
            r[j]=-48;
            r[j+1]=-113;
            break;
        case -112:
            r[j]=-47;
            r[j+1]=-110;
            break;
        case -111:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-104;
            j++;
            break;
        case -110:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-103;
            j++;
            break;
        case -109:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-100;
            j++;
            break;
        case -108:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-99;
            j++;
            break;
        case -107:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-94;
            j++;
            break;
        case -106:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-109;
            j++;
            break;
        case -105:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-108;
            j++;
            break;
        case -104:
            *err=1;
            break;
        case -103:
            r[j]=-30;
            r[j+1]=-124;
            r[j+2]=-94;
            j++;
            break;
        case -102:
            r[j]=-47;
            r[j+1]=-103;
            break;
        case -101:
            r[j]=-30;
            r[j+1]=-128;
            r[j+2]=-70;
            j++;
            break;
        case -100:
            r[j]=-47;
            r[j+1]=-102;
            break;
        case -99:
            r[j]=-47;
            r[j+1]=-100;
            break;
        case -98:
            r[j]=-47;
            r[j+1]=-101;
            break;
        case -97:
            r[j]=-47;
            r[j+1]=-97;
            break;
        case -96:
            r[j]=-62;
            r[j+1]=-96;
            break;
        case -95:
            r[j]=-48;
            r[j+1]=-114;
            break;
        case -94:
            r[j]=-47;
            r[j+1]=-98;
            break;
        case -93:
            r[j]=-48;
            r[j+1]=-120;
            break;
        case -92:
            r[j]=-62;
            r[j+1]=-92;
            break;
        case -91:
            r[j]=-46;
            r[j+1]=-112;
            break;
        case -90:
            r[j]=-62;
            r[j+1]=-90;
            break;
        case -89:
            r[j]=-62;
            r[j+1]=-89;
            break;
        case -88:
            r[j]=-48;
            r[j+1]=-127;
            break;
        case -87:
            r[j]=-62;
            r[j+1]=-87;
            break;
        case -86:
            r[j]=-48;
            r[j+1]=-124;
            break;
        case -85:
            r[j]=-62;
            r[j+1]=-85;
            break;
        case -84:
            r[j]=-62;
            r[j+1]=-84;
            break;
        case -83:
            r[j]=-62;
            r[j+1]=-83;
            break;
        case -82:
            r[j]=-62;
            r[j+1]=-82;
            break;
        case -81:
            r[j]=-48;
            r[j+1]=-121;
            break;
        case -80:
            r[j]=-62;
            r[j+1]=-80;
            break;
        case -79:
            r[j]=-62;
            r[j+1]=-79;
            break;
        case -78:
            r[j]=-48;
            r[j+1]=-122;
            break;
        case -77:
            r[j]=-47;
            r[j+1]=-106;
            break;
        case -76:
            r[j]=-46;
            r[j+1]=-111;
            break;
        case -75:
            r[j]=-62;
            r[j+1]=-75;
            break;
        case -74:
            r[j]=-62;
            r[j+1]=-74;
            break;
        case -73:
            r[j]=-62;
            r[j+1]=-73;
            break;
        case -72:
            r[j]=-47;
            r[j+1]=-111;
            break;
        case -71:
            r[j]=-30;
            r[j+1]=-124;
            r[j+2]=-106;
            j++;
            break;
        case -70:
            r[j]=-47;
            r[j+1]=-108;
            break;
        case -69:
            r[j]=-62;
            r[j+1]=-69;
            break;
        case -68:
            r[j]=-47;
            r[j+1]=-104;
            break;
        case -67:
            r[j]=-48;
            r[j+1]=-123;
            break;
        case -66:
            r[j]=-47;
            r[j+1]=-107;
            break;
        case -65:
            r[j]=-47;
            r[j+1]=-105;
            break;
        default:
            break;
        }
        j+=2;
    }
    return r;
}

/*char* cp1251toCP866(char *buf)
{
	char *res=(char *)malloc(sizeof(char)*(1024));
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
*/

int getCPbom(const char *file)
//!Получени кодировки из BOM
{
    if((file[0]==-1)&&(file[1]==-2)&&(file[2]==0x00)&&(file[3]==0x00))
        return UTF32;
    if((file[0]==-1)&&(file[1]==-2))
        return UTF16;
	if((file[0]==-17)&&(file[1]==-69)&&(file[2]==-65))
        return UTF8;
	return 0;
}

int getCPzero(const char *file,const int len)
//!Получени кодировки из нулей
{
    if((file[2]==0)&&(file[3]==0)&&(file[5]==0)&&(file[6]==0)&&(file[7]==0))
        return UTF32;
    int l=len;
    if(len>100){
        l=100;
    }
    int z=0;
    for(int i=0;i<l;i++){
        if(file[i]==0)
            z++;
    }
    if(z>0)
        return UTF16;
    return UTF8;
}

int xml_getCP(const char *str)
//!Получение кодировки из xml
{
	int l=pos("encoding=",str);
	if(l==0)
        return UTF8;
	char *tmp=(char *)malloc(sizeof(char)*(100));
	memset(tmp,0,100);
	strcpy_m(tmp,l+9+1,l+9+1+20,str,0);
	int e=pos("\"",tmp);
	char *r=(char *)malloc(sizeof(char)*(100));
	memset(r,0,100);
	strcpy_m(r,0,e-1,tmp,0);
	free(tmp);
	if(strcmp(strlwr(r),"utf-8")==0){
	    free(r);
	    return UTF8;
    }
	if(strcmp(strlwr(r),"utf-16")==0){
	    free(r);
	    return UTF16;
	}
	if(strcmp(strlwr(r),"utf-32")==0){
	    free(r);
	    return UTF32;
	}
	if(strcmp(strlwr(r),"windows-1251")==0){
	    free(r);
	    return win1251;
    }
	return 0;
}

int getCP(const char *file,const int len)
//!Получение кодировки, Сначала через BOM, если не удалось то через нули, и в конец через xml
{
    int c=0;
    c=getCPbom(file);
    if(c==0)
        c=getCPzero(file,len);
    else
        return c;
    if((c==UTF16)||(c==UTF32))
        return c;
    else{
        int xgp=xml_getCP(file);
        return xgp;
    }
}
