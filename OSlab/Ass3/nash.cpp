// this is nash = nilanjana's bash B)
#include <bits/stdc++.h>
#include <sys/wait.h>// this line is really important.. otherwise u ll end up calling the wrong wait and debug foolishly for an hour -_-
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF 500
using namespace std;
char* cmdlist[20];//i am limiting the number of arguments to 20 
char* cmdname;
int numargs;
bool readcmd();//returns whether the process is to be run in background or not

int main()
{
    int dummy=0;
    int mychild=1;//arbit value

    while(true)
    {
                    
        printf("$ "); fflush(stdout);
        bool bg=readcmd();
//        printf(" bg = %d \n ",bg);fflush(stdout);
        cmdname=cmdlist[0];

        if(cmdname && strcmp(cmdname,"exit")==0)
            exit(EXIT_SUCCESS);
            
        mychild=fork();
        if(mychild==0)
        {
            execvp(cmdname,cmdlist);
            //if process reaches this place, it means execvp failed

            printf("Command not found \n");fflush(stdout);
            exit(EXIT_SUCCESS);
        }
        else if(mychild<0)
        {
            printf("forking failed\n");
            exit(EXIT_FAILURE);
        }
        
        if(!bg) wait(&dummy);
        //printf("wait completed ");fflush(stdout);
                


        
    }

    exit(EXIT_SUCCESS);
}

bool readcmd()//reads a line of input from stdin
{
    string str;
    getline(cin,str);
    char *strc =(char*) malloc(str.size()+1);
    strcpy(strc,str.c_str());
    char *rest=strc;
    char *x; 

    x=strtok_r(rest," ",&rest);
    
    numargs=0;
    bool background=false;
    while(x!=NULL)   
    {
        if(strcmp(x,"&")==0)
        {
            //this means background process
            background=true;
            break;
        }
        cmdlist[numargs]= (char*) malloc(strlen(x)+1);
        strcpy(cmdlist[numargs],x);
        x=strtok_r(rest," ",&rest);

        numargs++;
    }    

    cmdlist[numargs]=NULL;
    return background;
}
