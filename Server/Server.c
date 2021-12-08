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
    int clilen;
    IPC_DATA ipcdata;
    struct sockaddr_un clientaddr, serveraddr;

    unsigned int* DataPtr = NULL; 

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0); 
    if (sockfd < 0)
    {
        perror("socket error : ");
        exit(0);
    }    
    unlink(IPC_PATH);

    memset(&serveraddr, 0x00,sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, IPC_PATH);

    DataPtr = (unsigned int*)(ipcdata.pbuff);

    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("bind error : ");
        exit(0);
    }

    clilen  = sizeof(clientaddr); 

    while(1)
    {
        recvfrom(sockfd, (void *)&ipcdata, sizeof(IPC_DATA), 0, (struct sockaddr *)&clientaddr, &clilen); 
        printf("0x%X, %d, %d\r\n", ipcdata.ipc_type, ipcdata.length, *DataPtr);    
    }

    close(sockfd);
    exit(0);
}
			