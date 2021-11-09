/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/
#include "GameEngine.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <list>
using namespace std;

//Default compiler-generated destructor is enough since no GameEngine variables are pointers.

/**
*Default constructor that creates a GameEngine object, which state is initialized to "start" (the starting position of the game).
*/
GameEngine::GameEngine()
{
    state = "start";
    command = "";
    //CommandProcessor* cp = new CommandProcessor();
}
/**
*Parameterized constructor that creates a GameEngine object, which state is initialized to the passed state as a parameter.
*@param state is a string that corresponds to the desired state of the GameEngine object.
*/
GameEngine::GameEngine(string state, CommandProcessor* cp)
{
    this->state = state;
    this->cp = new CommandProcessor(*cp);

}
//Since there are is a variables that is a pointer, a deep copy must be created.
/**
*Copy constructor that creates a GameEngine object, which is a copy of the passed object.
*@param ge is a constant reference to its own class type (GameEngine class in this case).
*/
GameEngine::GameEngine(const GameEngine& ge)
{
    this->state = ge.state;
    this->cp = new CommandProcessor(*(ge.cp));
}
/**
*Overloaded assignment operator that replaces the contents of an exiting GameEngine object with the passed GameEngine object.
*@param ge is a constant reference to its own class type (GameEngine class in this case).
*@return the current object by reference.
*/
GameEngine& GameEngine::operator = (const GameEngine& ge)
{
    this->state = ge.state;
    this->cp = new CommandProcessor(*(ge.cp));
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

std::string GameEngine::getCommand()
{
    return command;
}

CommandProcessor* GameEngine::getCommandProcessor()
{
    return cp;
}

/**
*Setter method that sets the state of a GameEngine object.
*@param newState is a string that corresponds to the new state of a GameEngine object.
*/
void GameEngine::setState(string newState)
{
    state = newState;
}

void GameEngine::setCommand(string newCommand)
{
    command = newCommand;
}

void GameEngine::setCommandProcessor(CommandProcessor* newCp)
{
    cp = newCp;
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
bool GameEngine::passedCommand()
{
    string command = getCommand();
    if (command=="reset")
    {
        cout<<"restarting the game"<<endl;
        transition("start");
        return true;
    }
    if((getState() == "start") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("maploaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command == "validatemap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("mapvalidated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "mapvalidated") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("playersadded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command == "gamestart"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assignreinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "assignreinforcement") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("issueorders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "issueorders") && (command == "issueorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "issueorders") && (command == "issueordersend"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("executeorders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "executeorders") && (command == "execorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "executeorders") && (command == "endexecorders"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assignreinforcement");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "executeorders") && (command == "win"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("win");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "win") && (command == "replay"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".";
        cout << "The game starts again!\n" << endl;
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "win") && (command == "quit"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n";
        cout<<"--------------------------"<<endl;
    }
    cout << "The entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
    return false;
}

bool GameEngine::validate()
{
    string command = getCommand();
    if (command=="reset")
    {
        cout<<"restarting the game"<<endl;
        transition("start");
        return true;
    }
    if((getState() == "start") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("maploaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command.find("loadmap") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command == "validatemap"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("mapvalidated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "mapvalidated") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("playersadded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command.find("addplayer") !=string::npos))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command == "gamestart"))
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("win");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "win") && (command == "replay"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("the game will restart");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".";
        cout << "The game starts again!\n" << endl;
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "win") && (command == "quit"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("the game ends");
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n";
        cout<<"--------------------------"<<endl;
    }
    else
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("no effect since this command is not valid in current state");
        cout << "The entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
        return false;
    }
}

void GameEngine::startupPhase()
{
    string command;
    do
    {
        setCommand(getCommandProcessor()->getCommand());
        command = getCommand();

        if (validate())
        {
            if((getState() == "start"||getState()=="maploaded") && (command.find("loadmap") !=string::npos))
            {
                string filename=command.substr(command.find("loadmap")+9);
                filename = filename.substr(0,filename.size()-1);
                maploader = new MapLoader(filename);
                _map = new Map(maploader->Load());
                cout<<*_map<<endl;
                getCommandProcessor()->getCommandList().back()->saveEffect("map " + filename + " successfully loaded");
            }
            if (command == "validatemap")
            {
                if (!_map->validate())
                {
                    cout<<"Map is invalid, returning to start state"<<endl;
                    transition("start");
                    getCommandProcessor()->getCommandList().back()->saveEffect("map is invalid, returning to the start state");
                }
                else
                    getCommandProcessor()->getCommandList().back()->saveEffect("map is successfully validated");
            }
            if (command.find("addplayer") !=string::npos)
            {
                if (players.size()+1>MAXPLAYERS)
                {
                    cout<<"Maxiumum number of players reached, failed to add this player"<<endl;
                    getCommandProcessor()->getCommandList().back()->saveEffect("max number of players reached, failed to add this player");
                    continue;
                }
                string playername=command.substr(command.find("addplayer")+11);
                playername = playername.substr(0,playername.size()-1);
                Player p(playername);
                players.push_back(&p);
                getCommandProcessor()->getCommandList().back()->saveEffect("player " + playername + " successfully added");
            }
            if (command =="gamestart")
            {
                if (players.size()<MINPLAYERS)
                {
                    cout<<"Not enough players! please enter at least one more player"<<endl;
                    getCommandProcessor()->getCommandList().back()->saveEffect("Not enough players! At least one more player is needed");
                    transition("playersadded");
                    continue;
                }
                else
                    getCommandProcessor()->getCommandList().back()->saveEffect("main loop of the game is successfully entered");

                // Distribute all terrotories to players
                // setPlayersTerritories(_map->territories, players, players.size());
                //cout << players.at(0) << endl;
            }
        }
    }
    while (!((command == "quit") && (getState() == "win")));
}

/**
*Overloaded stream insertion operator that outputs the current state of the GameEngine object.
*@param out is a reference to the ostream class type.
*@param ge is a reference to the GameEngine class type.
*/
std::ostream &operator << (std::ostream &out, const GameEngine &ge)
{
    out << "The state of the game is: "
    << ge.state << endl;
    return out;
}
/**
*Overloaded stream extraction operator that inputs the current state of the GameEngine object.
*@param in is a reference to the ostream class type.
*@param ge is a reference to the GameEngine class type.
*/
std::istream &operator >> (std::istream &in,  GameEngine &ge)
{
    cout << "Enter the state of the game: ";
    in >> ge.state;
    return in;
}
