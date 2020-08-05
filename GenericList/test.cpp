#include"GenericList.h"

int main(){
List<int> *list = new List<int>();
cout<<"Size: "<<list->size()<<endl;
list->insertStart(5);
list->insertLast(15);
cout<<"Size: "<<list->size()<<endl;
list->insertLast(23);
list->insertAt(44,2);
list->insertAt(144,0);
list->insertAt(441,list->size());

cout<<"found at "<<list->search(5)<<endl;
cout<<"found at "<<list->search(524)<<endl;

list->printList();
list->removeStart();
list->removeStart();
list->removeLast();
cout<<"Size: "<<list->size()<<endl;
list->remove(2);
list->remove(3);
list->remove(2);
list->printList();
cout<<"Size: "<<list->size()<<endl;
cout<<endl;



List<float> *list_float = new List<float>();
cout<<"Size: "<<list_float->size()<<endl;
list_float ->insertLast(4.6);
list_float ->insertStart(44.6);
cout<<"Size: "<<list_float -> size()<<endl;
list_float ->insertStart(4.56);
list_float ->insertLast(43.6);
list_float ->remove(2);
list_float ->insertLast(14.6);
list_float ->printList();
cout<<"Size: "<<list_float->size()<<endl;
cout<<endl;

List<char> *list_char= new List<char>();
list_char ->insertLast('a');
list_char ->insertLast('b');
list_char ->insertLast('d');
list_char ->insertLast('f');
list_char ->insertLast('e');
list_char ->printList();
cout<<endl;

List<double> *list_double = new List<double>();
list_double ->insertLast(60.24);
list_double ->insertLast(4.20);
list_double ->insertLast(458.02);
list_double ->insertLast(4.36);
list_double ->insertLast(58.31);
list_double ->printList();
cout<<endl;


delete list;
delete list_char;
delete list_double;

return 0;
}
