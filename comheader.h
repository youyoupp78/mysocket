#pragma once
#include <stdio.h>
#include <time.h>

#define ERROR_PRINT(fmt,args...)  {printf(fmt,##args);}
#define DEBUG_PRINT(fmt,args...)  {printf(fmt,##args);}
#define NORMAL_PRINT(s) 

#define WRITE_LOG(buf,str) \
        int ibuflen =sizeof(buf) \
        snprintf(buf,sizeof(buf),"(%s,%d):%s",__FILE__,__LINE__,buf);\
        printf("%s\n",buff);


#define  MAXSLEEP  5
#define  MAXBUFFLEN  1024
#define  LISTENMAXNUM  10

enum SERTYPE
{
    SERFLAG = 0,
	CLIFLAG = 1,

};



struct mysock
{
	int fd;
	int port;
	int flag;
};