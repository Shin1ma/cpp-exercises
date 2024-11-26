#include <iostream>
#include "WumpusGame.h"

int main() {
    char input;
    WumpusGame game;
    while(true) {
        try {
            if(game.play_loop()) {
                std::cout << "You won!\n";
            }
            else {
                std::cout << "You lost!\n";
            }
            std::cout << "Do you want to play again? (y/n)\n";
            std::cin >> input;
            if(input == 'y' || input == 'Y') {
                game.reset_game();
            }
            else {
                break;
            }
        }
        catch (std::exception &e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << "\n\n\n" << std::flush;
        }
    }



    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.