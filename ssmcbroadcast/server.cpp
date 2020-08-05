#include"ServerSocket.h"

vector<int> client;
vector<string> clientName;

void process(int csock){
  //cout<<"sock: "<<csock;
  char buf[100];
  char name[100];
  int n;
  client.push_back(csock);    

  //read name
	n = read(csock , name , 100);
  if(n < 0) perror("Error reading to socket");
  clientName.push_back(name);

  cout<<"Conected user: "<<name<<"With sock id: "<<csock<<endl;

  //echoing name to client
  n = write(csock , name , 100);
  if(n < 0) perror("Error writing to socket");
  
  //broadcasting that user connected
  for(int i = 0 ; i < client.size(); i++){

    if(client[i] == csock)  continue;
    n = write(client[i] , name , 100);
    if(n < 0) perror("Error writing to socket");

    n = write(client[i] ,"connected\n" , 100);
    if(n < 0) perror("Error writing to socket");
  }

  while(1){ 
    int sock_index;
    bzero(buf,100);    
    n = read(csock , buf , 100);
    if(n < 0) perror("Error reading to socket");
/*    
//if received a send connnected users
    if(*buf == 'a'){
      char tmpbuf[100];
      bzero(tmpbuf,100);
      for(int i = 0 ; i < client.size(); i++){
        int g=0;
        while(clientName[i][g] != '\0'){
          tmpbuf[g] = clientName[i][g];g++;
        }
        n = write(csock , tmpbuf , 100);
        if(n < 0) perror("Error writing to socket");
      }
      continue;
    }
*/
    for(int i = 0 ; i < client.size() ; i++){
      //cout<<client[i];
      if(csock == client[i]){ sock_index=i;  continue;}

      //sendin name
      n = write(client[i] , name , 100);
      if(n < 0) perror("Error writing to socket");

      //sending msg
      n = write(client[i] , buf , 100);
      if(n < 0) perror("Error writing to socket");

    }
     //wants to leave
    if(*buf == 'x'){
      client.erase(client.begin() + sock_index);
      clientName.erase(clientName.begin() + sock_index);
      close(csock);
      cout<<"Disconnected :"<<csock<<endl;
      pthread_exit(0);
    }
    bzero(buf,100);
  }
}


int main(int argc, char *argv[]){

  //check for proper arguments
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
    }
	//making server socket
  ServerSocket ss(atoi(argv[1]));
	//ready to accept client
  
  while(1){
    int csock = ss.acceptClient();
    //cout<<"sock in main:"<<csock;
    if(csock == 0)  perror("unable to oaccept incoming client");
    thread th(&process , csock);
    th.detach();
  }

  return 0;
}