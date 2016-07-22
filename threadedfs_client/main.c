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
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "struct_msg.h"
#define MAXSIZE 1024
#define MAXLINE 80
#define FILEPERM S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH|S_IRGRP

int serverfifo;
int clientfifo;
int dummy;
int server_pid;
pid_t client_pid;
int userid;
char  path_to_server[MAXSIZE];
char path_to_client[MAXSIZE];
char  pwd[MAXSIZE];
char buff[1024];

//typedef struct instruction
//{
//    int instruct_code;
//    int userid;
//    char pwd[1024];
//
//};

MSGP allot_msg()
{
    MSGP temp;
    
    if((temp=(MSGP)malloc(sizeof (MSG)))!=NULL)
        return temp;
    else
        return NULL;
    
}



SMSGP allot_smsg()
{
    SMSGP temp;
    
    if((temp=(SMSGP)malloc(sizeof (SMSG)))!=NULL)
        return temp;
    else
        return NULL;
    
}

void printmsg()
{
    SMSGP temp;
    
    temp=allot_smsg();
    
    if(temp!=NULL)
    {
    
    clientfifo=open(path_to_client,O_RDONLY);
    //dummy=open(path_to_client,O_WRONLY);
    
        do
        {
            
            read(clientfifo,temp,sizeof(temp)); 
            printf("Message ID:%d Is More :%d %s\n",temp->msg_id, temp->more,temp->msg_body);
            
            close(clientfifo);
        }
        while(temp->more);
        
        free(temp);
        
    }
    else
        printf("Problem with printmsg\n");
    

}



void setuserid()
{
    printf("Enter the user ID for filesystem access:");
    scanf("%d",&userid);
    strcpy(pwd,"/");
    
}

void printpwd()
{
    int choice;
    
    MSGP temp;
    
    
    printf("Present working directory of user id %d: %s\n",userid,pwd);
    printf("Want to see list?\n1.Yes\n2.No\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        temp=allot_msg();
        if(temp!=NULL)
        {
            temp->instruct_code=2;
            temp->userid=userid;
            strcpy(temp->pwd,pwd);
            temp->client_pid=client_pid;

        
            write(serverfifo,temp,sizeof(MSG));
            free(temp);
            printmsg();
        }
        else
            printf("instruction can not be sent\n");
    }

    
}

void changedir()
{
    char buff[1024];
    char dirname[256];
    printf("Enter the directory name:");
    getchar();
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d \"%s/%s\" %d",3,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
}

void makedir()
{
    char dirname[256];
    printf("Enter the name of new directory to make:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",4,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    

}

void removedir()
{
    char dirname[256];
    printf("Enter the name of new directory to remove:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",5,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
    
}

void changeown()
{
    char dirname[256];
    printf("Enter the name of file or directory to change ownership:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",6,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
    
}

void createfile()
{
    char dirname[256];
    printf("Enter the name of file to create:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",7,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
    
}

void rename_copy_fd()
{
    char dirname[256];
    printf("Enter the name of file of directory to rename:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",9,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
    
}

void deletefile()
{
    char dirname[256];
    printf("Enter the name of file  to delete:");
    scanf("%[^\n]s",dirname);
    
    sprintf(buff,"%d %d %s/%s %d",8,userid,pwd,dirname,client_pid);
    write(serverfifo,buff,MAXLINE);
    
    printmsg();
    
    
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
            case 5:
                removedir();
                break;
            case 6:
                changeown();
                break;
            case 7:
                createfile();
                break;
            case 8:
                rename_copy_fd();
                break;
            case 9:
                deletefile();
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
        sprintf(path_to_server,"/tmp/server");
        if(!access(path_to_server, F_OK))
        {
            serverfifo=open(path_to_server,O_WRONLY);
            
            //write(serverfifo,"Okay Client 2 is speaking\n",MAXLINE);
            
            sprintf(path_to_client,"/tmp/client.%d",client_pid);
            mkfifo(path_to_client, FILEPERM);
            
            
            menu();
            close(serverfifo);
            close(clientfifo);
            unlink(path_to_client);
        }
        else
        {
            printf("Server does not exist.\n");
        }
        
    }
    return 0;
}
