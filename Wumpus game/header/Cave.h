//
// Created by nebur on 22/11/2024.
//

#ifndef CAVE_H
#define CAVE_H

#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

#include "utils.h"

/*
Class defining the randomic cave structure where the game takes place,
It's generated randomly with rooms going from MIN_ROOMS to MAX_ROOMS
*/
const static int MIN_ROOMS = 10;
const static int MAX_ROOMS = 20;


//enum defining the possible states of a room
enum room_state {
    EMPTY,
    PIT,
    BAT
};

//struct defining a cave room
struct cave_node {
    int room_num;
    room_state room_type;
    std::vector<cave_node *> adj_rooms;

    cave_node(int num, room_state type) :
            room_num(num),
            room_type(type),
            adj_rooms(3, nullptr) {}

};

class Cave {
private:
    int cave_size;
    cave_node *cave_head;
    std::vector<cave_node *> cave_nodes; //used to efficently look up rooms

public:
    Cave();

    cave_node *get_cave_head() { return cave_head; }
    int get_size() { return cave_size; }
    int get_random_room(int min) { if(min > cave_size) error("out of bounds"); return getRandomInt(min, cave_size); }

    cave_node& operator[](int room_num); //overloads the [] operator to return a room range 1-size

    void reset_cave(); //resets the cave, basically the same as the constructor
    void generate_cave(); //generates the cave structure with size rooms iterconnecting
    void randomly_connect_adjacent_rooms(int room_num); //connects all of the rooms randomly with eachother
    bool verify_connection(cave_node *current_node, int random_connection); //verifies if a connection is valid

    room_state get_room_state(int room); //returns the state of a room
    bool is_adjacent(int room1, int room2); //checks if two rooms are adjacent
    bool is_out_of_bounds(int room) const; //checks if a room is out of bounds
    void print_room(int room) const; //prints the room and it's exits

    ~Cave();
};


#endif //CAVE_H
