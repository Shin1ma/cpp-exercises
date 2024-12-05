#include <iostream>



template<class T> 
struct Node{
	T value;
	Node* next;
	
	Node(T val = T()):
		value(val),
		next(NULL)
	{
	}
};

template<class T>
class Base_LinkList{
private:
	Node<T>* head;
	int size;
	
public:
	Base_LinkList(int size_val):
	size(size_val)
	{
		head = new Node<T>;
		
		Node<T>* new_node;
		Node<T>* iterator = head;
		for(int i = 0; i < size - 1; i++){
			new_node = new Node<T>;
			iterator->next = new_node;
			iterator = iterator->next;
		}
	}
	
	~Base_LinkList(){
		Node<T>* iterator = head;
		Node<T>* delete_node;
		for(int i = 0; i < size; i++){
			delete_node = iterator;
			iterator = iterator->next;
			delete delete_node;
		}
	}	
};

template<class T>
class Link_List{
private:
	Base_LinkList* rough_link;
	Node<T>* head;
	int size;
	
public:
	Link_list():
		head(NULL),
		rough_link(NULL),
		size(0)
	{
	}
	
	Node* push_back(T val){
		
	}
};

