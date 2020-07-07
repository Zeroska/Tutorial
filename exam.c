#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 1337
#define MAX_BUF 1024
#define SA struct sockaddr
//prototype
void client_action(int, char*);

//The old style of socket programming

int main(int number, char *khuong[])
{
    printf("number: %s\n",khuong[0]);
    printf("number: %s\n",khuong[2]);
    printf("so bien truyen vo %d", number);
}