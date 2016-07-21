//
//  struct_msg.h
//  threadedfs_client
//
//  Created by Sankarsan Seal on 21/07/16.
//  Copyright © 2016 Sankarsan Seal. All rights reserved.
//

#ifndef struct_msg_h
#define struct_msg_h

typedef struct msg_block
{
    int instruct_code;
    int userid;
    char pwd[1024];
    pid_t client_pid;
    
} * MSGP, MSG;

typedef struct server_msg
{
    int msg_id;
    /*
     msg_id==1  usual message
     msg_id==2  error
     
     */
    int more;
    /*
     more==1 message is bigger than 1024 character
     
     */
    char msg_body[1024];
    
} * SMSGP, SMSG;

#endif /* struct_msg_h */
