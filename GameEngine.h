/*This is the header file GameEngine.h.
It contains all the class, variable and function declarations related to Game Engine part.*/

//The following commands avoid the compilation of the same header file more than once.
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include <string>
#include <iostream>
#include <list>
using std::string;
using std::cin;
using std::cout;
using std::endl;

const int MINPLAYERS = 2;
const int MAXPLAYERS = 6;

//GameEngine class declaration.
class GameEngine
{
public:
    //Default constructor declaration:
    GameEngine();
    //Parameterized constructor declaration:
    GameEngine(string state, CommandProcessor* cp);
    //Copy constructor declaration:
    GameEngine(const GameEngine& ge);
    //Overloaded assignment operator declaration:
    GameEngine& operator = (const GameEngine& ge);
    //Getters declaration:
    string getState();
    string getCommand();
    CommandProcessor* getCommandProcessor();
    //Setters declaration:
    void setState(string newState);
    void setCommand(string newCommand);
    void setCommandProcessor(CommandProcessor* newCp);
    //Other methods declarations:
    void transition(string newState);
    bool validate();
    bool passedCommand();
    void startupPhase();
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const GameEngine &ge);
    friend std::istream & operator >> (std::istream &in,  GameEngine &ge);
    vector<Player*> players;
    MapLoader* maploader;
    Map* _map;
private:
    //String that stores the state of a game.
    string state;
    string command;
    CommandProcessor* cp;
};
#endif // GAMEENGINE_H
