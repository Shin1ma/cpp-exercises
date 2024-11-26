//
// Created by nebur on 22/11/2024.
//

#include "WumpusGame.h"

//overload implementation
std::istream& operator >>(std::istream& is, PlayerInput& i){
    is >> i.identifier;
    switch (i.identifier) {
    case 'm':
        is >> i.move_room;
        if(is.fail()){
            return is;
        }
        break;

    case 's':
        char ch1;
        is >> i.arrow_rooms[0] >> ch1 >> i.arrow_rooms[1];
        if(is.fail() || ch1 != ','){
            is.clear(std::ios_base::failbit);
            return is;
        }
        break;

    default:
        is.clear(std::ios_base::failbit);
        return is;
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //in case user put too much input so program doesn't go boom
    return is;
}

//class implementation
WumpusGame::WumpusGame():
    cave(),
    player_room(1),
    wumpus_room(cave.get_random_room(3)),
    HasWon(false),
    HasLost(false)
{
    cave.generate_cave();
}

bool WumpusGame::play_loop(){
    while(!HasWon && !HasLost){
        if(elaborate_player_status()) break;    //checks if an event needs to be triggered and if the player has lost
        cave.print_room(player_room);
        display_adj_rooms_status(player_room);  //displays clues about the adjacent rooms based on whats in them
        elaborate_player_input();

    }
    if(HasWon) return true;
    else return false;
}

void WumpusGame::reset_game(){
    cave.reset_cave();
    cave.generate_cave();
    player_room = 1;
    wumpus_room = cave.get_random_room(3);
    HasWon = false;
    HasLost = false;
}

bool WumpusGame::shoot_arrow(int room[2]){
    if(cave.is_out_of_bounds(room[0]) || cave.is_out_of_bounds(room[1])) error("Room number out of bounds");

    cave_node* current_node = &cave[player_room];
    for(int i = 0; i < 2; i++) {    //iterates the rooms to check if the wumpus is in one of them
        if(room[i] == wumpus_room){
            std::cout << "You have slain the wumpus!!\n";
            return true;
        }
        current_node = &cave[room[i]];
    }
    std::cout << "You missed the wumpus\n";
    wake_up_wumpus();   //wumpus moves to an adjacent room
    return false;
}
void WumpusGame::move_player(int room){
    if(cave.is_out_of_bounds(room)) error("Room number out of bounds");
    if(!(cave.is_adjacent(player_room, room))) error("Rooms are not adjacent");
    player_room = room;
}

void WumpusGame::wake_up_wumpus(){
    std::cout << "uh oh the wumpus has woken up and is moving to an adjacent room\n\n\n";
    wumpus_room = cave[wumpus_room].adj_rooms[getRandomInt(0, 2)]->room_num;
}

void WumpusGame::display_adj_rooms_status(int room){
    if(cave.is_out_of_bounds(room)) error("Room number out of bounds");

    cave_node* current_node = &cave[room];
    for(int i = 0; i < 3; i++){ //iterates the adjacent rooms and checks room type or if the wumpus is in one of them
        if(current_node->adj_rooms[i] != nullptr){
            if(current_node->adj_rooms[i]->room_num == wumpus_room){
                std::cout << "you smell a terrible stench\n";
            }
            switch(current_node->adj_rooms[i]->room_type){
                case PIT:
                    std::cout << "you hear a gust of air\n";
                    break;
                case BAT:
                    std::cout << "you hear wings flapping\n";
                    break;
            }
        }
    }
}

void WumpusGame::elaborate_player_input(){
    PlayerInput input;
    std::cout << "//: ";    //prompt
    std::cin >> input;
    if(std::cin.fail()) error("Invalid input");
    switch (input.identifier) {
        case 'm':   //move identifier
            move_player(input.move_room);
            break;
        case 's':   //shoot identifier
            if(shoot_arrow(input.arrow_rooms)){ //if shoot_arrow returns true the player has won
                HasWon = true;
            }
            break;
    }
}

bool WumpusGame::elaborate_player_status(){
    if(player_room == wumpus_room){ //checks if the player is in the same room as the wumpus, if he is the player loses
        wumpus_event();
        return true;
    }
    switch (cave.get_room_state(player_room)) {
        case PIT:
            pit_event();
            return true;    //if the player falls into a pit he loses
        case BAT:
            bat_event();
            break;
    }
    return false;   //the player hasn't lost
}

void WumpusGame::bat_event(){
    std::cout << "there is a bat in this room\n";
    std::cout << "The bat has taken you to another room\n\n\n";
    player_room = getRandomInt(1, cave.get_size());
}
void WumpusGame::pit_event(){
    std::cout << "Oh no! There is a pit in this room\n";
    std::cout << "you fell into a pit\n\n\n";
    HasLost = true;
}
void WumpusGame::wumpus_event(){
    std::cout << "You found the wumpus, unfortunately it's still alive and he gives you a gruesome death\n";
    std::cout << "The wumpus has eaten you\n\n\n";
    HasLost = true;
}