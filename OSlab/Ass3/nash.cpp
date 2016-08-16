// this is nash = nilanjana's bash B)
#include <bits/stdc++.h>
#include <sys/wait.h>// this line is really important.. otherwise u ll end up calling the wrong wait and debug foolishly for an hour -_-
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>//for creat
#include <fcntl.h>//for creat
#include <signal.h>
#include <errno.h>

#define BUF 500

using namespace std;
char* cmdlist[20];//i am limiting the number of arguments to 20 
char* cmdname;
char *opfile, *ipfile;
int numargs;
bool inredirect,outredirect,background;
void readcmd();
void initialize();
void sigchild_handler(int signum)
{
//    cout<<"sigchild handler invoked"<<endl;
    while(waitpid(-1,NULL,WNOHANG)>0){}; 
}

int main()
{

    signal(SIGCHLD,sigchild_handler); //installing signal
    int dummy=0;
    int mychild=1;//arbit value

    while(true)
    {
        
        initialize();
        printf("$ "); fflush(stdout);
        readcmd();
        cmdname=cmdlist[0];

        //_______________INTERNAL COMMANDS__________________
        //These are handled by the parent herself.

        if(cmdname && strcmp(cmdname,"exit")==0)
            exit(EXIT_SUCCESS);

        if(cmdname && strcmp(cmdname,"cd")==0 )
        {
            int status = chdir(cmdlist[1]);
            if(status==-1)
            {
                printf("Invalid directory \n");fflush(stdout);
            }
            continue;
        }

        //________________EXTERNAL COMMANDS_________________    
        mychild=fork();
        if(mychild==0)
        {
            if(outredirect)
            {
                int fd1=creat(opfile, 777);
                if(fd1==-1)
                {
                    printf("Invalid file name  \n"); fflush(stdout);
                    exit(EXIT_FAILURE);
                }

                dup2(fd1,1);
                close(fd1);
                //printf("%s\n",opfile);fflush(stdout);
            }
            if(inredirect)
            {
                int fd0=open(ipfile, O_RDONLY);
                if(fd0==-1)
                {
                    printf("Invalid file name  \n"); fflush(stdout);
                    exit(EXIT_FAILURE);
                }

                dup2(fd0,0);
                close(fd0);
                //printf("%s\n",opfile);fflush(stdout);
            }

            execvp(cmdname,cmdlist);
            //if process reaches this place, it means execvp failed

            printf("Command not found \n");fflush(stdout);
            exit(EXIT_FAILURE);
        
        }
        else if(mychild<0)
        {
            printf("forking failed\n");
            exit(EXIT_FAILURE);
        }
        
        if(!background)waitpid(mychild,0,0);    
        //printf("wait completed ");fflush(stdout);
                
        
    }

    exit(EXIT_SUCCESS);
}

void initialize()
{
    opfile=NULL; ipfile=NULL;
    background =false;
    inredirect=false;
    outredirect=false;
}

void readcmd()//reads a line of input from stdin, and sets the flags background , inredirect , outredirect
{
    string str;
    getline(cin,str);
    int i,pos;
    vector<string> symbs;
    symbs.push_back("&");
    symbs.push_back("<");
    symbs.push_back(">");

    
    for(i=0;i<symbs.size();i++)
    {
        pos=str.find(symbs[i]);
        if(pos != string::npos)
        {
            str.replace(pos,1," "+symbs[i]+" ");
        }

    }
       char *strc =(char*) malloc(str.size()+1);
    strcpy(strc,str.c_str());
    char *rest=strc;
    char *x; 
    x=strtok_r(rest," ",&rest);
    
    numargs=0;
    background=false;
    while(x!=NULL)   
    {
       
        if(strcmp(x,">")==0)
        {
            // output redirection !
            outredirect = true;
            x=strtok_r(rest," ",&rest);
            opfile = (char*) malloc(strlen(x) + 1 );
            strcpy(opfile,x);

            x=strtok_r(rest," ",&rest);//set the token for next time .. otherwise same token will be processed again
            continue;
        }
        if(strcmp(x,"<")==0)
        {
            // input redirection !
            inredirect = true;
            x=strtok_r(rest," ",&rest);
            ipfile = (char*) malloc(strlen(x) + 1 );
            strcpy(ipfile,x);

            x=strtok_r(rest," ",&rest);//set the token for next time .. otherwise same token will be processed again
            continue;
        }
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
}

void printcmdlist()
{
  
    int i;
    for(i=0;i<numargs;i++)
        cout<<cmdlist[i]<<" / ";

    cout<<endl;

}
