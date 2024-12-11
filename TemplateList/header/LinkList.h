//
// Created by nebur on 10/12/2024.
//

#ifndef TEMPLATEEX_LINKLIST_H
#define TEMPLATEEX_LINKLIST_H

#include <iostream>

//all the source is in the header as they are templates because I've read it's best practice?????

template<class T>
struct Node{    //node structure to store values and links
    T value;
    Node<T>* next;

    explicit Node(T v = T()):
        value(v),
        next(nullptr)
    {}
};

template<class T>
class Linked_list{
private:
    Node<T>* head;
    int size;

public:
    Linked_list():
        size(0),
        head(nullptr)
    {}
    explicit Linked_list(int size_val, T def_val = T()):    //creates a list with size elements initialized at def_val
        size(0),
        head(nullptr)
    {
            this->resize(size_val, def_val);    //just resizes
    }

    Linked_list(const Linked_list<T>& copyll):  //copy constructor
        size(copyll.size),
        head(nullptr)
    {
        if(size) {  //copy only if there is something to copy
            Node<T>* iterator;
            head = new Node<T>(copyll.head->value); //creates head and then creates and copy's all of the nodes
            iterator = head;
            for (int i = 1; i < size; i++) {
                iterator->next = new Node<T>(copyll[i].value);
                iterator = iterator->next;
            }
        }
    }

    int lenght(){return size;}  //getter

    Linked_list& operator=(const Linked_list& copyll){  //assignment op
        if(copyll.head == this->head) return *this; //handles self copy
        this->resize(copyll.size);  //resize and copy
        for(int i = 0; i < size; i++) this->operator[](i).value = copyll[i].value;
        return *this;
    }
    Node<T>& operator[](int index){ //funky array operator, don't remember the name
        if(index < 0 || index >= size) throw std::out_of_range("list index out of range");

        Node<T>* iterator = head;   //iterate and return
        for(int i = 0; i < index; i++) iterator = iterator->next;
        return *iterator;
    }
    Node<T>& operator[](int index) const{   //overload made for const
        if(index < 0 || index >= size) throw std::out_of_range("list index out of range");

        Node<T>* iterator = head;
        for(int i = 0; i < index; i++) iterator = iterator->next;
        return *iterator;
    }

    Node<T>& push_back(T val){  //creates an element at the tail
        if(head){   //if head is initialized create new node at tail
            size++;
            Node<T>* iterator = head;
            while(true){
                if(!(iterator->next)){
                    iterator->next = new Node<T>(val);
                    return *(iterator->next);
                }
                else iterator = iterator->next;
            }
        }
        else{   //if head isn't initialized create head
            size++;
            head = new Node<T>(val);
            return *head;
        }
    }

    Node<T>& pop_in(T val, int index){  //pops in a node at index moving the previous node residing at index after it
        if(index < 0 || index > size) throw std::out_of_range("list index out of range");

        Node<T> *new_node = new Node<T>(val);

        if(index) { //if the index isn't an edge case (start of the list) iterate to index-1
            Node<T> *iterator = head;
            size++;
            for (int i = 0; i < index - 1; i++) iterator = iterator->next;
            new_node->next = iterator->next;    //make the original element at index the next element of the new node
            iterator->next = new_node;  //change the link at index
            return *new_node;
        }
        else{
            size++;
            new_node->next = head;
            head = new_node;    //same thing but set head
            return *head;
        }
    }

    void delete_node(int index){    //deletes node at index
        if(index < 0 || index >= size) throw std::out_of_range("list index out of range");

        Node<T>* iterator = head;
        Node<T>* deleted_node;

        if(index == 0){ //if the list needs to be deleted or the index is 0 the element that needs deletion is head
            size--;
            deleted_node = head;
            if(deleted_node->next) head = deleted_node->next;   //checks if list has only head, if it has other elements replace head
            else head = nullptr;    //or just delete head
            delete deleted_node;
            return;
        }

            size--;
            for (int i = 0; i < index - 1; i++) iterator = iterator->next;  //iterate to index - 1, skip index and then delete it
            deleted_node = iterator->next;
            iterator->next = deleted_node->next;
            delete deleted_node;
    }

    void resize(int new_size, T def_val = T()){ //resizes the list with a default val
        if(new_size < 0) throw std::out_of_range("new size out of range");
        int difference = abs(new_size - size);

        //just uses pushback and delete for difference times
        if(new_size > size) for(int i = 0; i < difference; i++) push_back(def_val);
        else if(new_size < size) for(int i = 1; i <= difference; i++ ) delete_node(size - 1);   //delete elements from the tail
        else return;    //sizes are equal

        size = new_size;
    }

    ~Linked_list(){ //destructor
        Node<T>* iterator = head;
        Node<T>* next_node;
        while(true){    //iterate all the list and delete it along the way
            if(iterator){
                next_node = iterator->next;
                delete iterator;
                iterator = next_node;
            }
            else break;
        }
    }
};


#endif //TEMPLATEEX_LINKLIST_H
