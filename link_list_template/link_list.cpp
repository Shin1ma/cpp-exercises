#include <iostream>
#include <stdexcept>


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
struct Base_LinkList{
	Node<T>* head;
	int size;

	Base_LinkList(int size_val):
	size(size_val)
	{
		if(size > 0)head = new Node<T>;
		
		Node<T>* new_node;
		Node<T>* iterator = head;
		for(int i = 0; i < size - 1; i++){
			new_node = new Node<T>;
			iterator->next = new_node;
			iterator = iterator->next;
		}
	}
	
	Node<T>& operator[](int index){
		if(index < 0 || index >= size) throw std::runtime_error("index out of range");
		
		Node<T>* iterator = head;
		for(int i = 0; i <= index; i++){
			iterator = iterator->next;
		}
		return *iterator;
	}
	
	~Base_LinkList(){
		
		Node<T>* iterator = head;
		Node<T>* delete_node;
		for(int i = 0; i < size ; i++){
			
			delete_node = iterator;	//SEGFAULT
			iterator = iterator->next;
			delete_node->next = NULL;
			std::cout << "deleted\n";
			delete delete_node;
		}
		
	}	
};

template<class T>
class Link_List{
private:
	Base_LinkList<T> rough_link;
	int size;
	
public:
	Link_List():
		rough_link(0),
		size(0)
	{
	}
	
	Node<T>& operator[](int index) {
		return rough_link[index];
	}
	
	void push_back(T val){
		if(rough_link.size == 0){
			size++;
			rough_link = Base_LinkList<T>(1);
			rough_link[0] = val;
		}
		else{
			size++;
			Base_LinkList<T> old_link = rough_link;
			rough_link = Base_LinkList<T>(size);
			rough_link[size - 1] = val;
			for(int i = 0; i < size - 1; i++) rough_link[i] = old_link[i];
		}
	}
};


int main(){
	Link_List<int> ls;
	
	ls.push_back(1);
	
	std::cout << ls[0].value;
	
	return 0;
}
