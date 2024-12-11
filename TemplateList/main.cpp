#include <iostream>
#include "header/LinkList.h"




int main(){ //tests
    Linked_list<int> tester;
    Linked_list<std::string> tester1;
    Linked_list<std::string> tester2(10, "aaa");
    tester2[2].value = "hi";
    for(int i = 0; i < tester2.lenght(); i++){
        std::cout << tester2[i].value << "\n";
    }
    std::cout << "\n";
    tester1.pop_in("lol", 0);
    std::cout << tester1[0].value << "\n";
    tester1.pop_in("mylol", 1);
    std::cout << tester1[1].value << "\n";
    tester1.push_back("hi boys");
    std::cout << tester1[2].value << "\n";

    tester.push_back(1);
    tester.push_back(2);
    tester.push_back(3);
    tester.push_back(4);

    for(int i = 0; i < tester.lenght(); i++){
        std::cout << tester[i].value << "\n";
    }
    std::cout << "\n";
    tester.delete_node(3);
    for(int i = 0; i < tester.lenght(); i++){
        std::cout << tester[i].value << "\n";
    }
    std::cout << "\n";
    tester.delete_node(0);
    for(int i = 0; i < tester.lenght(); i++){
        std::cout << tester[i].value << "\n";
    }
    std::cout << "\n";

    tester.delete_node(0);
    tester.delete_node(0);

    std::cout << tester.lenght() << "\n";
    std::cout << "\n";

    tester.resize(10);
    for(int i = 0; i < tester.lenght(); i++){
        std::cout << tester[i].value << "\n";
    }
    std::cout << "\n";

    tester.resize(0);
    std::cout << tester.lenght() << "\n";
    std::cout << "\n";

    Linked_list<std::string> copy = tester1;
    for(int i = 0; i < copy.lenght(); i++){
        std::cout << copy[i].value << "\n";
    }
    std::cout << "\n";

    tester2.delete_node(0);
    tester2.delete_node(0);
    tester2.resize(1, "aaaa");
    copy = tester2;
    for(int i = 0; i < copy.lenght(); i++){
        std::cout << copy[i].value;
    }

 	return 0;
}