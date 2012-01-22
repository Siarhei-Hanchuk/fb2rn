#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *strlwr(char *s)
{
    for(int i=0;s[i]!=0;i++)
        s[i]=tolower(s[i]);
    return s;
}

char *strupr(char *s)
{
    for(int i=0;s[i]!=0;i++)
        s[i]=toupper(s[i]);
    return s;
}

char *strcpy_m(char *Dst,int beginSrc,int endSrc,const char *Src,long beginDst)
{
    int i;
	for(i=beginDst;i<=endSrc-beginSrc+beginDst;i++){
		Dst[i]=Src[i+beginSrc];
	}
	Dst[i]=0;
	return Dst;
}

int pos(const char *substr,const char *str)
{
	if(strlen(substr)==1){
		for(int j=0;str[j]!=0;j++){
			if(str[j]==substr[0]){
			    return j;
            }
		}
		return -1;
	}
	else{
        int i=0;
        int sizeSub=strlen(substr);
        int sizeStr=strlen(str);
        if(sizeStr<sizeSub)
            return 0;
        char *tmp=(char *)malloc(sizeof(char)*(sizeSub+1));
        for(i=0;i<sizeStr-sizeSub+2;i++){
            strcpy_m(tmp,i,sizeSub+i-1,str,0);
            if(!strcoll(tmp,substr)){
                free(tmp);
                return i;
		    }
        }
	free(tmp);
	}
	return -1;
}

char *itoa(const long int n)
{
    long int t=n;
    char *buf=(char *)malloc(sizeof(char)*21);
    memset(buf,0,21);
    if(n==0){
        buf[0]='0';
        buf[1]=0;
        return buf;
    }
    char *tmp=(char *)malloc(sizeof(char)*21);
    memset(buf,0,21);
    int i=0;
    while(t!=0){
        tmp[i]=abs(t%10)+48;
        t=t/10;
        i++;
    }
    i--;

    short j=0;
    if(n<0){
        buf[0]='-';
        j=1;
    }
    while(i>-1){
        buf[j]=tmp[i];
        i--;
        j++;
    }
    free(tmp);
    return buf;
}
