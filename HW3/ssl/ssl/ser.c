//
//  ser.c
//  ssl
//
//  Created by yuejing zhu on 2018/3/27.
//  Copyright © 2018年 yuejing. All rights reserved.
//

#include <stdio.h>
#include<netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char **argv){
    int listenfd,connfd;
    socklen_t  clilen;
    struct sockaddr_in servaddr, cliaddr;
    char buff[100];
    
    
     /* Create a TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* Initialize server's address and well-known port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(9311);   /* daytime server */
    
    /* Bind server’s address and port to the socket */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* Convert socket to a listening socket – max 100 pending clients*/
    listen(listenfd,100);
    
    while (1) {
        /* Wait for client connections and accept them */
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        
         /* Write to socket */
        write(connfd, buff, strlen(buff));
        
        /* reading command */
        ssize_t read_n;
        char cmd[256];
        while ((read_n = read(connfd, cmd, 256))>=0) {
            if (read_n == 0) {
                perror("connect failed");
                close(connfd);
                exit(1);
            }else{
                cmd[read_n] = '\0';
                printf("%s",cmd);
                
                char *argv[20];
                
            }
        }
    }
    
    
    
    
    
    
    
    
}
