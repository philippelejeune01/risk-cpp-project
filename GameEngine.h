/*This is the header file GameEngine.h.
It contains all the class, variable and function declarations related to Game Engine part.*/

//The following commands avoid the compilation of the same header file more than once.
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

const int MINPLAYERS = 2;
const int MAXPLAYERS = 6;

//GameEngine class declaration.
class GameEngine : public Subject, ILoggable
{
public:
    //Default constructor declaration:
    GameEngine();
    //Parameterized constructor declaration:
    GameEngine(string state, CommandProcessor* cp);
    //Destructor:
    ~GameEngine();
    //Copy constructor declaration:
    GameEngine(const GameEngine& ge);
    //Overloaded assignment operator declaration:
    GameEngine& operator = (const GameEngine& ge);
    //Getters declaration:
    string getState();
    CommandProcessor* getCommandProcessor();
    //Setters declaration:
    void setState(string newState);
    void setCommandProcessor(CommandProcessor* newCp);
    //Other methods declarations:
    void transition(string newState);
    bool validate(string command);
    void startupPhase();
    void mainGameLoop();
    void initializeDeck();
    void setPlayersTerritories();
    void randomizePlayOrder();
    void reinforcementPhase();
    void executeOrderPhase();
    void issueOrdersPhase();
    bool shift();
    bool gameOver();
    void removeLosingPlayers();
    bool doesPlayerOwnContinent(int cnum,Player* player);
    string stringToLog();

    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const GameEngine &ge);
    friend std::istream & operator >> (std::istream &in,  GameEngine &ge);
    const int DECK_SIZE = 20;
    Deck* _deck;
    vector<Player*> players;
    MapLoader* maploader;
    Map* _map;
    LogObserver* lo;
    string state;
    CommandProcessor* cp;
    Player *playerPairs[3][2];
};
#endif // GAMEENGINE_H
