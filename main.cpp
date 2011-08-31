#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "functions.h"
#include "charstr.h"
#include "cp.h"
#include "FB2.h"

using namespace std;

bool procfile(char* oldname, char *book, char *params, bool Or,bool Oind, bool Onoerr,int &err,int &nr,int &rn)
{
    char tags[13]="nftmglpyi";
    char *newname=new char[256*2+20];
    char *newnamet=new char[256];memset(newnamet,0,256);
    int y=0;
    int l=strlen(params);
    if(l==0){strcpy(params,"-Pn f - t");l=strlen(params);}
    char *tmp=getPath(oldname);
    strcpy(newname,tmp);
    delete[] tmp;
    for(int i=2;i<l;i++){
        if(strchr(tags,params[i])==NULL){y=strlen(newnamet);newnamet[y]=params[i];}
        else{
            switch(params[i]){
                case 'n':
                    tmp=xml_GetParam("<first-name>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'f':
                    tmp=xml_GetParam("<last-name>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 't':
                    tmp=xml_GetParam("<book-title>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'm':
                    tmp=xml_GetParam("<middle-name>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'g':
                    tmp=xml_GetParam("<genre>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'l':
                    tmp=xml_GetParam("<lang>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'p':
                    tmp=xml_GetParam("<publisher>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'y':
                    tmp=xml_GetParam("<year>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;
                case 'i':
                    tmp=xml_GetParam("<isbn>",book);
                    strcat(newnamet,tmp);
                    delete[] tmp;
                    break;

            }
        }
    }
    strcat(newname,newnamet);
    strcat(newname,".fb2");
    if(strcmp(newname,oldname)==0){
        if(Oind){cout<<"Имена одинаковы:"<<getFilename(oldname)<<endl;}
        nr++;
        delete[] newname;
        delete[] newnamet;
        return false;
    }
    if(fileexist(newname)){
        if(!Onoerr){cout<<"Ошибка: файл "<<newname<<" уже существует"<<endl;}
        err++;
        delete[] newname;
        delete[] newnamet;
        return false;
    }

    if(Or){cout<<getFilename(oldname)<<" -> "<<getFilename(newname)<<endl;}
    newname=delescape(newname);
    oldname=delescape(oldname);
    char *cmd=new char[1024];
    strcpy(cmd,"mv ");
    strcat(cmd,oldname);
    strcat(cmd," ");
    strcat(cmd,newname);
    system(cmd);
    delete[] cmd;
    delete[] newname;
    delete[] newnamet;
    rn++;
    return true;

}

void printhelp()
{
    cout<<"FB2rename 0.2.5\n"
    "'fb2rn <dir> -P<params> -<options>'\n"
    "Программа предназначена для массового переименования файлов fb2(электронных книг) по виду \"Имя и фамилия автора - Название книги\"(или др.)\n"
    "Нужно задать папку для с книгами, например \"./fb2rn /home/user/books\" или \"fb2rn ~/Книги\\ 2/\"\n"
    "Так же можно задать, как переименовывать файлы например \"серия - название\" или \"Фамилия автора_серия_название\" и так далее\n"
    "Например 'fb2rn -Pf\\ -\\ n(s) ~/books/' файлы будут переименованы как 'фамилия - название(серия).fb2'\n"
    "Параметры переименования(-P<params>)\n"
    " f - фамилия автора\n"
    " n - имя автора\n"
    " t - название книги\n"
    " m - очество автора\n"
    " g - жанр книги\n"
    " l - язык книги\n"
    " p - издатель\n"
    " y - год\n"
    " i - isbn\n"
    "Опции:\n"
    " r -Выводить информацию о переименовании каждого файла\n"
    " e -Не выводить информацию об ошибках\n"
    " i -Выволить информацию о совпадении имён\n";
}

void printshlp(bool v=false)
{
    cout<<"FB2 books renamer 0.2.5\n";
    if(!v)cout<<"Пропущен операнд. Попробуйте fb2rn --help для получения подробной информации\n";
}

int main(int argc, char *argv[])
{
    int rn=0, nr=0, ne=0;
    if(argc>1){
        if(strcmp(argv[1],"--help")==0){
            printhelp();
            return 2;
        }
        if(strcmp(argv[1],"--version")==0){
            printshlp(true);
            return 2;
        }
    }

    char *dir=new char[256];memset(dir,0,256);
    char params[100]={0};
    char options[100]={0};

    bool b=false;
    for(int i=1; i<argc;i++){
        if(argv[i][0]=='/'){
            strcpy(dir,argv[i]);
            b=true;
        }
    }
    char *d=delescape(dir);
    delete []dir;
    dir=d;
        if(!b){
        printshlp();
        delete[]dir;
        return 1;
    }

    for(int i=0; i<argc;i++){
        if((argv[i][0]=='-')&&(argv[i][1]=='P')){
            strcpy(params,argv[i]);
            break;
        }
    }
    for(int i=0; i<argc;i++){
        if((argv[i][0]=='-')&&(argv[i][1]!='P')){
            strcpy(options,argv[i]);
        }
    }

    bool Onoerr=false, Or=false, Oind=false;
    if(strchr(options,'e')){Onoerr=true;}
    if(strchr(options,'i')){Oind=true;}
    if(strchr(options,'r')){Or=true;}

    char *book;
    char cmd[256];memset(cmd,0,256);
    FILE *fr;
    snprintf(cmd, sizeof(cmd), "find %s -type f -name \"*.fb2\"", dir);
    delete[] dir;
    fr=popen(cmd,"r");
    if(fr==NULL)
    {
         perror("Shell execution error");
         return -1;
    }
    char tmp[512];memset(tmp,0,512);
    while(fgets(tmp,sizeof(tmp),fr)!=NULL)
    {
        tmp[strlen(tmp)-1]=0;
        int err=FB2Load(tmp,book);
        if(err!=0){
            if(Onoerr){cout<<"Ошибка код#"<<err<<":"<<getFilename(tmp)<<endl;}
            ne++;
            continue;
        }
       procfile(tmp,book,params,Or,Oind,Onoerr,ne,nr,rn);
       delete[] book;
    }
    pclose(fr);
    cout<<"Переимновано:"<<rn<<" Совпадающие имена:"<<nr<<" Ошибка:"<<ne<<endl;
    return 0;
}
