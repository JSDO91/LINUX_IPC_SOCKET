#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define IPC_PATH "../ipc_test"
#define MASK_UINT   0xFFFFFFFF

typedef struct ipc_data
{
    int ipc_type;
    int length;
    unsigned char pbuff[256];
}IPC_DATA;

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_un serveraddr;
    int  clilen;
    IPC_DATA ipcdata;
    unsigned int* DataPtr = NULL; 

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0); 
    if (sockfd < 0)
    {
        perror("exit : ");
        exit(0);
    }

    memset(&serveraddr, 0x00,sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, IPC_PATH);
    clilen = sizeof(serveraddr);

    ipcdata.ipc_type    = 0x3F20;
    ipcdata.length      = 0xF;
    DataPtr             = (unsigned int*)(ipcdata.pbuff);       

    while(1)
    {
        if (sendto(sockfd, (void *)&ipcdata, sizeof(IPC_DATA), 0, (struct sockaddr *)&serveraddr, clilen) < 0)
        {
            perror("send error : ");
            exit(0);
        }
        (*DataPtr)++;
        *DataPtr = (*DataPtr)&MASK_UINT;

        sleep(5);
    }

    close(sockfd);
    exit(0);
}