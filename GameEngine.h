/*This is the header file GameEngine.h.
It contains all the class, variable and function declarations related to Game Engine part.*/

//The following commands avoid the compilation of the same header file more than once.
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Map.h"
#include "Player.h"
#include <string>
#include <iostream>
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
    GameEngine(string state);
    //Copy constructor declaration:
    GameEngine(const GameEngine& ge);
    //Overloaded assignment operator declaration:
    GameEngine& operator = (const GameEngine& ge);
    //Destructor
    ~GameEngine();
    //Getters declaration:
    string getState();
    //Setters declaration:
    void startupPhase();
    void setState(string newState);
    //Other methods declarations:
    void transition(string newState);
    bool passedCommand(string command);
    void initializeDeck();
    void randomizePlayOrder();
    void reinforcementPhase();
    void issueOrdersPhase(Player* pl1, Player* pl2);
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const GameEngine &ge);
    friend std::istream & operator >> (std::istream &in,  GameEngine &ge);
    const int DECK_SIZE = 20;
    Deck* _deck;
    vector<Player*> players;
    MapLoader* maploader;
    Map* _map;
private:
    //String that stores the state of a game.
    string state;

};

#endif // GAMEENGINE_H
