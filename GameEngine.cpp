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
    cp = new CommandProcessor();
    lo = new LogObserver();
    Attach(lo);
}
void GameEngine::shift(Player *playerPairs[][2], int size){
    // 1 2 3 4
    // 5 6 7 8
    Player *tempPlayer;
    for(int i=0;i<size;i++){
        for (int j = 0; j < 2; ++j) {
            if(i==0 && j==0){
                continue;
            }else if(j==0){
                tempPlayer = playerPairs[i][j];
                playerPairs[i][j] = playerPairs[(i+1) % size][j+( ((i+1)%size) == i+1 ? 0 : 1)];
                playerPairs[(i+1) % size][j+( ((i+1)%size) == i+1 ? 0 : 1)] = tempPlayer;
            }else{
                tempPlayer = playerPairs[i][j];
                playerPairs[i][j] = playerPairs[(i+1) % size][j+( ((i+1)%size) == i+1 ? 1 : 0)];
                playerPairs[(i+1) % size][j+( ((i+1)%size) == i+1 ? 1 : 0)] = tempPlayer;
            }
        }
    }
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
    delete _deck;
    _deck = NULL;
    //This deletes all the Player objects stored in the vector
    //cout << players.size()<<endl;

    //This erases all the pointers stored in the vector
    players.clear();

    delete maploader;
    maploader = NULL;
    delete _map;
    _map = NULL;
    delete lo;
    lo = NULL;
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
    Notify(this);
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
*stringToLog method that creates a string that stores the new state of the GameEngine.
*@return a string that stores the new state of the GameEngine.
*/
string GameEngine::stringToLog()
{
    string s = getState();
    s = ("Game Engine new state: " + s);
    return s;
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
        getCommandProcessor()->getCommandList().back()->saveEffect("restarting the game");
        cout<<"restarting the game"<<endl;
        transition("start");
        return true;
    }
    if((getState() == "start") && (command.find("loadmap") !=string::npos))
    {
        string filename = command.substr(command.find("loadmap")+9);
        filename = filename.substr(0,filename.size()-1);
        getCommandProcessor()->getCommandList().back()->saveEffect("map " + filename + " successfully loaded");
        cout << "\nThe entered command " << command << " is valid for state " << getState();
        transition("maploaded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command.find("loadmap") !=string::npos))
    {
        string filename = command.substr(command.find("loadmap")+9);
        filename = filename.substr(0,filename.size()-1);
        getCommandProcessor()->getCommandList().back()->saveEffect("map " + filename + " successfully loaded");
        cout << "\nThe entered command " << command << " is valid for state " << getState()
            << ", the game remains in the state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "maploaded") && (command == "validatemap"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("map is successfully validated");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("mapvalidated");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "mapvalidated") && (command.find("addplayer") !=string::npos))
    {
        string playername=command.substr(command.find("addplayer")+11);
        playername = playername.substr(0,playername.size()-1);
        getCommandProcessor()->getCommandList().back()->saveEffect("player " + playername + " successfully added");
        cout << "\nThe entered command " << command << " is valid for state " << getState();
        transition("playersadded");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "playersadded") && (command.find("addplayer") !=string::npos))
    {
        string playername=command.substr(command.find("addplayer")+11);
        playername = playername.substr(0,playername.size()-1);
        getCommandProcessor()->getCommandList().back()->saveEffect("player " + playername + " successfully added");
        cout << "\nThe entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "playersadded") && (command == "gamestart"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("main loop of the game is successfully entered");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("assignreinforcement");
        reinforcementPhase();
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "assignreinforcement") && (command == "issueorder"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Assign reinforcement phase");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("issueorders");
        issueOrdersPhase();
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "issueorders") && (command == "execorder"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Issue Order Phase");
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        executeOrderPhase();
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "executeorders") && (command == "win"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Execute Order Phase");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("win");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if(command == "replay")
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("the game will restart");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        players.clear();
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".";
        cout << "\nThe game starts again!" << endl;
        cout<<"--------------------------"<<endl;
        return true;
    }
    if(command == "quit")
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("the game ends");
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    getCommandProcessor()->getCommandList().back()->saveEffect("no effect since this command is not valid in current state");
    cout << "\nThe entered command " << command << " is invalid, please try again and enter a valid command:"<< endl;
    cout<<"--------------------------"<<endl;
    return false;
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
        issueOrdersPhase();
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    if((getState() == "executeorders") && (command == "execorder"))
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        executeOrderPhase();
        shift(playerPairs,players.size());
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

    if (command == "replay")
    {
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("start");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".";
        cout << "The game starts again!\n" << endl;
        cout<<"--------------------------"<<endl;
        return true;
    }
    if(command == "quit")
    {
        cout << "The entered command " << command << " is valid for state " << getState() << ", therefore the game is "
            << "successfully terminated.\n";
        cout<<"--------------------------"<<endl;
        return true;
    }
    cout << "The entered command " << command << " is invalid, please try again and enter a valid command:\n"<< endl;
    return false;
}
void GameEngine::mainGameLoop()
{
    string command;
    do
    {
        command = getCommandProcessor()->getCommand();
        if (!validate(command)) cout<<"Wrong Command, try a valid command\n";
        if (command=="replay") startupPhase();
    }
    while (!(command == "quit") && !(getState() == "win"));
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
            }
            if (command == "validatemap")
            {
                if (!_map->validate())
                {
                    getCommandProcessor()->getCommandList().back()->saveEffect("map is invalid, returning to the start state");
                    cout<<"Map is invalid, returning to start state"<<endl;
                    transition("start");
                }
            }
            if (command.find("addplayer") !=string::npos)
            {
                if (players.size()+1>MAXPLAYERS)
                {
                    getCommandProcessor()->getCommandList().back()->saveEffect("max number of players reached, failed to add this player");
                    cout<<"Maxiumum number of players reached, failed to add this player"<<endl;
                    continue;
                }
                string playername=command.substr(command.find("addplayer")+11);
                playername = playername.substr(0,playername.size()-1);
                tempPlayer = new Player(playername);
                players.push_back(tempPlayer);
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
                }

            }
        }
    }
    while (!(command=="gamestart"));
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


void GameEngine::reinforcementPhase(){
    for (auto x : players){
        int numberOfArmies = (x->getTerritories().size())/3;
        int i;
        int *continent_ptr = _map->getEndOfContinents();
        for(i = 1;i<_map->getNumberOfContinents();i++){
            if(_map->doesPlayerOwnAllTerritories(i, x)) {
                numberOfArmies += *continent_ptr;
            }
            continent_ptr++;
        }
        if(numberOfArmies<3){
            numberOfArmies = 3;
        }
        x->setPool(numberOfArmies);
        cout << numberOfArmies << endl;
    }
}
void GameEngine::issueOrdersPhase()
{
    cout << "--------------------------" << endl;
    cout << "Issue Order Phase\n" << endl;

    //add dummy player if number of players is odd
    if(players.size() % 2 == 1){
        players.push_back(NULL);
    }

    int playerSize = players.size();
    //create a pair of player from players
    for(int i=0;i<playerSize/2;i++){
        playerPairs[i][0] = players.at(i);
        playerPairs[i][1] = players.at((playerSize/2)+i);
    }

    for(int i=0;i<playerSize;i++){
        //if there is a bye (when players are odd)
        if(playerPairs[i][0]==NULL || playerPairs[i][1]==NULL){
            continue;
        }
        else if(playerPairs[i][0]->getFlagIssueOrder() || playerPairs[i][1]->getFlagIssueOrder()){
            cout << "Before issue Order" << endl;
            playerPairs[i][0]->issueOrder(_deck, playerPairs[i][1]);
            cout << "Before issue Order" << endl;
        }
    }
}

void GameEngine::executeOrderPhase(){
    cout << "--------------------------" << endl;
    cout << "Execute Order Phase\n" << endl;
    if(players.size() % 2 == 1){
        players.push_back(NULL);
    }

    int playerSize = players.size();
    Player *playerPairs[playerSize/2][2];
    for(int i=0;i<playerSize;i++){
        //if there is a bye (when players are odd)
        if(playerPairs[i][0]==NULL || playerPairs[i][1]==NULL){
            continue;
        }else{
            playerPairs[i][0]->getOrderList()->executeFirstOrder();
            playerPairs[i][1]->getOrderList()->executeFirstOrder();
        }
    }

}
