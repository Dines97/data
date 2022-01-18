#include <iostream>
#include <fstream>
using namespace std;

class Node{

    public:
    char data;

    public:
    Node *next = NULL, *previous = NULL;

    Node(char data){this->data = data;}

};

class DoubleLinkedList{

    Node *head = NULL;
    public:

    DoubleLinkedList(){}
    DoubleLinkedList(ifstream *file);
    int getSize();
    bool isEmpty();
    void printList();

    void insertElementAtPosition(Node *node, int position);
    void insertElementAtBegin(Node *node);
    void insertElementAtEnd(Node *node);

    void deleteElementAtPosition(int position);
    void deleteElementAtBegin();
    void deleteElementAtEnd();

    Node* getElementAtPosition(int position);
    Node* getElementAtBegin();
    Node* getElementAtEnd();

};

class Stack{

    DoubleLinkedList doubleLinkedList;

    public:
    void push(char value);
    char pop();

};

class Queue{

    DoubleLinkedList doubleLinkedList;

    public:
    void enQueue(char value);
    char deQueue();

};

bool isDoubleLinkedListPalindrom(DoubleLinkedList doubleLinkedList);

DoubleLinkedList::DoubleLinkedList(ifstream *file){
    char value;

    while(*file>>value){
        Node *node = new Node(value);
        insertElementAtBegin(node);
    }
}


int DoubleLinkedList::getSize(){

    Node *tmp = head;

    if(isEmpty()){
        return 0;
    }

    int i;

    for(i = 1; tmp->next; i++){
        tmp = tmp->next;
    }
    return i;
}

bool DoubleLinkedList::isEmpty(){

    return head==NULL ? true : false; 

}

void DoubleLinkedList::printList(){
    Node *tmp = head;

    if(tmp==NULL){
        cout<<"List is empty";
        return;
    }
    
    while(tmp->next){

        cout<<tmp->data<<", ";
        tmp = tmp->next;

    }
    cout<<tmp->data;

}

void DoubleLinkedList::insertElementAtBegin(Node *node){
    if(!head){
        head = node;
        return;
    }

    node->next = head;
    head->previous = node;
    head = node;

}

void DoubleLinkedList::insertElementAtEnd(Node *node){
    if(!head){
        head = node;
        return;
    }

    Node *tmp = head;
    while(tmp->next){
        tmp = tmp->next;
    }

    tmp->next = node;
    node->previous = tmp;
}

void DoubleLinkedList::insertElementAtPosition(Node *node, int position){
    if(!head){
        head = node;
        return;
    }

    Node *tmp = head;
    for(int i=0; !(!tmp->next || i == position); i++){
        tmp = tmp->next;
    }

    if(tmp->next){
        node->next = tmp->next;
        node->previous = tmp;

        tmp->next->previous = node;
        tmp->next = node;
    }
    else{
        node->previous = tmp;
        tmp->next = node;
    }
}

void DoubleLinkedList::deleteElementAtBegin(){

    if(!head){
        cout<<"List is empty";
        return;
    }

    if(head->next){
        Node *tmp = head;
        head = head->next;
        head->previous = NULL;
        delete tmp;
    }
    else{
        delete head;
        head = NULL;
    }
}

void DoubleLinkedList::deleteElementAtEnd(){

    if(getSize() == 0){
        cout<<"List empty"<<endl;
        return;
    }

    Node *tmp = head;

    if(getSize() == 1){
        delete tmp;
        head = NULL;
        return;
    }

    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->previous->next = NULL;
    delete tmp;

}

void DoubleLinkedList::deleteElementAtPosition(int position){

    Node *tmp = head;

    for(int i = 0; !(!tmp->next || i == position); i++){
        tmp = tmp->next;
    }

    if(tmp->next){
        tmp->previous->next = tmp->next;
        tmp->next->previous = tmp->previous;
        
    }
    else{
        tmp->previous->next = tmp->next;
    }

    delete tmp;

}

Node* DoubleLinkedList::getElementAtBegin(){
    return head;
}

Node* DoubleLinkedList::getElementAtEnd(){
    Node *tmp = head;

    while(tmp->next){
        tmp = tmp->next;
    } 

    return tmp;
}

Node* DoubleLinkedList::getElementAtPosition(int position){
    Node *tmp = head;

    for(int i = 0; !(!tmp->next || i == position); i++){
        tmp = tmp->next;
    }

    return tmp;
}

void Stack::push(char value){
    doubleLinkedList.insertElementAtBegin(new Node(value));
}

char Stack::pop(){
    if(doubleLinkedList.getElementAtBegin()){
        char value = doubleLinkedList.getElementAtBegin()->data;
        doubleLinkedList.deleteElementAtBegin();
        return value;
    }
    else{
        cout<<"Stack empty";
    }
}

void Queue::enQueue(char value){
    doubleLinkedList.insertElementAtBegin(new Node(value));
}

char Queue::deQueue(){
    if(doubleLinkedList.getElementAtEnd()){
        char value = doubleLinkedList.getElementAtEnd()->data;
        doubleLinkedList.deleteElementAtEnd();
        return value;
    }
    else{
        cout<<"Queue empty";
    }
}

bool isDoubleLinkedListPalindrom(DoubleLinkedList doubleLinkedList){

    cout<<"Initial state: ";
    doubleLinkedList.printList();
    cout<<endl;

    bool repaired = false;
    
    for(int i = 0; !(doubleLinkedList.getSize()==0 || doubleLinkedList.getSize()==1);){

        if(doubleLinkedList.getElementAtBegin()->data == doubleLinkedList.getElementAtEnd()->data){
            doubleLinkedList.deleteElementAtBegin();
            doubleLinkedList.deleteElementAtEnd();
            cout<<i+1<<". Step: ";
            doubleLinkedList.printList();
            cout<<endl;
            i++;
        }
        else{

            repaired = true;

            Node *startNode = new Node(doubleLinkedList.getElementAtBegin()->data);
            Node *endNode = new Node(doubleLinkedList.getElementAtEnd()->data);
            
            doubleLinkedList.deleteElementAtBegin();
            cout<<i+1<<". Step: ";
            doubleLinkedList.printList();
            cout<<" ("<<startNode->data<<" has been deleted)";
            cout<<endl;
            i++;

            doubleLinkedList.insertElementAtBegin(endNode); 
            cout<<i+1<<". Step: ";
            doubleLinkedList.printList();
            cout<<" ("<<endNode->data<<" has been inserted at begining)";    
            cout<<endl;
            i++;
        }
    }

    if(!repaired){
        cout<<"Phrase is palindrom "<<endl;
    }
    else{
        cout<<"Phrase is repaired palindrom"<<endl;
    }
}


int main(){

    ifstream *example1 = new ifstream("Example1");
    ifstream *example2 = new ifstream("Example2");
    ifstream *example3 = new ifstream("Example3");

    DoubleLinkedList *listExample1 = new DoubleLinkedList(example1);
    DoubleLinkedList *listExample2 = new DoubleLinkedList(example2);
    DoubleLinkedList *listExample3 = new DoubleLinkedList(example3);

    isDoubleLinkedListPalindrom(*listExample1);
    isDoubleLinkedListPalindrom(*listExample2);
    isDoubleLinkedListPalindrom(*listExample3);

}