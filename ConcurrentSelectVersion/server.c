#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


#define PORT 1337
#define MAX_BUF 1024
#define CONNECTION_QUEUE 10


void serverHanlder(int,char*);
void serverInit();

//this code lack of signal handling 
int main(void)
{
    int connfd, listenfd,connfd2, recieveBytes;
    struct sockaddr_in serverAddr;
    socklen_t len = sizeof serverAddr;
    struct sockaddr_storage remoteAddr;
    struct timeval tv; //time value
    int fdmax;
    int addrlen;
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    //this is where you set your fd_set
    fd_set read_fds;
    fd_set master;
    FD_ZERO(&read_fds);
    FD_ZERO(&master);
    //add socket to the fd_set
    FD_SET(connfd,&master);
    FD_SET(listenfd,&master);
    FD_SET(connfd2,&master);
   
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
    //sometimes I read this and I got STD
    while(1){
        //need to block until the socket is available.
        int n  = 0;
        read_fds = master;
        if((n = select(FD_SETSIZE + 1, &read_fds,NULL, NULL, &tv)) == -1){
            fprintf(stderr,"Something wrong with the select()");
            exit(EXIT_FAILURE);
        }

        printf("select() return %d\n",n);
        for(int i = 0; i< FD_SETSIZE; i++){
            if(FD_ISSET(i,&read_fds))
            {// what is FD_ISSET return
                if(i == listenfd){
                    addrlen = sizeof remoteAddr;
                    //after accept the socket
                    if((connfd = accept(listenfd, (struct sockaddr*)&serverAddr, &len)) < 0){
                        fprintf(stderr,"Something wrong in the accept()\n");
                        exit(EXIT_FAILURE);
                    }else{
                        FD_SET(connfd,&master);
                        if(connfd > FD_SETSIZE){
                            //if
                        }
                    }
                }
            }
        }

        if((connfd = accept(listenfd, (struct sockaddr*)&serverAddr, &len)) < 0){
            fprintf(stderr,"Something wrong in the accept()\n");
            exit(EXIT_FAILURE);
        }
        //this is stuck right here because of signal 
        char buffer[MAX_BUF] = {0};
        recieveBytes = recv(connfd,buffer,MAX_BUF,0);//connfd is just a number
        //print out the bytes the client sent
        printf("bytes client sent %d\n",recieveBytes);
        if(recieveBytes == 0){
            printf("Connection is close\n");
        }
        sscanf(buffer,"%s",buffer);
        printf("a client said: %s\n",buffer);
        //sleep 1 second
        send(connfd, buffer,MAX_BUF,0);
        printf("Echo back: %s\n",buffer);
    }
    return EXIT_SUCCESS;
    //Client jobs
}


void serverInit(){

}

void serverHandler(int sockfd, char buffer[]){
    printf("[*] Server handle take place\n");
    
}