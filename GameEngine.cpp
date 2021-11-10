/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/
#include "GameEngine.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <random>
using namespace std;

/**
*Default constructor that creates a GameEngine object, which state is initialized to "start" (the starting position of the game).
*/
GameEngine::GameEngine()
{
    state = "start";
}
/**
*Parameterized constructor that creates a GameEngine object, which state is initialized to the passed state as a parameter
*and CommandProcessor object is initialized to the passed command processor object as a parameter.
*@param state is a string that corresponds to the desired state of the GameEngine object.
*@param cp is a CommandProcessor object that corresponds to the desired CommandProcessor object of the GameEngine object.
*/
GameEngine::GameEngine(string state, CommandProcessor* cp)
{
    this->state = state;
    this->cp = new CommandProcessor(*cp);

}
/**
*Destructor that deletes the CommandProcessor object of the GameEngine object and then initializes it to NULL.
*/
GameEngine::~GameEngine()
{
    delete cp;
    cp = NULL;
    //This deletes all the Player objects stored in the vector
    for(vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
    {
        delete *it;
    }
    //This erases all the pointers stored in the vector
    players.clear();

    delete _deck;
    _deck = NULL;
    delete maploader;
    maploader = NULL;
    delete _map;
    _map = NULL;
}
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
/**
*Getter method that returns the current CommandProcessor object of a GameEngine object.
*@return a CommandProcessor object that corresponds to the current CommandProcessor object of a GameEngine object.
*/
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
/**
*Setter method that sets the CommandProcessor object of a GameEngine object.
*@param newCp is a CommandProcessor object that corresponds to the new CommandProcessor object of a GameEngine object.
*/
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
*Creates a vector of random card pointers to pass to be used when initializing the deck object
*/
void GameEngine::initializeDeck()
{
    srand((unsigned) time(0));
    vector<Card*> v;
    //creating Cards to put in deck
    for(int i = 0; i < GameEngine::DECK_SIZE; i++){
        Card *c = new Card();
        v.push_back(c);
    }

    _deck = new Deck(v);
}
/**
*Randomize the order of play of the players by shuffling the players vector
*/
void GameEngine::randomizePlayOrder()
{
    default_random_engine randEngine{random_device{}()};
    shuffle(begin(players), end(players), randEngine);
}
/**
*validate method that checks if the passed command is a valid one for the current state,
*effectuates the transition if the command is valid and outputs the necessary information about the
*command, current state, new state if tansition is successfully done or displays an error message if
*the passed command is invalid.
*@param command is a string that corresponds to the command passed.
*@return a boolean depending whether the command is valid or not in the current game state.
*/
bool GameEngine::validate(string command)
{
    if (command=="reset")
    {
        cout<<"restarting the game"<<endl;
        transition("start");
        return true;
    }
    if((getState() == "start") && (command.find("loadmap") !=string::npos))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState();
        transition("maploaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command.find("loadmap") !=string::npos))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command == "validatemap"))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState();
        transition("mapvalidated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "mapvalidated") && (command.find("addplayer") !=string::npos))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState();
        transition("playersadded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command.find("addplayer") !=string::npos))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command == "gamestart"))
    {
        cout << "\nThe entered command " << command << " is valid for state " << getState();
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
        cout << "\nThe entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
        return false;
    }
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
    string command = getCommandProcessor()->getCommand();
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
void GameEngine::startupPhase()
{
    Player* tempPlayer; // Temporary player pointer
    string command;
    do
    {
        command = getCommandProcessor()->getCommand();
        if (validate(command))
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
                tempPlayer = new Player(playername);
                players.push_back(tempPlayer);
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
                {
                    // Distribute all territories to players in almost equald parts depending on the number of players
                    setPlayersTerritories(_map->getTerritories(), players);

                    //Randomize the order of play
                    randomizePlayOrder();

                    initializeDeck(); //Creating the Deck
                    for(int i = 0; i < players.size(); i++)
                    {
                        //Give 50 initial armies to each player's respective reinforcement pool
                        players.at(i)->setPool(50);
                        //Each player draws 2 initial cards from the deck
                        players.at(i)->getHand()->addCard(_deck->draw());
                        players.at(i)->getHand()->addCard(_deck->draw());

                        cout << *players.at(i) << endl;
                    }
                    getCommandProcessor()->getCommandList().back()->saveEffect("main loop of the game is successfully entered");
                }
            }
        }
    }
    while (!((command == "quit") && (getState() == "win")));
    delete tempPlayer;
    tempPlayer = NULL;
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
