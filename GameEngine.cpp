/*This is the source file: GameEngine.cpp.
It contains all the function definitions for the function declarations in the GameEngine.h file.*/
#include "GameEngine.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
using namespace std;

/**
*Default constructor that creates a GameEngine object, which state is initialized to "start" (the starting position of the game).
*/
GameEngine::GameEngine()
{
    state = "start";
    players = new vector<Player*>();
    cp = new CommandProcessor();
    lo = new LogObserver();
    Attach(lo);
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
    players = new vector<Player*>();
}
/**
*Destructor that deletes the CommandProcessor object of the GameEngine object and then initializes it to NULL.
*/
GameEngine::~GameEngine()
{
    if (cp)
    delete cp;
    cp = NULL;
    if (_deck)
    delete _deck;
    _deck = NULL;
    //This deletes all the Player objects stored in the vector
    //cout << players.size()<<endl;

    //This erases all the pointers stored in the vector
    if (players)
        delete players;
    players->clear();

    if (maploader)
    delete maploader;
    maploader = NULL;
    if (_map)
    delete _map;
    _map = NULL;
    if (lo)
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
    vector<Card*>* v = new vector<Card*>();
    //creating Cards to put in deck
    for(int i = 0; i < GameEngine::DECK_SIZE; i++){
        Card *c = new Card();
        v->push_back(c);
    }

    _deck = new Deck(v);
}
/**
*Randomize the order of play of the players by shuffling the players vector
*/
void GameEngine::randomizePlayOrder()
{
    default_random_engine randEngine{random_device{}()};
    shuffle(begin(*players), end(*players), randEngine);
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
Map* GameEngine::_map=NULL;
vector<Player*>* GameEngine::players=NULL;

void tournamentMode(CommandProcessor * fcpa)
{
    int numberOfMaps,numberOfPlayers,numberOfGames,t;
    vector<Map*> maps;
    vector<Player*> players;
    vector<string> winners;
    cout<<"Enter the number of maps:\n";
    numberOfMaps =stoi(fcpa->getCommand());

    for (int i=0;i<numberOfMaps;i++)
    {
        string fileName="";
        cout<<"Enter Map "<<i+1<<"'s filename:\n";
        fileName=fcpa->getCommand();;
        MapLoader* maploader = new MapLoader(fileName);
        Map* maptemp = new Map(*maploader->Load());
        cout<<*maptemp<<endl;
        maptemp->validate();
        maps.push_back(maptemp);

        delete maploader;
    }
    cout<<"Enter Number of players:\n";
    numberOfPlayers =stoi(fcpa->getCommand());
    GameEngine::players = new vector<Player*>();
    for (int i=0;i<numberOfPlayers;i++)
    {
        string strategy;
        cout<<"Enter Player"<<i+1<<"s strategy:\n";
        strategy=fcpa->getCommand();
        Player* temp = new Player("p"+to_string(i+1),strategy);
        players.push_back(new Player(*temp));
    }
    cout<<"Enter Number of games:\n";
    numberOfGames = stoi(fcpa->getCommand());
    cout<<"Enter Number of turns:\n";
    t = stoi(fcpa->getCommand());
    for (int i = 0 ; i < numberOfMaps; i++)
    {
        for (int j = 0 ; j < numberOfGames; j++)
        {
            GameEngine* game = new GameEngine();
            game->turnsPerGame=t;
            GameEngine::_map = new Map(*maps[i]);
            for (int k=0;k<players.size();k++)
                game->players->push_back(new Player(*players[k]));
            game->setPlayersTerritories();
            game->randomizePlayOrder();
            game->initializeDeck(); //Creating the Deck
            for(int l = 0; l < players.size(); l++)
            {
                game->players->at(l)->setPool(50);
                game->players->at(l)->getHand()->addCard(game->_deck->draw());
                game->players->at(l)->getHand()->addCard(game->_deck->draw());
            }
            game->mainGameLoop();
            winners.push_back(game->strategyname);
            GameEngine::_map=NULL;
            GameEngine::players->clear();
            GameEngine::players=NULL;
        }
    }
    cout<< "\n\n\n-------Tournament Mode:----------\n          ";
    for (int i = 0; i<numberOfGames ;i++)
    {
        cout<<"Game"<<i+1<<"         ";
    }
    cout<<endl;
    for (int i = 0; i<numberOfMaps ;i++)
    {
        cout<<"Map "<<i+1<<"     ";
        for (int j =0;j<numberOfGames;j++)
        {
            cout<<winners[i*j];
            int blank = 14 - winners[i*j].length();
            if (j!= numberOfGames-1)
                for (int k = 0; k<blank; k++)
                    cout<<' ';
        }
        cout<<endl;
    }

}

void tournamentMode()
{
    int numberOfMaps,numberOfPlayers,numberOfGames,t;
    vector<Map*> maps;
    vector<Player*> players;
    vector<string> winners;
    cout<<"Enter the number of maps:\n";
    //cin>>numberOfMaps;
    while (!(cin>>numberOfMaps))
    {
        cout<<"Wrong value, try again!\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int i=0;i<numberOfMaps;i++)
    {
        string fileName="";
        cout<<"Enter Map "<<i+1<<"'s filename:\n";
        cin>>fileName;
        ifstream file;
        file.open(fileName);

        while (!file)
        {
            cout<<"Map doesn't exist, enter a valid map\n";
            cin>>fileName;
            file.open(fileName);
        }
        file.close();

        MapLoader* maploader = new MapLoader(fileName);
        Map* maptemp = new Map(*maploader->Load());
        cout<<*maptemp<<endl;
        maptemp->validate();
        maps.push_back(maptemp);

        delete maploader;
    }
    cout<<"Enter Number of players:\n";

    while (!(cin>>numberOfPlayers))
    {
        cout<<"Wrong value, try again!\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    GameEngine::players = new vector<Player*>();

    for (int i=0;i<numberOfPlayers;i++)
    {
        string strategy;
        cout<<"Enter Player"<<i+1<<"s strategy:\n";
        cin>>strategy;
        bool flag = false;
        string types[] = {"Aggressive", "Neutral", "Benevolent", "Cheater", "Human"};
        while (true)
        {
            for (int x = 0; x < 5; x++)
                if (strategy == types[x])
                {
                    flag=true;
                    break;
                }
            if (flag) break;
            cout<<"Wrong strategy";
            cin>>strategy;
        }

        Player* temp = new Player("p"+to_string(i+1),strategy);
        players.push_back(new Player(*temp));
    }
    cout<<"Enter Number of games:\n";

    while (!(cin>>numberOfGames))
    {
        cout<<"Wrong value, try again!\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    cout<<"Enter Number of turns:\n";

    while (!(cin>>t))
    {
        cout<<"Wrong value, try again!\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int i = 0 ; i < numberOfMaps; i++)
    {
        for (int j = 0 ; j < numberOfGames; j++)
        {
            GameEngine* game = new GameEngine();
            game->turnsPerGame=t;
            GameEngine::_map = new Map(*maps[i]);
            for (int k=0;k<players.size();k++)
                game->players->push_back(new Player(*players[k]));
            game->setPlayersTerritories();
            game->randomizePlayOrder();
            game->initializeDeck(); //Creating the Deck
            for(int l = 0; l < players.size(); l++)
            {
                game->players->at(l)->setPool(50);
                game->players->at(l)->getHand()->addCard(game->_deck->draw());
                game->players->at(l)->getHand()->addCard(game->_deck->draw());
            }
            game->mainGameLoop();
            winners.push_back(game->strategyname);
            GameEngine::_map=NULL;
            GameEngine::players->clear();
            GameEngine::players=NULL;
        }
    }
    cout<< "\n\n\n-------Tournament Mode:----------\n          ";
    for (int i = 0; i<numberOfGames ;i++)
    {
        cout<<"Game"<<i+1<<"         ";
    }
    cout<<endl;
    for (int i = 0; i<numberOfMaps ;i++)
    {
        cout<<"Map "<<i+1<<"     ";
        for (int j =0;j<numberOfGames;j++)
        {
            cout<<winners[i*j];
            int blank = 14 - winners[i*j].length();
            if (j!= numberOfGames-1)
                for (int k = 0; k<blank; k++)
                    cout<<' ';
        }
        cout<<endl;
    }

}
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
    if((getState() == "start") && (command.find("tournament") !=string::npos))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("tournament mode successfully ");
        cout << "Tournament Mode initiated" << endl;
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
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "assignreinforcement") && (command == "reinforce"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Assign reinforcement phase");
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "assignreinforcement") && (command == "issueorder"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Assign reinforcement phase");
        cout << "The entered command " << command << " is valid for state " << getState();
        transition("issueorders");
        cout << ", therefore the game is successfully transited to the next state " << getState() << ".\n";
        cout<<"--------------------------"<<endl;
        return true;
    }

    if((getState() == "issueorders") && (command == "execorder"))
    {
        getCommandProcessor()->getCommandList().back()->saveEffect("Issue Order Phase");
        cout << "The entered command " << command << " is valid for state " << getState() << ", the game remains in the state "
            << getState() << ".\n";
        transition("executeorders");
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
        players->clear();
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
        exit(0);
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


void GameEngine::setPlayersTerritories()
{
    int territoryCount = _map->numOfTerritories;
    int playerCount = players->size();
    int subLength = territoryCount / playerCount;
    int remainder = territoryCount % playerCount;
    int limit = min(playerCount, territoryCount);

    int startIndex = 1; //Start index is one because the first element in allTerritories is always null
    int endIndex = 0;

    for(int i = 0; i < limit; ++i) {
        endIndex += (remainder > 0) ? (subLength + !!(remainder--)) : subLength;
        //cout<<"start index: "<<startIndex<<"end index: "<<endIndex<<endl;
        vector <Territory*>* subTerritories = new vector<Territory*>();

        for (int j=startIndex;j<=endIndex;j++)
        {
            subTerritories->push_back(_map->territories->at(j));
            //cout<<_map->territories[j]->name<<endl;
        }
        for (int j=startIndex;j<=endIndex;j++)
        {
            _map->territories->at(j)->setPlayer(players->at(i));
            //cout<<_map->territories->at(j)->name<<"is given to: "<<_map->territories->at(j)->ownedplayer->getName()<<endl;
        }
        players->at(i)->setTerritories(subTerritories);
        startIndex = endIndex+1;
    }
}
void GameEngine::winner(string name,string strategy)
{
    winnername = name;
    strategyname= strategy;
}
bool GameEngine::gameOver()
{
    if (players->size()==1)
    {
        cout<<"Player "<<players->at(0)->getName()<<" has won the game!";
        transition("win");
        Order::deletePlayerCannotAttackList();
        winner(players->at(0)->getName(),players->at(0)->getStrategy());
        return true;
    }
    return false;
}
void GameEngine::removeLosingPlayers()
{
    int count = players->size();
    for (int i=0;i<count;i++)
        if (players->at(i)->getPointerToTerritories()->size()==0)
        {
            cout<<players->at(i)->getName()<<" has no more territories and is removed from the game\n Remaining players: "<< count-1<<endl;
            players->erase(players->begin()+i);
            count--;
        }
}
void GameEngine::mainGameLoop()
{
    string command;
    Order::setUpPlayerCannotAttackList();
    int turns = 0;
    do
    {
        if (turns == turnsPerGame)
        {
            winner("nobody","Draw");
            break;
        }
        removeLosingPlayers();
        if (gameOver()) break;
        transition("assignreinforcement");
        reinforcementPhase();
        transition("issueorders");
        issueOrdersPhase();
        transition("executeorders");
        executeOrderPhase();
        turns++;
    }
    while (!(getState() == "win") && !gameOver());
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
            if (command=="tournament")
            {
                tournament = true;
                tournamentMode(getCommandProcessor());
                return;
            }
            if((getState() == "start"||getState()=="maploaded") && (command.find("loadmap") !=string::npos))
            {
                string filename=command.substr(command.find("loadmap")+9);
                filename = filename.substr(0,filename.size()-1);
                maploader = new MapLoader(filename);
                _map = new Map(*maploader->Load());
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
                if (players->size()+1>MAXPLAYERS)
                {
                    getCommandProcessor()->getCommandList().back()->saveEffect("max number of players reached, failed to add this player");
                    cout<<"Maxiumum number of players reached, failed to add this player"<<endl;
                    continue;
                }
                string playername=command.substr(command.find("addplayer")+11);
                playername = playername.substr(0,playername.size()-1);
                tempPlayer = new Player(playername);
                players->push_back(tempPlayer);
            }
            if (command =="gamestart")
            {
                if (players->size()<MINPLAYERS)
                {
                    cout<<"Not enough players! please enter at least one more player"<<endl;
                    getCommandProcessor()->getCommandList().back()->saveEffect("Not enough players! At least one more player is needed");
                    transition("playersadded");
                    continue;
                }
                else
                {
                    // Distribute all territories to players in almost equald parts depending on the number of players
                    setPlayersTerritories();
                    //Randomize the order of play
                    randomizePlayOrder();

                    initializeDeck(); //Creating the Deck
                    for(int i = 0; i < players->size(); i++)
                    {
                        //Give 50 initial armies to each player's respective reinforcement pool
                        players->at(i)->setPool(50);
                        //Each player draws 2 initial cards from the deck
                        players->at(i)->getHand()->addCard(_deck->draw());
                        players->at(i)->getHand()->addCard(_deck->draw());

                        cout << *players->at(i) << endl;
                    }
                }
            }
        }
    }
    while (!(command=="gamestart"));
//    delete tempPlayer;
//    tempPlayer = NULL;
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
bool GameEngine::doesPlayerOwnContinent(int cnum,Player* player)
{
    int i;
    if (cnum==1) i=1;
    else
        i=_map->endofContinents[cnum-1]+1;
    for (i; i<= _map->endofContinents[cnum];i++)
    {
        //cout<<"checking territory "<<i<<endl;
        if (_map->territories->at(i)->ownedplayer != player)
            return false;
    }
    return true;
}

void GameEngine::reinforcementPhase(){

    cout << "\n--------------------------" << endl;
    cout << "Reinforcement Phase\n" << endl;
    int nCont = _map->getNumberOfContinents();
    for (int p=0;p<players->size();p++)
    {
        int numberOfArmies = (players->at(p)->getTerritories()->size())/3;

        for(int i = 1;i <= nCont;i++)
            if(doesPlayerOwnContinent(i, players->at(p)))
            {
                //cout<<" owns continent " <<i<<endl;
                numberOfArmies += _map->continentPoints[i-1];
            }
        if(numberOfArmies<3)
            numberOfArmies = 3;

        players->at(p)->addToPool(numberOfArmies);

        cout << "- Number of armies added to player's pool: " << numberOfArmies << "\n" << endl;
        cout << *players->at(p) << endl;
    }
}

//round-robin shift
bool GameEngine::shift()
{
    Player *tempPairs[3][2];
    int pairs = players->size()/2 +players->size()%2;

    if (pairs==1) return false;

    tempPairs[0][0]=playerPairs[0][0];
    tempPairs[0][1]=playerPairs[pairs-1][0];
    tempPairs[1][0]=playerPairs[pairs-1][1];

    for(int i=0;i<2;i++){
        for (int j = 0; j<pairs; j++)
        {
            if ((j==1)&&(i==0)) continue;
            if ((j==0)&&(i==1)) continue;
            if ((i==0)&&(j==0)) continue;
            tempPairs[j][i]=playerPairs[j-1][i];
        }
    }
    for(int i=0;i<2;i++)
        for (int j = 0; j<pairs; j++)
            playerPairs[j][i]=tempPairs[j][i];
}

void GameEngine::issueOrdersPhase()
{
    cout << "\n--------------------------" << endl;
    cout << "Issue Order Phase\n" << endl;
    int playerSize = players->size();
    //shift(); //round-robin fashion

    /*for (int i=0;i<playerSize;i++)
        cout<<*players->at(i);*/
    for(int i=0;i<playerSize;i++)
    {
        if (players->at(i)!=NULL)
        {
            if (players->at(i)->getStrategy()!="Cheater")
                players->at(i)->issueOrder();
        }
    }

}

void GameEngine::executeOrderPhase()
{

    int playerSize = players->size();
    OrdersList* pOrd;
    int counter=0;
    bool flag[6], flag2;
    cout << "--------------------------" << endl;
    cout << "Execute Order Phase\n" << endl;

    for (int i=0;i<playerSize;i++)
    {
        if (players->at(i)!=NULL)
        {
            pOrd = players->at(i)->ordersList;
            if (!pOrd->isEmpty())
            {
                while (pOrd->getFirstOrderType()=="Deploy")
                {
                    pOrd->executeFirstOrder();
                    if (pOrd->isEmpty()) break;
                }
            }
            else
                continue;
        }
    }
    for (int i=0;i<playerSize;i++)
       if (players->at(i)->getStrategy()=="Cheater")
           players->at(i)->issueOrder();
    for (int i=0;i<playerSize;i++)
        flag[i]=true;
    while (true)
    {
        pOrd = players->at(counter)->ordersList;
        if (pOrd->isEmpty()) flag[counter]=false;
        else
            pOrd->executeFirstOrder();
        flag2=false;
        for (int i=0;i<playerSize;i++)
            if (flag[i])
                flag2=true;
        if (!flag2)
            break;
        counter=(counter+1)%playerSize;
        pOrd=NULL;
    }
    for (int i=0;i<playerSize;i++)
        if(players->at(i)->getFlagConqTerr())
        {
            players->at(i)->getHand()->addCard(_deck->draw());
            players->at(i)->setFlagConqTerr(false);
        }
    Order::clearPlayerCannotAttackList();
}
