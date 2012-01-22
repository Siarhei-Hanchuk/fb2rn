#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

char *getFilepath_fromFullname(char *FullName)
{
	char *r=(char *)malloc(sizeof(char)*(256));
	memset(r,0,256);
	int l=strlen(FullName);
	for(int i=l;i>0;i--){
	    if(FullName[i]=='/'){
	        l=i;
	        break;
	    }
	}
	int i;
	for(i=0;i<l+1;i++){
        r[i]=FullName[i];
	}
	r[l+1]=0;
	return r;
}

char *getFilename_fromFullname(char *n)
{
    int l=strlen(n);
    if(n[l]=='/'){
        return 0;
    }
    char *r=(char *)malloc(sizeof(char)*(l));
    memset(r,0,l);
    int i=0;
    int e=0;
    for(i=l;n[i]!='/';i--);
    for(int j=i+1;j<l;j++){
        r[e]=n[j];e++;
    }
    return r;
}

char *delescape(char *str,_Bool newline)
{
    char escSymb[]={'"','\\','\'',')','(',' ',13,10};
    int l=strlen(str);
    char *n=(char *)malloc(sizeof(char)*(l*2));
    memset(n,0,l*2);
    int e=0;
    for(int i=0;i<l;i++){
        if(strchr(escSymb,str[i])!=NULL){
            n[e]='\\';
            n[e+1]=str[i];
            if((newline)&&
               ((n[e+1]==10)||(n[e+1]==13))){
                    n[e+1]=' ';
                }
            e+=2;
        }else{
            n[e]=str[i];
            e++;
        }
    }
    return n;
}

_Bool fileexist(char *path)
{
    struct stat filest;
	int s=stat(path, &filest);
	if(s==0){
	    return 1;
    }
    return 0;
}
