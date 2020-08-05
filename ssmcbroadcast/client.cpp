#include"ClientSocket.h"

void recvProcess(int csock){
	char buf[100];
	int n;
	while(1){
		bzero(buf,100);
		fgets(buf,100,stdin);

		n = write(csock , buf , 100);
      	if(n < 0) perror("Error writing to socket");

		if(*buf == 'x') {close(csock); exit(0);}
		//std::this_thread::sleep_for (std::chrono::seconds(2));
	}
}


int main(int argc, char *argv[]){
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);

    }
    int n;
	char buf[100];
  	char name[100];
    ClientSocket cs(argv[1] , atoi(argv[2]));
    int csock = cs.getSockFD();

	cout<<"\nYour Name: ";
	bzero(buf ,100);
    fgets(buf, 100 ,stdin);

	n = write(csock , buf , 100);
    if(n < 0) perror("Error writing to socket");
//echo from server

	bzero(buf,100);
	n = read(csock , buf , 100);
    if(n < 0) perror("Error reading to socket");
	cout<<"Welcome Aboard: "<<buf;
	cout<<"type --> to send\n'x' --> to leave"<<endl;

//	cout<<"csock main:"<<csock;
	thread th(&recvProcess , csock);
	th.detach();

	while(1){
		//reading name
		bzero(buf,100);
		n = read(csock , name , 100);
	    if(n < 0) perror("Error reading to socket");

	    //reading msg
		bzero(buf,100);
		n = read(csock , buf , 100);
	    if(n < 0) perror("Error reading to socket");
	    
	    if(buf[0] != '\0')	printf("\nFrom %s-> %s\n",name,buf);

//		cout<<buf;
		//std::this_thread::sleep_for (std::chrono::seconds(2));
	}

    return 0;
}