#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 1337
#define MAX_BUF 5000
#define SA struct sockaddr
//prototype
void client_action(int, char*);

//The old style of socket programming

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUF] = {0};
    char recieveBuffer[MAX_BUF] = {0};

    //why we should do alot of handler here
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr,"Something is wrong and need to be fix socket()\n");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr,0,sizeof serverAddr);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //this look scary at first but trust me
    if (connect(sockfd, (struct sockaddr *) &serverAddr,sizeof serverAddr) < 0){
        fprintf(stderr,"Something is wrong and need to be fix connect()\n");
        exit(EXIT_FAILURE);
    }
    //Client jobs
    while(1){
        client_action(sockfd,buffer);
    }

    return EXIT_SUCCESS;
    //after this we will send something to the server to process
}


void client_action(int sockfd, char sendBuffer[]){
    //this thing is fuck
    printf("Type something bro: ");
    fgets(sendBuffer, MAX_BUF, stdin);
    
    send(sockfd,sendBuffer, MAX_BUF, 0);
    bzero(&sendBuffer,sizeof *sendBuffer);
    recv(sockfd, sendBuffer,MAX_BUF,0);
    printf("server respond: %s\n",sendBuffer);
    return;
}