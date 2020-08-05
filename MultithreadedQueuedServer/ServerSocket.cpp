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

    listen(sockfd,5);
    cout<<"server in listen mode..."<<endl;
}

ServerSocket :: ~ServerSocket(){
	close(newsockfd);
    close(sockfd);
}
void ServerSocket :: acceptClient(){
	clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)     error("ERROR on accept");
}

const char * ServerSocket :: readData(){
	bzero(buffer , 100);
	n = read(newsockfd,buffer,100);
    if (n < 0) error("ERROR reading from socket");
    return buffer;
    
}


void ServerSocket :: writeData(char str[100]){
    n = write(newsockfd , str , 100);
 	if(n < 0)	error("Error writing to socket");

}
