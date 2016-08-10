// this is nash = nilanjana's bash B)
#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF 500
using namespace std;
char* cmdlist[20];//i am limiting the number of arguments to 20 
char* cmdname;
int numargs;

void readcmd();

int main()
{
    int dummy;
    int mychild=1;//arbit value

    while(true)
    {
        if(mychild>0)// we're in parent
        {
                        
            printf("entered parent %d ", getpid()); fflush(stdout);
            readcmd();
            cmdname=cmdlist[0];

            if(cmdname && strcmp(cmdname,"exit")==0)
                exit(EXIT_SUCCESS);
                
            mychild=fork();
            wait();
            printf("Leaving parent %d\n",getpid()); fflush(stdout);
        }
        
        else if(mychild==0)
        {
            printf("child %d\n",getpid());fflush(stdout);
            execvp(cmdname,cmdlist);
            //if process reaches this place, it means execvp failed

            printf("Command not found \n");
            break;
        }
        else //(whereamI<0)
        {
            printf("fork failed , exiting process :( \n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

void readcmd()//reads a line of input from stdin
{
    string str;
    getline(cin,str);
    char *strc =(char*) malloc(str.size()+1);
    strcpy(strc,str.c_str());
    char *rest=strc;
    char *x; 

    x=strtok_r(rest," ",&rest);
    
    numargs=0;
    
    while(x!=NULL)   
    {
        cmdlist[numargs]= (char*) malloc(strlen(x)+1);
        strcpy(cmdlist[numargs],x);
        x=strtok_r(rest," ",&rest);

        numargs++;
    }    

    cmdlist[numargs]=NULL;
    
}
