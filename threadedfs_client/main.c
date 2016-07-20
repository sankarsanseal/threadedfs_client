//
//  main.c
//  threadedfs_client
//
//  Created by Sankarsan Seal on 20/07/16.
//  Copyright © 2016 Sankarsan Seal. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int serverfifo;
int clientfifo;
int server_pid;
int client_pid;
int userid;
char  path_to_server[1024];
char  pwd[1024];

typedef struct instruction
{
    int instruct_code;
    int userid;
    char pwd[1024];
    
};


void setuserid()
{
    printf("Enter the user ID for filesystem access:");
    scanf("%d",&userid);
    strcpy(pwd,"/");
    
}

void printpwd()
{
    int choice;
    printf("Present working directory of user id %d: %s\n",userid,pwd);
    printf("Want to see list?\n1.Yes\n2.No\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        int
        write(serverfifo,
    }
}

void changedir()
{
    char dirname[256];
    printf("Enter the directory name:");
    scanf("%[^\n]s",dirname);
    write(
    
}

void makedir()
{
    char dirname[256];
    printf("Enter the name of new directory:");
    scanf("%[^\n]s",dirname);
}



void menu()
{
    
    int c=1;
    while(c!=0)
    {
        printf("1.Enter the User ID\n");
        printf("2.Preset Working Directory(pwd)\n");
        printf("3.Change directory(chdir)\n");
        printf("4.Make Directory(mkdir)\n");
        printf("5.Remove Directory(rmdir)\n");
        printf("6.Change Owner(chown)\n");
        printf("7.Create File(touch)\n");
        printf("8.Rename Directory or File\n");
        printf("9.Delete File(rm)\n");
        printf("0.For exit the client.\n");
        printf("Enter your choice:");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                setuserid();
                break;
            case 2:
                printpwd();
                break;
            case 3:
                changedir();
                break;
            case 4:
                makedir();
                break;
                
            case 0:
                printf("Exiting...\n");
                
                
                
        }
    }
        
}

int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc!=2)
    {
        printf("usage:%s <server_pid>", argv[0]);
        return 0;
    }
    else
    {
        client_pid=getpid();
        server_pid=atoi(argv[1]);
        sprintf(path_to_server,"/tmp/server.%d",server_pid);
        if(!access(path_to_server, F_OK))
        {
            menu();
        }
        else
        {
            printf("Server does not exist.\n");
        }
        
    }
    return 0;
}
