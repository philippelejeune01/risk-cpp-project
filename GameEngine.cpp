/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/

#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
#include "GameEngine.h"

//Default compiler-generated destructor is enough since no GameEngine variables are pointers.

/**
*Default constructor that creates a GameEngine object, which state is initialized to "start" (the starting position of the game).
*/
GameEngine::GameEngine()
{
    state = "start";
}
/**
*Parameterized constructor that creates a GameEngine object, which state is initialized to the passed state as a parameter.
*@param state is a string that corresponds to the desired state of the GameEngine object.
*/
GameEngine::GameEngine(string state)
{
    state = state;
}
//Since there are no variables that are pointers, a shallow copy can be used.
/**
*Copy constructor that creates a GameEngine object, which is a copy of the passed object.
*@param ge is a constant reference to its own class type (GameEngine class in this case).
*/
GameEngine::GameEngine(const GameEngine& ge)
{
    this->state = ge.state;
}
/**
*Overloaded assignment operator that replaces the contents of an exiting GameEngine object with the passed GameEngine object.
*@param ge is a constant reference to its own class type (GameEngine class in this case).
*@return the current object by reference.
*/
GameEngine& GameEngine::operator = (const GameEngine& ge)
{
    this->state = ge.state;
    return *this;
}
/**
*Getter method that returns the current state of a GameEngine object.
*@return a string that corresponds to the current state of a GameEngine object.
*/
std::string GameEngine::getState()
{
    return state;
}
/**
*Setter method that sets the state of a GameEngine object.
*@param newState is a string that corresponds to the new state of a GameEngine object.
*/
void GameEngine::setState(string newState)
{
    state = newState;
}
/**
*Transition method that transitions from the current state of a GameEngine object to the next one.
*@param newState is a string that corresponds to the new state of a GameEngine object.
*/
void GameEngine::transition(string newState)
{
    setState(newState);
}
/**
*PassedCommand method that checks if the passed command is a valid one for the current state,
*effectuates the transition if the command is valid and outputs the necessary information about the
*command, current state, new state if tansition is successfully done or displays an error message if
*the passed command is invalid.
*@param command is a string that corresponds to the command passed.
*/
void GameEngine::passedCommand(string command)
{
    if((getState() == "start") && (command == "loadmap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("map loaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "map loaded") && (command == "loadmap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n" << endl;
    }
    else if((getState() == "map loaded") && (command == "validatemap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("map validated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "map validated") && (command == "addplayer"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("players added");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "players added") && (command == "addplayer"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n" << endl;
    }
    else if((getState() == "players added") && (command == "assigncountries"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assign reinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "assign reinforcement") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("issue orders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "issue orders") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n" << endl;
    }
    else if((getState() == "issue orders") && (command == "endissueorders"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("execute orders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "execute orders") && (command == "execorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n" << endl;
    }
    else if((getState() == "execute orders") && (command == "endexecorders"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assign reinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }
    else if((getState() == "execute orders") && (command == "win"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("win");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n" << endl;
    }

    else if((getState() == "win") && (command == "play"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        cout << ", therefore the game is successfully transited to the next state " << getState() << "." << endl;
        cout << "The game starts again!\n" << endl;
    }
    else if((getState() == "win") && (command == "end"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n" << endl;
    }
    else
        cout << "The entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
}
/**
*Overloaded stream insertion operator that outputs the current state of the GameEngine object.
*@param out is a reference to the ostream class type.
*@param ge is a reference to the GameEngine class type.
*/
std::ostream & operator << (std::ostream &out, const GameEngine &ge)
{
    out << "The state of the game is: ";
    out << ge.state << endl;
    return out;
}
/**
*Overloaded stream extraction operator that inputs the current state of the GameEngine object.
*@param in is a reference to the ostream class type.
*@param ge is a reference to the GameEngine class type.
*/
std::istream & operator >> (std::istream &in,  GameEngine &ge)
{
    cout << "Enter the state of the game: ";
    in >> ge.state;
    return in;
}
