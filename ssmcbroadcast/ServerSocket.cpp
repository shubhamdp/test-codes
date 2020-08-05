#include"ServerSocket.h"

void ServerSocket :: error(const char *msg){
    perror(msg);
    exit(1);
}

ServerSocket :: ServerSocket(int port){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)     error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    if( listen(sockfd,5) < 0) error("Error while listining");
    cout<<"server in listen mode..."<<endl;
}

ServerSocket :: ~ServerSocket(){
	close(newsockfd);
    close(sockfd);
}
int ServerSocket :: acceptClient(){
	clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)     return 0;
    return newsockfd;
}

int ServerSocket :: getSsock(){
    return sockfd;
}


int ServerSocket :: getClientSock(){
    return newsockfd;
}