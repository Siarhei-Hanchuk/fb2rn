#include  <sys/stat.h>
#include <string.h>

char *getPath(char *FullName)
//!Получение пути из полного имени файла
{
	char *r=new char[256];
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

char *getFilename(char *n)
//!Получние имени файла из полного имени
{
    int l=strlen(n);
    if(n[l]=='/'){return 0;}
    char *r=new char[l];
    memset(r,0,l);
    int i=0;
    int e=0;
    for(i=l;n[i]!='/';i--);
    for(int j=i+1;j<l;j++){
        r[e]=n[j];e++;
    }
    return r;
}

char *delescape(char *str)
//! Установка перез пробелами и др символа '\'
//! Перед пробелом '\', Замена перехода на новую строку на пробел
{
    //char smbls[100];
    //strcpy(smbls,"\"\\\')( \13\10")

    int l=strlen(str);
    char *n=new char[l*2];
    memset(n,0,l*2);
    int e=0;
    for(int i=0;i<l;i++){
        if((str[i]=='"')||(str[i]=='\\')||(str[i]=='\'')||(str[i]==')')||(str[i]=='(')||(str[i]==' ')||((str[i]==13)||(str[i]==10))){
            n[e]='\\';
            n[e+1]=str[i];
            if((n[e+1]==10)||(n[e+1]==13)){n[e+1]=' ';}
            e+=2;
        }else
        {n[e]=str[i];e++;}
    }
    return n;
}

bool fileexist(char *path)
{
    struct stat filest;
	int s=stat(path, &filest);
	if(s==0){return true;}else{return false;}
}
