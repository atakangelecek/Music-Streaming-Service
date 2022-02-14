#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);
    Node<T> *head;
    int size;
private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    

    
};

template<class T>
LinkedList<T>::LinkedList() {
    head = NULL;
    size = 0;
    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    Node<T> *objcurr = obj.head;
    // Generate node pointers to build our list
    Node<T> *current = NULL;
    Node<T> *previous = NULL;

    // If obj is an empty list
    if (obj.head == NULL) {
        // Then, our list will be an empty list also
        head = NULL;
        size = 0;
    }

    // If obj has only one node
    else if (((obj.head)->next == obj.head) && ((obj.head)->prev == obj.head)) {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Build our single node
        head = new Node<T>((obj.head)->data);

        // Make the connections properly
        // next should look at head
        head->next = head;
        // prev should look at head
        head->prev = head;

        // Finally, set size
        size = 1;
    }

    // If obj has more than one node
    else {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Start building our list
        // Build our first node
        head = new Node<T>((obj.head)->data);

        // Make previous to point our first node
        previous = head;

        // This will traverse both lists
        // The condition here might be while(true) also
        do {

            // If objcurr is looking at the last node in the obj list
            // At this point, previous is looking at the last node of our list, current is NULL
            if (objcurr == (obj.head)->prev) {
                // Make your last connection
                // Connect the last node to the first node
                previous->next = head;
                // Connect the first node to the last node
                head->prev = previous;

                // We finished our mission, so don't continue looping
                break;
            }

            else {
                // Pass objcurr to the next node
                objcurr = objcurr->next;

                // Build a new node at which current is looking, and put the data inside the node pointed by objcurr to this new node
                current = new Node<T>(objcurr->data);

                // Connect the previous node to current node
                previous->next = current;
                // Connect the current node to previouse node
                current->prev = previous;

                // Take a step such that current is NULL and previous is looking at the last generated node
                previous = current;
                current = NULL;
            }
        } while(objcurr != obj.head);

        // Set our size correctly
        size = obj.size;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    int i=1;
    if(head){
        if(head->next == head){
            delete head;
            head = NULL;
        }
        else{
            Node<T> *temp = head;
            while(i<size){
                Node<T> *ptr = temp;
                temp = temp->next;
                delete ptr;
                ptr = NULL;
                i++;
            }
            delete temp;
            temp = NULL;
        }
    }
    else{;}
}
template<class T>
int LinkedList<T>::getSize() const {
    /*Node<T> *temp = head;
    int count = 0;
    if(head){
        count++;
        while(temp->next != head){
            count++;
            temp = temp->next;
        }
    }    
    return count;*/
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if(head == NULL){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> * temp = head;
    int count=0;
    if(head){
        while(temp->next != head){
            if(temp == node){
                count++;
                break;
            }
            temp = temp->next;
        }
        if(temp == node){
            count++;}
        
        if(count != 0){
            return true;
        }
        else{
            return false;}
    }
    else{
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if(head){
        return head;
    }
    else{
        return NULL;
    }
    
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if(head){
        Node<T> *last = head->prev;
        return last;
    }
    else{
        return NULL;
    }
    
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *temp = head;
    if(head){
    if(temp->data == data){
        return temp;
    }
    else{
        temp = temp->next;
        while(temp != head){
            if(temp->data == data){
               return temp;
               break;
            }
            temp = temp->next;
        }
        if(temp == head){
            return NULL;
        }
    }
    }
    else{
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    Node<T> *temp = head;
    int i,count = 0;
    if(head){
    if(index == 0){
        return temp;
    }
    else if(index>0){    
        for(i=0; i<index; i++){
            temp = temp->next;
            if(temp == head){
                count++;
                return NULL;
                break;
            }
        }
        if(count == 0){
            return temp;
        }
    }
    else{
        return NULL;
    }
    }
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    Node<T> *new_node = new Node<T>(data) ;
    new_node->data = data;
    if(head == NULL){
        new_node->next = new_node->prev = new_node;
        head = new_node;
        size++;
    }
    else{
        new_node->next = head;
        head->prev->next = new_node;
        new_node->prev = head->prev;
        head->prev = new_node;
        head = new_node;
        size++;    
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    Node<T> *new_node = new Node<T>(data);
    if(head == NULL){
        new_node->next = new_node->prev = new_node;
        head = new_node;
        size++;    
    }
    else{
        Node<T> *last = head->prev;
        last->next = new_node;
        new_node->prev = last;
        head->prev = new_node;
        new_node->next = head;
        size++;
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    if(head){
        Node<T> *new_node = new Node<T>(data);
        Node<T> *temp = head;
        if(temp == node){
            temp->next->prev = new_node;
            new_node->next= temp->next;
            temp->next = new_node;
            new_node->prev = temp;
            size++;
        }
        else{
            temp=temp->next;
            while(temp != head){
                if(temp == node){
                    temp->next->prev = new_node;
                    new_node->next= temp->next;
                    temp->next = new_node;
                    new_node->prev = temp;
                    size++;
                }
                temp=temp->next;
            }
        }
    }
    else{;}
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    if(head && k>= 2){
        int i, counter = 1;
        Node<T> *temp = head;
        while(temp->next != head){
            if(counter % k == 0){
                Node<T> *new_node = new Node<T>(data);
                temp->prev->next = new_node;
                new_node->prev = temp->prev;
                temp->prev = new_node;
                new_node->next = temp;
                counter++;
                size++;
            }
            counter++;
            temp = temp->next;
        }
        if(counter % k == 0){
            Node<T> *new_node = new Node<T>(data);
            temp->prev->next = new_node;
            new_node->prev = temp->prev;
            temp->prev = new_node;
            new_node->next = temp;
            counter++;
            size++;
        }
        counter++;
        temp = temp->next;
           
        if(counter % k == 0){  
            Node<T> *new_node = new Node<T>(data);
            temp->prev->next = new_node;
            new_node->prev = temp->prev;
            temp->prev = new_node;
            new_node->next = temp;
            counter++;
            size++;
        }
        counter++;
        temp = temp->next;
    }
    else{;}
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    if(head){
        Node<T> *temp = head;
        while(temp->next != head){
            if(temp == node && temp == head){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp = temp->next;
                head = temp;
                node->next = node->prev = NULL;
                delete node;
                size--;
            }
            if(temp == node){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp = temp->next;
                node->next = node->prev = NULL;
                delete node;
                size--;
            }
            else{
                temp = temp->next;
            }
        } 
        if(temp == node){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp = temp->next;
            node->next = node->prev = NULL;
            delete node;
            size--;
        }
    }
    else{;}
    
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if(head){
        Node<T> *temp = head;
        while(temp->next != head){
            if(temp->data == data && temp == head){
                Node<T> *ptr = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp = temp->next;
                head = temp;
                ptr->next = ptr->prev = NULL;
                delete ptr;
                size--;
            }
            else if(temp->data == data){
                Node<T> *ptr = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp = temp->next;
                ptr->next = ptr->prev =  NULL;
                delete ptr;
                size--;
            }
            else{
                temp = temp->next;
            }
        } 
        if(temp->data == data){
            Node<T> *ptr = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp = temp->next;
            ptr->next = ptr->prev = NULL;
            delete ptr;
            size--;
        }
    }
    else{;}
    
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    if(head){    
        Node<T> *last = head->prev;
        head->prev = NULL;
        last->next = NULL;
        if(last == head){
            delete head;
            head = NULL;
            size--;
        }
        else{
            while(head != last){
                Node<T> *prev1 = head;
                head = head->next;
                prev1->next = NULL;
                head->prev = NULL;
                delete prev1;
                prev1 = NULL;
                size--;
            }
            delete head;
            head = NULL;
            size--;
        }
    }
    else{;}
    /* TODO */
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    if(head && k>= 2 && k<= size){
        Node<T> *curr = head;
        int counter = 1;
        while(curr->next != head){
            if(counter % k == 0){
                Node<T> *temp = curr;
                curr = curr->next;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp->prev = temp->next = NULL;
                delete temp;
                size--;
            }
            else{
                curr = curr->next;
            }
            counter++;
        }
        if(counter % k == 0){
            Node<T> *temp = curr;
            curr = curr->next;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp->prev = temp->next = NULL;
            delete temp;
            size--;    
        }
    }
    
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    if(head){
        Node<T> *temp1 = head;
        Node<T> *temp2 = head;
        int adj_counter1 = 0;
        int adj_counter2 = 0;
        int counter1 = 0;
        int counter2 = 0;

        do{
            if(temp1 == node1){
                counter1++;
                adj_counter1++;
                break;
            }
            else{
                temp1 = temp1->next;
                adj_counter1++;
            }    
        }
        while(temp1 != head);

        do{
            if(temp2 == node2){
                counter2 ++;
                adj_counter2++;
                break;
            }
            else{
                temp2 = temp2->next;
                adj_counter2++;
            }    
        }
        while(temp2 != head);
        
        if(counter1 != 0 && counter2 != 0){
            if(size == 2){
                if(head == node1){
                    head = node2;
                }
                else if(head == node2){
                    head = node1;
                }
            }
            else if(node1 == head && head->prev == node2){
                Node<T> *next = node1->next;
                Node<T> *prev = node2->prev;
                node1->next = node2;
                node1->prev = prev;
                node2->next = next;
                node2->prev = node1;
                next->prev = node2;
                prev->next = node1;
                head = node2;
            }
            else if(node2 == head && head->prev == node1){
                Node<T> *next = node2->next;
                Node<T> *prev = node1->prev;
                node2->next = node1;
                node2->prev = prev;
                node1->next = next;
                node1->prev = node2;
                next->prev = node1;
                prev->next = node2;
                head = node1;
            }
            else if(node1 == head && (adj_counter2 - adj_counter1 == 1)){
                Node<T> *prev = node1->prev;
                Node<T> *next = node2->next;
                node1->prev = node2;
                node1->next = next;
                node2->prev = prev;
                node2->next = node1;
                next->prev = node1;
                prev->next = node2;
                head = node2;
            }
            else if(node1 == head && (adj_counter2 - adj_counter1 != 1)){
                Node<T> *prev1 = node1->prev;
                Node<T> *next1 = node1->next;
                Node<T> *prev2 = node2->prev;
                Node<T> *next2 = node2->next;
                node1->prev = prev2;
                node1->next = next2;
                node2->prev = prev1;
                node2->next = next1;
                prev1->next = node2;
                next1->prev = node2;
                prev2->next = node1;
                next2->prev = node1;
                head = node2;
            }
            else if(node2 == head && (adj_counter1 - adj_counter2 == 1)){
                Node<T> *prev = node2->prev;
                Node<T> *next = node1->next;
                node2->prev = node1;
                node2->next = next;
                node1->prev = prev;
                node1->next = node2;
                next->prev = node2;
                prev->next = node1;
                head = node1;
            }
            else if(node2 == head && (adj_counter1 - adj_counter2 != 1)){
                Node<T> *prev1 = node1->prev;
                Node<T> *next1 = node1->next;
                Node<T> *prev2 = node2->prev;
                Node<T> *next2 = node2->next;
                node2->prev = prev1;
                node2->next = next1;
                node1->prev = prev2;
                node1->next = next2;
                prev2->next = node1;
                next2->prev = node1;
                prev1->next = node2;
                next1->prev = node2;
                head = node1;
            }
            else if(adj_counter2 - adj_counter1 == 1){
                Node<T> *prev = node1->prev;
                Node<T> *next = node2->next;
                node1->prev = node2;
                node1->next = next;
                node2->prev = prev;
                node2->next = node1;
                next->prev = node1;
                prev->next = node2;
            }
            else if(adj_counter1 - adj_counter2 == 1){
                Node<T> *prev = node2->prev;
                Node<T> *next = node1->next;
                node2->prev = node1;
                node2->next = next;
                node1->prev = prev;
                node1->next = node2;
                next->prev = node2;
                prev->next = node1;
            }
            else{
                Node<T> *prev1 = node1->prev;
                Node<T> *next1 = node1->next;
                Node<T> *prev2 = node2->prev;
                Node<T> *next2 = node2->next;
                node1->prev = prev2;
                node1->next = next2;
                node2->prev = prev1;
                node2->next = next1;
                prev1->next = node2;
                next1->prev = node2;
                prev2->next = node1;
                next2->prev = node1;
            }
        }    
        else{;}
    }
    else{;}
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    int i;
    for(i=0; i<size; i++){
        if(((i*i+seed)%size == i) || ((i*i+seed)%size <0)){
            ;
        }
        else{
            swap(getNodeAtIndex(i),getNodeAtIndex((i*i+seed)%size));
        }
    }
}
template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    removeAllNodes();
    Node<T> *objcurr = rhs.head;
    // Generate node pointers to build our list
    Node<T> *current = NULL;
    Node<T> *previous = NULL;

    // If obj is an empty list
    if (rhs.head == NULL) {
        // Then, our list will be an empty list also
        head = NULL;
        size = 0;
    }

    // If obj has only one node
    else if (((rhs.head)->next == rhs.head) && ((rhs.head)->prev == rhs.head)) {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Build our single node
        head = new Node<T>((rhs.head)->data);

        // Make the connections properly
        // next should look at head
        head->next = head;
        // prev should look at head
        head->prev = head;

        // Finally, set size
        size = 1;
    }

    // If obj has more than one node
    else {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Start building our list
        // Build our first node
        head = new Node<T>((rhs.head)->data);

        // Make previous to point our first node
        previous = head;

        // This will traverse both lists
        // The condition here might be while(true) also
        do {

            // If objcurr is looking at the last node in the obj list
            // At this point, previous is looking at the last node of our list, current is NULL
            if (objcurr == (rhs.head)->prev) {
                // Make your last connection
                // Connect the last node to the first node
                previous->next = head;
                // Connect the first node to the last node
                head->prev = previous;

                // We finished our mission, so don't continue looping
                break;
            }

            else {
                // Pass objcurr to the next node
                objcurr = objcurr->next;

                // Build a new node at which current is looking, and put the data inside the node pointed by objcurr to this new node
                current = new Node<T>(objcurr->data);

                // Connect the previous node to current node
                previous->next = current;
                // Connect the current node to previouse node
                current->prev = previous;

                // Take a step such that current is NULL and previous is looking at the last generated node
                previous = current;
                current = NULL;
            }
        } while(objcurr != rhs.head);

        // Set our size correctly
        size = rhs.size;
    }
    /* TODO */
}

#endif //LINKEDLIST_H
