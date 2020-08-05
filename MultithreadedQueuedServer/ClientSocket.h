#include"GenericList/GenericList.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<sstream>
#include<fstream>

class ClientSocket{
public:
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[100];

	ClientSocket(const char * , int);
	~ClientSocket();
	void error(const char *);
    const char * readData();
    void writeData(char []);


};
