#include "SkipList.h"


node& skip_list::operator[](int index) {
	return *(getNode(index));
}

node* skip_list::pushBack(int val) {
	node* new_node = nullptr;
	if (head) {		//different procedure for initialization of the list
		node* iterator;
		lenght++;

		int levels = 1;
		while(levels < max_levels && (rand() % 2) == 1) levels++;	//coin flip

		new_node = new node(val, levels, lenght);
		iterator = head;
		for (int i = 1; i <= levels; i++) {
			while (true) {
				if (!(iterator->level_links[i])) break;	//iterates the list of all the levels unlocked by new_node and places it at the end
				iterator = iterator->level_links[i];
			}
			iterator->level_links[i] = new_node;
			iterator = head;
		}
	}
	else {
		lenght++;
		new_node = new node(val, max_levels, lenght);	//just sets head
		head = new_node;
	}

	if (!new_node) throw std::runtime_error("couldn't create node");
	return new_node;
}
node* skip_list::popIn(int val, int pos) {
	if (pos > lenght || pos < 1) throw std::runtime_error("index out of range");
	node* new_node;

	if (pos != 1) {	//if the position is at head theres a different procedure
		node* iterator;
		lenght++;

		int levels = 1;
		while (levels < max_levels && (rand() % 2) == 1) levels++;	//coin flip

		new_node = new node(val, levels, 0);
		iterator = head;
		for (int i = 1; i <= levels; i++) {	//repeats for every level of new_node
			while (true) {	//cycle till we dont need the level anymore
				if (!(iterator->level_links[i]) || iterator->level_links[i]->index > pos) break;
				if (iterator->level_links[i]->index == pos) {
					for (int j = 1; j <= i; j++) new_node->level_links[j] = iterator->level_links[i];	//sets all the links as the of the original node in the existing levels to the one replacing
					iterator->level_links[i] = new_node;	//sets it before the replaced node
					break;
				}
				iterator = iterator->level_links[i];
			}
			iterator = head;
		}
	}
	else{
		lenght++;
		new_node = new node(val, max_levels, 0);
		for (int i = 1; i <= max_levels; i++) new_node->level_links[i] = head;	//sets all the links to head
		head = new_node;
	}

	normalizeIndexes();
	return new_node;
}
void skip_list::erase(int pos) {
	if (lenght == 0) throw std::runtime_error("zero size can't delete");
	if(pos != 1){	//different procedures to handle head erasal
		node* deleted_node = getNode(pos); //usefull to save the node to delete it later
		node* iterator = head;	//iterates starting from head
		node* next_node;
		for (int i = max_levels; i >= 1; i--) {	//searches the node in every level
			while (true) {	//iterate till you find the node or go out of range
				next_node = iterator->level_links[i];
				if (!next_node || next_node->index > pos) break;
				if (next_node->index == pos) {
					if (!(next_node->level_links[i])) {	//if the node we need to delete hasn't got links on the level we set the precedent node accordingly
						iterator->level_links[i] = nullptr;
						break;
					}
					iterator->level_links[i] = next_node->level_links[i];	//converts the links of the precedent to the ones after the deleted node
					break;
				}
				iterator = next_node;
			}
			iterator = head;
		}
		delete deleted_node;
	}
	else if(lenght > 1){	//pos is 1 and there is a lenght
		node* nextNode = getNode(pos + 1);
		node* headReplace = new node(nextNode->val, max_levels, 1);	//we create a replacement for head and the node after it and set it up, then replace head and delete the element after it
		for (int i = max_levels; i >= 1; i--) {
			if (head->level_links[i] == nextNode) headReplace->level_links[i] = nextNode->level_links[i];
			else if (head->level_links[i]) headReplace->level_links[i] = head->level_links[i];
		}
		
		delete nextNode;
		delete head;
		head = headReplace;
	}
	else {
		delete head;	//just destroy head
		head = nullptr;
	}

	lenght--;
	normalizeIndexes();
}

node* skip_list::getNode(int pos) {
	if (pos > lenght || pos < 1) throw std::runtime_error("index out of range");

	node* iterator = head;
	for (int i = iterator->levels; i >= 1; i--) {	//iterates till it finds pos on the highest level it can or just errors
		while (true) {
			if (!(iterator) || iterator->index > pos) break;
			if (iterator->index == pos) return iterator;
			iterator = iterator->level_links[i];
		}
		iterator = head;
	}
	throw std::runtime_error("node not found");
	return nullptr;
}

void skip_list::normalizeIndexes() {
	node* iterator = head;

	for (int i = 1; i <= lenght; i++) {
		if (!iterator) throw std::runtime_error("bad normalization");
		iterator->index = i;
		iterator = iterator->level_links[1];
	}
}

skip_list::~skip_list() {
	if (!head) return;
	node* iterator = head;
	node* next_node;
	while (true) {
		next_node = iterator->level_links[1];
		delete iterator;
		if (!next_node) break;
		iterator = next_node;
	}
	head = nullptr;
	lenght = 0;
}
