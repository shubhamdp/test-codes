#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
using namespace std;

class ServerSocket{
public:
	int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[100];
    struct sockaddr_in serv_addr, cli_addr;

    int getClientSock();
    int getSsock();
    ServerSocket(int);
    ~ServerSocket();
    void error(const char *);
    int acceptClient();
};
