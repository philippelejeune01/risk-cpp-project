/*This is the header file GameEngine.h.
It contains all the class, variable and function declarations related to Game Engine part.*/

//The following commands avoid the compilation of the same header file more than once.
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

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
    //Getters declaration:
    string getState();
    //Setters declaration:
    void setState(string newState);
    //Other methods declarations:
    void transition(string newState);
    void passedCommand(string command);
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const GameEngine &ge);
    friend std::istream & operator >> (std::istream &in,  GameEngine &ge);

private:
    //String that stores the state of a game.
    string state;
};

#endif // GAMEENGINE_H