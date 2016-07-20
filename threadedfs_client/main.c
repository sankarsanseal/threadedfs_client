//
//  main.c
//  threadedfs_client
//
//  Created by Sankarsan Seal on 20/07/16.
//  Copyright © 2016 Sankarsan Seal. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    int serverfifo;
    int clientfifo;
    int server_id
    int client_pid;
    char * path_to_server[1024];
    
    if(argc!=2)
    {
        printf("usage:%s <server_pid>");
        return 0;
    }
    else
    {
        client_pid=getpid();
        sprintf(path_to_server,"/tmp/server.%d",);
        if(!access(path_to_server))
        {
            
        }
        else
        {
            printf("Server does not")
        }
        
    }
    return 0;
}
