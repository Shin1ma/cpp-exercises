#pragma once
#include <iostream>
#include <vector>
#include <math.h>

struct node {	//list element
	int val;
	int index;
	int levels;
	std::vector<node*> level_links;	//connections to the various levels

	node(int value, int level_links_num, int position) :	//indexes go from 1-size
		val(value), level_links(level_links_num + 1, nullptr), index(position), levels(level_links_num)
	{}
};

class skip_list {
private:
	static const int max_levels = 5;	//max levels possible
	int lenght;
	node* head;	//start of the list has all 5 levels unlocked
	
public:

	

	skip_list():
		lenght(0), head(nullptr)
	{}

	node& operator[](int index);

	int size() { return lenght; }
	int levels() { return max_levels; }

	node* pushBack(int val);	//pushes an element to the tail
	node* popIn(int val, int pos);	//pops in an element at an index moving the one previously there after it
	void erase(int pos);	//erases an element
	
	node* getNode(int pos);	//gets a node from position

	void normalizeIndexes();//shifts the indexes after an erase/pop in

	~skip_list();
};
