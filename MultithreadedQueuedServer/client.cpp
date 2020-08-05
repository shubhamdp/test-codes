#include"ClientSocket.h"


int main(int argc, char *argv[]){
//1 for int
//2 for float
//3 for char
    int type,size;
    char buffer[100];
    //creating list
    
    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);

    }
	//opening socket
    ClientSocket cs(argv[1] , atoi(argv[2]) );
    //opening file
    ifstream file (argv[3]);
    //reading type and size
    file>>type;
    file>>size;

//writing type
	bzero(buffer , 100);
    sprintf (buffer, "%d", type);
	cs.writeData(buffer);

//sending size
    bzero(buffer , 100);
    sprintf( buffer, "%d",size);
    cs.writeData(buffer);

//for int
    if(type == 1){
    	int a;
    	List<int> *list = new List<int>();
	    while(file>>a)  list->insertLast(a);

		cout<<"Before sort:\n";
    	list->printList();
		Node<int> * tmp = list -> head;
    	while(tmp != NULL){
        	bzero(buffer , 100);
        	sprintf ( buffer, "%d", tmp->getData() );
        	cs.writeData(buffer);
        	tmp = tmp->getNext();
    	}
    	tmp = list -> head;
    	while(size-- > 0 ){
		    const char * str;
    	    int x ;
    	
        	bzero(buffer,100);      
        	str = cs.readData();
        	sscanf(str , "%d" , &x);
	        tmp -> setData(x);
    	    tmp = tmp -> getNext();
    	}
   	 	cout<<"\n\nafter sort: \n";
    	list->printList();
    }

//for float
    if(type == 2){
    	cout<<"\nin float\n";
    	float a;
    	List<float> *list = new List<float>();
	    while(file>>a)  list->insertLast(a);

		cout<<"Before sort:\n";
    	list->printList();
		Node<float> * tmp = list -> head;
    	while(tmp != NULL){
        	bzero(buffer , 100);
        	sprintf ( buffer, "%f", tmp->getData() );
        	cs.writeData(buffer);
        	tmp = tmp->getNext();
    	}
    	tmp = list -> head;
    	while(size-- > 0 ){
		    const char * str;
    	    float x ;
    	
        	bzero(buffer,100);      
        	str = cs.readData();
        	sscanf(str , "%f" , &x);
	        tmp -> setData(x);
    	    tmp = tmp -> getNext();
    	}
   	 	cout<<"\n\nafter sort: \n";
    	list->printList();
    }

//for char
    if(type == 3){
    	cout<<"\nin char\n";
    	char a;
    	List<char> *list = new List<char>();
	    while(file>>a)  list->insertLast(a);

		cout<<"Before sort:\n";
    	list->printList();
		Node<char> * tmp = list -> head;
    	while(tmp != NULL){
        	bzero(buffer , 100);
        	sprintf ( buffer, "%c", tmp->getData() );
        	cs.writeData(buffer);
        	tmp = tmp->getNext();
    	}
    	tmp = list -> head;
    	while(size-- > 0 ){
		    const char * str;
    	    char x ;
    	
        	bzero(buffer,100);      
        	str = cs.readData();
        	sscanf(str , "%c" , &x);
	        tmp -> setData(x);
    	    tmp = tmp -> getNext();
    	}
   	 	cout<<"\n\nafter sort: \n";
    	list->printList();
    }

    return 0;
}
