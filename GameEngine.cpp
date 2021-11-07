/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/

#include <string>
#include <iostream>
using namespace std;
#include "GameEngine.h"
#include "Map.h"

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
void GameEngine::startupPhase()
{
    string command;
    do
    {
        cout << "Please enter a valid command:" << endl;
        //user inputs a string using the keyboard that is stored in the string command.
        std::getline(cin,command);
        if (passedCommand(command))
        {
            if((getState() == "start"||getState()=="map loaded") && (command.find("loadmap") !=string::npos))
            {
                string filename=command.substr(command.find("loadmap")+9);
                filename = filename.substr(0,filename.size()-1);
                maploader = new MapLoader(filename);
                _map = new Map(maploader->Load());
                cout<<*_map<<endl;
            }
            if (command == "validatemap")
                if (!_map->validate())
                {
                    cout<<"Map is invalid, returning to start state"<<endl;
                    transition("start");
                }
            if (command.find("addplayer") !=string::npos)
            {
                if (players.size()+1>MAXPLAYERS)
                {
                    cout<<"Maxiumum amount of players reached, failed to add this player"<<endl;
                    continue;
                }
                string playername=command.substr(command.find("addplayer")+11);
                playername = playername.substr(0,playername.size()-1);
                Player p(playername);
                players.push_back(&p);
            }
            if (command =="gamestart")
            {
                if (players.size()<MINPLAYERS)
                {
                    cout<<"Not enough players! please enter at least one more player"<<endl;
                    transition("players added");
                    continue;
                }
                // Distribute all terrotories to players
//                setPlayersTerritories(_map->territories, players, players.size());
//                cout << players.at(0) << endl;
            }
        }
    }
    while (!((command == "end") && (getState() == "win")));
}
bool GameEngine::passedCommand(string command)
{
    if (command=="reset")
    {
        cout<<"restarting the game"<<endl;
        transition("start");
        return true;
    }
    if((getState() == "start") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("map loaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "map loaded") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "map loaded") && (command == "validatemap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("map validated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "map validated") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("players added");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "players added") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "players added") && (command == "assigncountries"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assign reinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "players added") && (command == "gamestart"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assign reinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "assign reinforcement") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("issue orders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "issue orders") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "issue orders") && (command == "endissueorders"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("execute orders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "execute orders") && (command == "execorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "execute orders") && (command == "endexecorders"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assign reinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "execute orders") && (command == "win"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("win");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "win") && (command == "play"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".";
        cout << "The game starts again!\n" << endl;
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "win") && (command == "end"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n";
        cout<<"--------------------------"<<endl;
        transition("end");
    }
    cout << "The entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
    return false;
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
