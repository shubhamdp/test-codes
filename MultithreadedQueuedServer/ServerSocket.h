#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include"GenericList/GenericList.h"
#include<fstream>

class ServerSocket{
public:
	int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[100];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    ServerSocket(int);
    ~ServerSocket();
    void error(const char *);
    void acceptClient();
    const char * readData();
    void writeData(char []);
};
