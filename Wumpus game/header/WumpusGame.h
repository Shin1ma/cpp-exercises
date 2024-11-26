//
// Created by nebur on 22/11/2024.
//

#ifndef WUMPUSGAME_H
#define WUMPUSGAME_H

#include <iostream>
#include "Cave.h"
#include "utils.h"

struct PlayerInput {
    char identifier;    //move(m) or shoot(s)
    int move_room;  //in case identifier is move holds the new player position
    int arrow_rooms[2]; //in case identifier is shoot holds the 2 rooms the arrow will pass

    PlayerInput() : identifier(' '), move_room(0), arrow_rooms{0, 0}
    {}

};

std::istream& operator >>(std::istream& is, PlayerInput& i);    //overloads the >> operator to get player input

class WumpusGame {
private:
    Cave cave;  //cave structure
    int player_room;    //variables holding wumpus and player position
    int wumpus_room;
    bool HasWon;
    bool HasLost;

public:
    WumpusGame();

    bool play_loop();   //main game loop (returns true if player wins)
    void reset_game();  //resets game in case of a new game

    bool shoot_arrow(int room[2]);  //shoots an arrow passing 2 rooms (returns true if player gets the wumpus)
    void move_player(int room); //updates player_room

    void wake_up_wumpus();  //makes the wumpus move to an adjacent room

    void display_adj_rooms_status(int room); //displays clues about the adjacent rooms based on whats in them

    void elaborate_player_input();  //gets player input and acts accordingly
    bool elaborate_player_status(); //checks if an event needs to be triggered (returns true if player loses)

    void bat_event();   //moves player to a random room
    void pit_event();   //kills player
    void wumpus_event();   //kills player
};


#endif //WUMPUSGAME_H
