#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>


#define SERVER_IP "127.0.0.1"
#define PORT "9999"
#define CONNECTION_QUEUE 10
#define MAX_BUF 1024

//Prototype
void * get_sock_address(struct sockaddr *);
void victim_handle(int);

//TODO: should add signal handler
int main(void){

    int connfd, listenfd, bytes;
    struct addrinfo hints, *result, *rp;
    struct sockaddr_storage remoteClient;
    char address[INET6_ADDRSTRLEN];

    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; //should we use TCP or UDP
    hints.ai_flags = AI_PASSIVE;
    printf("Server is setting up\n");
    if ((bytes = getaddrinfo(0, PORT, &hints, &result))< 0){
        //or should I try to retry it or make it do something else
        exit(EXIT_FAILURE);
    }
    printf("CNAME %s\n",result->ai_canonname);

    if((listenfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol))< 0){
        
        exit(EXIT_FAILURE);
    }

    if((bind(listenfd,result->ai_addr,result->ai_addrlen))< 0){
        exit(EXIT_FAILURE);
    }

    if(listen(listenfd, CONNECTION_QUEUE) < 0){
        exit(EXIT_FAILURE);
    }
    //where should I free for the best result
    freeaddrinfo(result);

    socklen_t len = sizeof remoteClient;
    if((connfd = accept(listenfd,(struct sockaddr*)&remoteClient, &len)) < 0){
        exit(EXIT_FAILURE);
    }

    //get the IP address boy
    inet_ntop(remoteClient.ss_family,get_sock_address((struct sockaddr*)&remoteClient), address,sizeof address);
    printf("client %s\n",address);
    printf("SERVER ACTIVE!\n");
    while(1){
        char recvBuffer[MAX_BUF] = {0};
        recv(connfd,recvBuffer, MAX_BUF, 0);
        printf("%s\n",recvBuffer);
        
    }
    return EXIT_SUCCESS;
}


//check whether ipv4 or ipv6 and return its address (sockaddr_in)
void *get_sock_address(struct sockaddr * SA){
    if (SA->sa_family == AF_INET){
        return &(((struct sockaddr_in *)SA)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)SA)->sin6_addr);
}

void victim_handle(int clientfd){
    printf("[*] serve master\n");
    
}