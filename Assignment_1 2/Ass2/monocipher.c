//
//  main.c
//  mono
//
//  Created by yuejing zhu on 2018/2/14.
//  Copyright © 2018年 yuejing. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

int strlens(char lis[]){
    int i = 0;
    while(lis[i] != '\0'){
        i++;
    }
    return i;
}

char * encryption(char * inputfile, char * outputfile, char * letter,char * cipher){
    int ptlens = strlens(inputfile);
    for (int i = 0; i < ptlens; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (inputfile[i] == letter[j])
            {
                outputfile[i] = cipher[j];
            }
        }
    }
    outputfile[ptlens] = '\0';
    return outputfile;
}

char * decryption(char * inputfile, char * outputfile, char * letter,char * cipher){
    int ptlens = strlens(outputfile);
    for (int i = 0; i < ptlens; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (outputfile[i] == cipher[j])
            {
                inputfile[i] = letter[j];
            }
        }
    }
    inputfile[ptlens] = '\0';
    return inputfile;
}

int main(int argc, char const *argv[])
{
    char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char cipher[26];
    char c;
    char* ipfname = argv[1];
    char* opfname = argv[2];
    char opf[10000];
    char ipf[10000];
    const char* seed = argv[3];
    const char* mode = argv[4];
    int _seed = atoi(seed);
    int _mode = atoi(mode);
    //int lens = strlens(letter);
    srand((unsigned)_seed);
   
    //cipher
    int k = 0;
    int i = 0;
    while(i < 26)
    {
        c = 'a' + rand()%26;
        for(int j = 0; j < i; j++)
        {
            if(c == cipher[j])
            {
                k += 1;
            }
        }
        if(k != 0)
        {
            k = 0;
        }else{
            cipher[i] = c;
            i++;
        }
    }

    //print letter-cipher
    for (int i = 0; i < 26; ++i)
    {
        printf("%c - %c, ",letter[i], cipher[i]);
    }
    printf("\n");

    //ciphertext
    
    
    if (_mode == 1)
    {
        
        //FILE * fpip = fopen("/Users/yuejingzhu/Desktop/SecurityASSI/input.txt", "rt");
        FILE * fpip = fopen(ipfname, "rt");
        if(fpip == NULL)
        {
            printf("failed to open the inputfile\n");
            exit(1);
        }
        int i = 0;
        while((ipf[i] = fgetc(fpip) )!= EOF){
            
            i++;
         }
       
        ipf[i] = '\0';
        printf("%s\n", ipf);
        
        encryption(ipf, opf, letter, cipher);
        //FILE * fpop = fopen("/Users/yuejingzhu/Desktop/SecurityASSI/output.txt", "wt");
        FILE * fpop = fopen(opfname, "wt");
        if(fpop == NULL)
        {
            printf("failed to open the outputfile\n");
            exit(1);
        }
       
        printf("%s\n", opf);
        fputs(opf,fpop);
        fclose(fpip);
        fclose(fpop);
        
    }else if (_mode == 0)
    {
        
        //FILE * fpop = fopen("/Users/yuejingzhu/Desktop/SecurityASSI/output.txt", "rt");
        FILE * fpop = fopen(opfname, "rt");
        if(fpop == NULL)
        {
            printf("inputfile opening error!\n");
            exit(1);
        }
        int i = 0;
        while((opf[i] = fgetc(fpop) )!= EOF){
            
            i++;
        }
        opf[i] = '\0';
        printf("%s\n", opf);
        
        decryption(ipf, opf, letter, cipher);
        //FILE * fpip = fopen("/Users/yuejingzhu/Desktop/SecurityASSI/input.txt", "wt");
        FILE * fpip = fopen(ipfname, "wt");
        if(fpip == NULL)
        {
            printf("outputfile opening error!\n");
            exit(1);
        }
       
        printf("%s\n", ipf);
        fputs(ipf,fpip);
        fclose(fpip);
        fclose(fpop);
    }else{
        printf("You have to enter 0/1!\n");
    }
    
    
    return 0;
}







