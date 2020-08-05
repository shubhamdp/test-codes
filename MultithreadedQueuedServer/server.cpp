#include"ServerSocket.h"

//sort list
template<typename dataType>
void sortList(Node<dataType> * head){
    cout<<"\nin sort\n";
    Node<dataType> * tmp = head;
    while(tmp->getNext() != NULL){
        Node<dataType> *min = tmp;
        Node<dataType> *tmpNext = tmp->getNext();
        while(tmpNext != NULL){
            if(tmpNext -> getData() < min-> getData() )
                min = tmpNext;
            tmpNext = tmpNext -> getNext();
        }
        dataType x = tmp -> getData();
        tmp -> setData(min -> getData()) ;
        min -> setData(x);

        tmp = tmp->getNext();
        tmpNext = NULL;
        delete tmpNext;
        min = NULL;
        delete min;
    }
    tmp = NULL;
    delete tmp;
}


int main(int argc, char *argv[])
{
//type
// 1 for int
// 2 for float
//3 for char
  
  	//check for proper arguments
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

//variables for type and size
    int type;
    int size;
    char buffer[100];

//making server socket
    ServerSocket ss(atoi(argv[1]));
//ready to accept client
    ss.acceptClient();

//reading type
	const char * str = ss.readData();
	sscanf(str,"%d",&type);

//reading size
	str = ss.readData();
 	sscanf(str,"%d",&size);

//for int
    if( type == 1){
  		List<int> *list = new List<int>();
  		while(size-- > 0){
    		str = ss.readData();
        	int x ;
        	sscanf ( str, "%d", &x );
        	list -> insertLast(x);
    	}
    	//list->printList();
	    sortList(list->head);
	  	//list->printList();
    	
    	Node<int> *tmp = list -> head;
    	//returnig the sorted list
    	while(tmp != NULL){
	        sprintf ( buffer, "%d", tmp->getData() );
    	    ss.writeData(buffer);
        	tmp = tmp->getNext();
    	}
  	}

//for float
  	if( type == 2 ){
  		cout<<"\nin float\n";
  		List<float> *list = new List<float>();
		while(size-- > 0){
    		str = ss.readData();
        	float x ;
        	sscanf ( str, "%f", &x );
        	list -> insertLast(x);
    	}

	    sortList(list->head);
	  
    	Node<float> *tmp = list -> head;
    
    	//returnig the sorted list
    	while(tmp != NULL){
	        sprintf ( buffer, "%f", tmp->getData() );
    	    ss.writeData(buffer);
        	tmp = tmp->getNext();
    	}  		
  	}

//for character
  	if( type == 3 ){
  		cout<<"\nin char\n";
  		List<char> *list = new List<char>();
  		while(size-- > 0){
    		str = ss.readData();
        	char x ;
        	sscanf ( str, "%c", &x );
        	list -> insertLast(x);
    	}

	    sortList(list->head);
	  
    	Node<char> *tmp = list -> head;
    
    	//returnig the sorted list
    	while(tmp != NULL){
	        sprintf ( buffer, "%c", tmp->getData() );
    	    ss.writeData(buffer);
        	tmp = tmp->getNext();
    	}
  	}
    return 0; 
}
