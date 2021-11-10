/*This is the driver file: GameEngine.cpp.
It contains everything to run the GameEngine.*/
#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

/**
*This is the main method that creates a GameEngine object of a pointer type.
*/
int main()
{
    GameEngine *game = new GameEngine();
    string s;
    cout << "Please, enter \"-console\" if you want to pass the commands directly to the console or \"-file <name>\" if you want to load them from a file:" << endl;
    getline(std::cin, s);
    if(s == "-console")
    {
        cout << "The game just started and right now it is in the state: start\n" << endl;
        CommandProcessor *cp = new CommandProcessor();
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
    }
    if(s.find("file") != string::npos)
    {
        string name = s.substr(s.find("file")+6);
        name = name.substr(0,name.size()-1);
        FileLineReader *flc = new FileLineReader(name);
        FileCommandProcessorAdapter *fcpa = new FileCommandProcessorAdapter(flc);
        game->setCommandProcessor(fcpa);
        cout << "The game just started and right now it is in the state: start\n" << endl;
        game->startupPhase();

        /*Since, game must be a pointer, whenever it is no longer needed,
        the following two things must be done:
        1) deallocating memory:*/
        cout << *game->getCommandProcessor();
        delete flc;
        delete fcpa;
        delete game;
        //2) preventing dangling pointer errors:
        flc = NULL;
        fcpa = NULL;
        game = NULL;
    }
    return 0;
};


