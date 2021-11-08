/*This is the driver file: GameEngine.cpp.
It contains everything to run the GameEngine.*/
#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <list>
using namespace std;

/**
*This is the main method that creates a GameEngine object of a pointer type.
*The user is then asked to enter commands that are passed to the passedCommand method, until the game succesfully terminates.
*/
int main()
{
    CommandProcessor *cp = new CommandProcessor();
    GameEngine *game = new GameEngine();

    game->setCommandProcessor(cp);
    game->startupPhase();

    /*Since, game must be a pointer, whenever it is no longer needed,
    the following two things must be done:
    1) deallocating memory:*/
    cout << *game->getCommandProcessor();
    delete cp;
    delete game;
    //2) preventing dangling pointer errors:
    cp = NULL;
    game = NULL;
    return 0;
};
