#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "functions.h"
#include "FB2.h"

_Bool procfile(char* oldname, char *book, char *params, _Bool Or,_Bool Oind, _Bool Onoerr,int par[3])
{
    char tags[13]="nftmglpyi";
    char *newname=(char *)malloc(sizeof(char)*(256*2+20));
    char *newnamet=(char *)malloc(sizeof(char)*(256));
    memset(newnamet,0,256);
    int y=0;
    int l=strlen(params);
    if(l==0){
        strcpy(params,"n f - t");
        l=strlen(params);
    }
    char *tmp=getFilepath_fromFullname(oldname);
    strcpy(newname,tmp);
    free(tmp);
    tmp=NULL;
    for(int i=0;i<l;i++){
        if(strchr(tags,params[i])==NULL){
            y=strlen(newnamet);
            newnamet[y]=params[i];
        }
        else{
            switch(params[i]){
            case 'n':
                tmp=xml_GetParam("<first-name>",book);
                break;
            case 'f':
                tmp=xml_GetParam("<last-name>",book);
                break;
            case 't':
                tmp=xml_GetParam("<book-title>",book);
                break;
            case 'm':
                tmp=xml_GetParam("<middle-name>",book);
                break;
            case 'g':
                tmp=xml_GetParam("<genre>",book);
                break;
            case 'l':
                tmp=xml_GetParam("<lang>",book);
                break;
            case 'p':
                tmp=xml_GetParam("<publisher>",book);
                break;
            case 'y':
                tmp=xml_GetParam("<year>",book);
                break;
            case 'i':
                tmp=xml_GetParam("<isbn>",book);
                break;
            }
            if(tmp!=NULL){
                strcat(newnamet,tmp);
                free(tmp);
            }
        }
    }
    strcat(newname,newnamet);
    strcat(newname,".fb2");
    if(strcmp(newname,oldname)==0){
        if(Oind)
            printf("Имена одинаковы:%s\n",getFilename_fromFullname(oldname));
        par[1]++;
        free(newname);
        free(newnamet);
        return 0;
    }
    if(fileexist(newname)){
        if(!Onoerr)
            printf("Ошибка: файл %s уже существует\n",newname);
        par[0]++;
        free(newname);
        free(newnamet);
        return 0;
    }
    if(Or){
        printf("%s -> %s\n",getFilename_fromFullname(oldname),getFilename_fromFullname(newname));
    }
    newname=delescape(newname,1);
    oldname=delescape(oldname,1);
    char *cmd=(char *)malloc(sizeof(char)*(1024));
    strcpy(cmd,"mv ");
    strcat(cmd,oldname);
    strcat(cmd," ");
    strcat(cmd,newname);
    system(cmd);
    free(cmd);
    free(newname);
    free(newnamet);
    par[2]++;
    return 1;

}

void printhelp()
{
    printf("FB2 books renamer\n"
    "'fb2rn [dir] [options] [--mask=mask]'\n"
    "Программа предназначена для массового переименования файлов fb2(электронных книг) по виду"
           "\"Имя и фамилия автора - Название книги\"(или др.)\n"
    "Нужно задать папку для с книгами, например \"fb2rn /home/user/books\" или \"fb2rn .\"\n"
    "Так же можно задать маску для переименовывания файлов по виду \"серия - название\" или \"Фамилия автора_серия_название\" и так далее\n"
    "Например 'fb2rn --mask=f\\ -\\ n(s) ~/books/ -e' файлы будут переименованы как 'фамилия - название(серия).fb2' и не будут выведены ошибки\n"
    "Маска([mask])\n"
    " f - фамилия автора\n"
    " n - имя автора\n"
    " t - название книги\n"
    " m - очество автора\n"
    " g - жанр книги\n"
    " l - язык книги\n"
    " p - издатель\n"
    " y - год\n"
    " i - isbn\n"
    "Аргументы:\n"
    " --help - Вывести эту информацию\n"
    " --version - Вывести версию\n"
    " --renamed-files(-r) -Выводить информацию о переименовании каждого файла\n"
    " --noerror(-e) -Не выводить информацию об ошибках\n"
    " --match-names(-i) -Выволить информацию о совпадении имён\n"
    " --mask(-m) - Маска для переименования файла\n");
}

const struct option long_options[] = {
		{"match-names",no_argument,NULL,'i'},
		{"noerror",no_argument,NULL,'e'},
		{"renamed-files",no_argument,NULL,'r'},
		{"help",no_argument,NULL,'h'},
		{"version",no_argument,NULL,'v'},
		{"mask",required_argument,NULL,'m'},
		{"filter",required_argument,NULL,'m'},
		{NULL,0,NULL,0}
	};

int main(int argc, char *argv[])
{
    _Bool Onoerr=0, Or=0, Oind=0;
    char mask[100]={0};
    char findfilter[100];
    strcpy(findfilter,"*.fb2");
    char c;
    int option_index;
    while ((c = getopt_long (argc, argv, "eirf", long_options, &option_index))!=-1){
        switch(c){
        case 'h':
            printhelp();
            return 0;
        case 'v':
            printf("FB2 books renamer 0.3.0\n");
            return 0;
        case 'e':
            Onoerr=1;
            break;
        case 'r':
            Or=1;
            break;
        case 'i':
            Oind=1;
            break;
        case 'm':
            strcpy(mask,optarg);
            break;
        case 'd':
            strcpy(findfilter,optarg);
            break;
        default:
            fprintf (stderr, ("Try '%s --help' for more information.\n"), "fb2rn");
            return 0;
        }
    }
    char *dir=(char *)malloc(sizeof(char)*(256));
    memset(dir,0,256);
    _Bool b=0;
    for(int i=1; i<argc;i++){
        if(argv[i][0]=='/' || argv[i][0]=='.'){
            strcpy(dir,argv[i]);
            b=1;
        }
    }
    char *d=delescape(dir,1);
    free(dir);
    dir=d;
        if(!b){
        fprintf (stderr, ("Try '%s --help' for more information.\n"), "fb2rn");
        return 0;
    }
    char *book;
    char cmd[256];
    memset(cmd,0,256);
    FILE *fr;
    snprintf(cmd, sizeof(cmd), "find %s -type f -name \"*.fb2\"", dir);
    free(dir);
    int par[3]={0,0,0};
    fr=popen(cmd,"r");
    if(fr==NULL)
    {
         perror("Shell execution error");
         return -1;
    }
    char tmp[512];
    memset(tmp,0,512);
    while(fgets(tmp,sizeof(tmp),fr)!=NULL)
    {
        tmp[strlen(tmp)-1]=0;
        int err=FB2Load(tmp,&book);
        if(err!=0){
            if(Onoerr){
                printf("Error #,%d:%s\n",err,getFilename_fromFullname(tmp));
            }
            par[0]++;
            continue;
        }
        procfile(tmp,book,mask,Or,Oind,Onoerr,par);
        free(book);
    }
    pclose(fr);
    printf("Renamed:%d Matching names:%d Failed:%d\n",par[2],par[1],par[0]);
    return 0;
}
