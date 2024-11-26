//
// Created by nebur on 22/11/2024.
//

#include "Cave.h"

Cave::Cave() :
    cave_size(getRandomInt(MIN_ROOMS, MAX_ROOMS)),
    cave_head(nullptr)
{
    for (int i = 0; i < cave_size; i++) {   //creates cave nodes and initializes them with a random state (60% empty, 20% pit, 20% bat)
        if (i == 0) {
            cave_nodes.push_back(new cave_node(i + 1, EMPTY));
        }
        else
        {
            int random = getRandomInt(0, 9);
            if (random <= 5) {
                cave_nodes.push_back(new cave_node(i + 1, EMPTY));
            } else if (random <= 8) {
                cave_nodes.push_back(new cave_node(i + 1, BAT));
            } else {
                cave_nodes.push_back(new cave_node(i + 1, PIT));
            }
        }
    }
    cave_head = cave_nodes[0];
}

cave_node& Cave::operator[](int room_num){
    if(room_num < 1 || room_num > cave_size){
        error("Room number out of bounds");
    }
    return *cave_nodes[room_num - 1];
}

bool Cave::verify_connection(cave_node *current_node, int random_connection) {
    bool is_full;   //used to check if the room random connection has chosen is already full
    bool is_valid = true;    //returned value used to check if the connection is valid

    if (cave_nodes[random_connection] == current_node) is_valid = false;    //checks if the room is not connecting to itself
    for (int k = 0; k < 3; k++) {
        if (current_node->adj_rooms[k] == cave_nodes[random_connection] || cave_nodes[random_connection]->adj_rooms[k] == current_node) { //checks if the rooms are already connected
            is_valid = false;
            break;
        }

        is_full = true;
        if (cave_nodes[random_connection]->adj_rooms[k] == nullptr) {   //checks if the room chosen is full by checking if it has null pointers
            is_full = false;
            break;
        }
    }
    if (is_full) is_valid = false;  //if the room is full the connection is invalid
    return is_valid;
}
void Cave::randomly_connect_adjacent_rooms(int room_num) {
    int tolerance = 1000;   //used to avoid infinite loops
    int random_connection;  //used to store the random index to connect to
    cave_node *current_node = cave_nodes[room_num];   //used to store the current node to connect
    for (int j = 0; j < 3; j++) {   //for every exit of the room tries to connect to a random room if the exit is empty
        if (current_node->adj_rooms[j] != nullptr) continue;    //checks if the exit is already connected

        random_connection = getRandomInt(0 + room_num, cave_size - 1);
        while (!verify_connection(current_node, random_connection)) {   //generates random connections until a valid one is found
            if (tolerance <= 0) break;
            random_connection = getRandomInt(0 + room_num, cave_size - 1);
            tolerance--;
        }

        if (tolerance > 0) {    //if the loop ended because a valid connection was found, connects the rooms
            current_node->adj_rooms[j] = cave_nodes[random_connection];
            for (int x = 0; x < 3; x++) {
                if (cave_nodes[random_connection]->adj_rooms[x] == nullptr) {   //connects the rooms in both directions
                    cave_nodes[random_connection]->adj_rooms[x] = current_node;
                    break;
                }
            }
        }
        else current_node->adj_rooms[j] = nullptr;  //if the loop ended because of the tolerance, sets the exit to null
    }
}

void Cave::reset_cave(){
    for(int i = 0; i < cave_size; i++){
        delete cave_nodes[i];
        cave_nodes[i] = nullptr;
    }
    cave_nodes.clear();
    cave_size = getRandomInt(MIN_ROOMS, MAX_ROOMS);
    cave_head = nullptr;
    for (int i = 0; i < cave_size; i++) {   //creates cave nodes and initializes them with a random state (60% empty, 20% pit, 20% bat)
        if (i == 0) {
            cave_nodes.push_back(new cave_node(i + 1, EMPTY));
        }
        else
        {
            int random = getRandomInt(0, 9);
            if (random <= 5) {
                cave_nodes.push_back(new cave_node(i + 1, EMPTY));
            } else if (random <= 8) {
                cave_nodes.push_back(new cave_node(i + 1, BAT));
            } else {
                cave_nodes.push_back(new cave_node(i + 1, PIT));
            }
        }
    }
    cave_head = cave_nodes[0];
}
void Cave::generate_cave() {
    for (int i = 0; i < cave_size; i++) {
        randomly_connect_adjacent_rooms(i);   //connects all of the rooms randomly
    }
}

room_state Cave::get_room_state(int room) {
    if (room < 1 || room > cave_size) {
        error("Room number out of bounds");
    }
    return cave_nodes[room - 1]->room_type;
}

bool Cave::is_adjacent(int room1, int room2){
    if(room1 < 1 || room1 > cave_size || room2 < 1 || room2 > cave_size){
        error("Room number out of bounds");
    }
    for(int i = 0; i < 3; i++){
        if(cave_nodes[room1 - 1]->adj_rooms[i] == cave_nodes[room2 - 1] || cave_nodes[room2 - 1]->adj_rooms[i] == cave_nodes[room1 - 1]){
            return true;
        }
    }
    return false;
}
bool Cave::is_out_of_bounds(int room) const{
    if(room < 1 || room > cave_size){
        return true;
    }
    return false;
}

void Cave::print_room(int room) const {
    if (room < 1 || room > cave_size) {
        error("Room number out of bounds");
    }

    cave_node* current_node = cave_nodes[room - 1];
    std::stringstream msg;
    msg << "Room " << (current_node->adj_rooms[0] ? std::to_string(current_node->adj_rooms[0]->room_num) : "(no room here)")
        << " - " << "Room " << room << " - "
        << "Room " << (current_node->adj_rooms[1] ? std::to_string(current_node->adj_rooms[1]->room_num) : "(no room here)") << '\n';
    std::cout << msg.str();
    std::cout << "            |\n";
    std::cout << "         Room " + (current_node->adj_rooms[2] ? std::to_string(current_node->adj_rooms[2]->room_num) : "(no room here)") << '\n';
}

Cave::~Cave(){
    for(int i = 0; i < cave_size; i++){
        delete cave_nodes[i];
        cave_nodes[i] = nullptr;
    }
}