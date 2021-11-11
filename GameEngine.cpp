/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/

#include <string>
#include <iostream>
#include <algorithm>
#include <random>
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
*Destructor that takes care of deallocating pointers properly.
*/
GameEngine::~GameEngine()
{
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
*PassedCommand method that checks if the passed command is a valid one for the current state,
*effectuates the transition if the command is valid and outputs the necessary information about the
*command, current state, new state if tansition is successfully done or displays an error message if
*the passed command is invalid.
*@param command is a string that corresponds to the command passed.
*/
void GameEngine::startupPhase()
{
    string command;
    Player* tempPlayer; // Temporary player pointer
    do
    {
        cout << "Please enter a valid command:" << endl;
        //user inputs a string using the keyboard that is stored in the string command.
        std::getline(cin,command);
        if (passedCommand(command))
        {
            Player* tempPlayer; //Temporary player pointer
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
                tempPlayer = new Player(playername);
                players.push_back(tempPlayer);
            }
            if (command =="gamestart")
            {
                if (players.size()<MINPLAYERS)
                {
                    cout<<"Not enough players! please enter at least one more player"<<endl;
                    transition("players added");
                    continue;
                }
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
    while (!((command == "end") && (getState() == "win")));

    delete tempPlayer;
    tempPlayer = NULL;
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

void GameEngine::executeOrderPhase(){
    bool deployOrdersPresent = false;
    vector<Player*>::iterator players_it = players.begin();

    while(true){
        if((*players_it)->getOrderList()->getOrdList().front()->getOrderType().compare("deploy") == 0){
            (*players_it)->getOrderList()->executeFirstOrder();
            players_it++;
            deployOrdersPresent = true;
        }

        if(players_it == players.end()){
            if(!deployOrdersPresent){
                break;
            }
            players_it = players.begin();
            deployOrdersPresent = false;
            continue;
        }else{
            players_it++;
        }

    }
    bool ordersLeft = false;
    while(true){
        if(!(*players_it)->getOrderList()->getOrdList().empty()){
            (*players_it)->getOrderList()->executeFirstOrder();
            players_it++;
            ordersLeft = true;
        }

        if(players_it == players.end()){
            if(!ordersLeft){
                break;
            }
            players_it = players.begin();
            ordersLeft = false;
            continue;
        }else{
            players_it++;
        }
    }
}