#include"ClientSocket.h"

void ClientSocket :: error(const char *msg){
    perror(msg);
    exit(0);
}

ClientSocket :: ClientSocket(const char * host ,int port){
	
	portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)		error("ERROR opening socket");
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy( (char *)server->h_addr , (char *)&serv_addr.sin_addr.s_addr , server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) & serv_addr,sizeof(serv_addr)) < 0)		error("ERROR connecting");
    printf("Connected...");
}

ClientSocket :: ~ClientSocket(){
	close(sockfd);
}


const char * ClientSocket :: readData(){
	bzero(buffer , 100);
	n = read(sockfd,buffer,100);
    if (n < 0) error("ERROR reading from socket");
    return buffer;
    
}


void ClientSocket :: writeData(char str[100]){
    n = write(sockfd , str , 100);
 	if(n < 0)	error("Error writing to socket");

}
