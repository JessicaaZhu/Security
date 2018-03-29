//
//  gen-pass.c
//  ssl
//
//  Created by yuejing zhu on 2018/3/27.
//  Copyright © 2018年 yuejing. All rights reserved.
//

#include "gen-pass.h"
#include <stdio.h>
#include <time.h>
#include <openssl/md5.h>
#include <stdbool.h>

//struct tm *gmtime(const time_t *timep);

char * hashedpass(char * pwd){
    MD5_CTX ctx;
    unsigned char md[16];
    char tmp[3] = {'0'};
    int i;
    
    MD5_Init(&ctx);
    MD5_Update(&ctx, pwd, strlen(pwd));
    MD5_Final(md, &ctx);
    
    char *md5_pass = malloc(1024*sizeof(char));
    memset(md5_pass, 0, 1024);
    for(i = 0; i < 16;i++)
    {
        sprintf(tmp, "%02X", md[i]);
        strcat(md5_pass, tmp);
    }
    return pwd;
}

/*struct tm getime(){
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    printf("%d%d%d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf("%s%d;%d;%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
    return *p;
}
*/
bool verifyid(char * enterid){
    FILE * fpr = fopen("userfile.txt", "rt");
    if(fpr == NULL)
    {
        printf("failed to open the inputfile\n");
        //exit(1);
    }
    //fseek(fpr,0,SEEK_SET);
    char pwdfile[500];
    bool ifexist = false;
    while (!feof(fpr)) {
        fgets(pwdfile, sizeof(pwdfile), fpr);
        char * eid = strtok(pwdfile, "|");
        if (strcmp(enterid,eid)==0){
            printf("The ID exists!");
            ifexist = true;
            break;
        }
    }
    fclose(fpr);
    return ifexist;
}

int main(int argc, char const *argv[]){
    //const char * uid = argv[1];
    //const char * pwd = argv[2];
    //const char * ipname = argv[3];
   // char  pwdfile[500];
    char  enterid[20];
    char  enpwd[20];
    char  sTime[100]={'\0'};
    char  saving[200];
    
    FILE * fpr = fopen("userfile.txt", "rt");
    //fseek(fpr,0,SEEK_SET);
    /*if(fpr == NULL)
    {
        printf("failed to open the inputfile\n");
        //exit(1);
    }*/
    while(1){
    printf("Please enter a ID:\n");
    scanf("%s",enterid);
    bool exist = verifyid(enterid);
    if (exist == true ) {
        printf("The ID %s already exists.",enterid);

    }else{
        fputs(enterid, fpr);
        fputs("|", fpr);
        printf("The ID %s already entered.",enterid);
        printf("Please enter pa:\n");
        scanf("%s",enpwd);
        char * hashpwd = hashedpass(enpwd);
        fputs(hashpwd, fpr);
        fputs("|", fpr);
        time_t ticks = time(NULL);
        snprintf(sTime, sizeof(sTime), "%.24s", ctime(&ticks));
        sprintf(saving, "%s\n",sTime);
        fputs(saving, fpr);
        }
    }
}
