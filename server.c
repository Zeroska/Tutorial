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
#define CONNECTION_QUEUE 10

int main(void)
{
    int connfd, listenfd;
  
    struct sockaddr_in serverAddr;
    socklen_t len = sizeof serverAddr;
    
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Something is wrong and need to be fix socket()\n");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr, 0, sizeof serverAddr);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd,(struct sockaddr*)&serverAddr,sizeof serverAddr) < 0){
        fprintf(stderr, "Something wrong in the bind()");
        exit(EXIT_FAILURE);
    }

    if(listen(listenfd,CONNECTION_QUEUE)< 0){
        fprintf(stderr, "Something wrong in the listen()");
        exit(EXIT_FAILURE);
    }

    if((connfd = accept(listenfd, (struct sockaddr*)&serverAddr, &len)) < 0){
        fprintf(stderr,"Something wrong in the accept()\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        //this is stuck right here because of signale 
        int n = 0;  
        char buffer[MAX_BUF] = {0};
        n = recv(connfd,buffer,MAX_BUF,0);
        printf("bytes %d\n", n);
        sscanf(buffer,"%s",buffer);
        printf("a client said: %s\n",buffer);
        //sleep 1 second
        send(connfd, buffer,MAX_BUF,0);
        printf("Echo back: %s\n",buffer);
    }
    return EXIT_SUCCESS;
    //Client jobs
}