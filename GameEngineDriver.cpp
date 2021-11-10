/*This is the driver file: GameEngine.cpp.
It contains everything to run the GameEngine.*/
#include <string>
#include <iostream>
#include "Map.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
#include "GameEngine.h"

/*This is the main method that creates a GameEngine object of a pointer type.
/*The user is then asked to enter commands that are passed to the passedCommand method, until the game succesfully terminates.
*/
int main()
{
    GameEngine *game = new GameEngine();
    string command;

    cout << "The game just started and right now it is in the state: start" << endl;
    game->startupPhase();
    /*Since, game must be a pointer, whenever it is no longer needed,
    the following two things must be done:
    1) deallocating memory:*/
    delete game;
    //2) preventing dangling pointer errors:
    game = NULL;
    return 0;
};
