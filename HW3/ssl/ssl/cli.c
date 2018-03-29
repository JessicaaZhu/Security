//
//  cli.c
//  ssl
//
//  Created by yuejing zhu on 2018/3/27.
//  Copyright © 2018年 yuejing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


int main(int argc,char **argv){
    int sockfd;
    ssize_t n;
    char recvline[500];
    struct sockaddr_in servaddr;
    struct hostent *he;
    
    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        perror("gethostbyname");
        exit(2);
    }
    /* Create a TCP socket */
    //#include <sys/socket.h>
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        perror("socket");
        exit(2);
    }
    /* Specify server’s IP address and port */
    bzero(&servaddr, sizeof(servaddr));
    //set the socket address structure 0
    servaddr.sin_family = AF_INET;
    //set the address family to AF_INET(IPV4)
    servaddr.sin_port = htons(9311);
    //set port number
    if (inet_pton(AF_INET, inet_ntoa(*(struct in_addr*)he->h_addr_list[0]), &servaddr.sin_addr)<=0) {
        perror("inet_pton");
        exit(4);
    }
    //set ip address
    /* Connect to the server */
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) {
        perror("connect");
        exit(4);
    }
    
    /* Read and write */
    while(1){
        memset(recvline, 0, 500);
        while ((n = read(sockfd, recvline, 500)) >= 0) {
            recvline[n] = '\0';
            if (n == 0) {
                close(sockfd);
                exit(1);
            }
            printf("%s",recvline);
            /*write*/
            char cmd[256];
            printf("Enter userID and password:\n");
            fgets(cmd,256,stdin);
            if (strcmp(cmd, "exit\n")==0) {
                close(sockfd);
                exit(0);
            }
            write(sockfd, cmd, strlen(cmd));
        }
        if (n < 0) { perror("read"); exit(5); }
    }
    
    
    
    
    
    
    
    
}
