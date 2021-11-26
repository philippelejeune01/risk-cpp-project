#include "Map.h"
#include<iostream>
using namespace std;

void PrintList(vector<int>* adjacency,int total) //represent the graph for test of adjacency, not a class member function
{
    bool flag = false;
    for (int i = 1; i < total; ++i)
    {
        cout << "\nTerritory " << i << " connects to: ";
        for (auto x : adjacency[i])
        {
            cout << " " << x;
            flag=true;
        }
        if (!flag)
            cout<<"This is not a valid map!";
        flag=false;
    }
    cout<<endl;
}
//constructors and destructor:
Map::Map(vector<Territory*>* listOfTerritories,int nOfContinents,int nOfTerritories,int endOf[],vector<int> contPoints)
{
    territories = new vector<Territory*>();
    for(int i=0;i<listOfTerritories->size();i++)
        territories->push_back(new Territory(*listOfTerritories->at(i)));
    this->numOfContinents = nOfContinents;

    this->numOfTerritories = nOfTerritories;

    for (int i = 1; i<=numOfContinents;i++)
        this->endofContinents[i]=endOf[i];
    //cout<<"Continent point size"<<contPoints.size()<<endl;
    for(vector<int>::iterator it = contPoints.begin(); it != contPoints.end(); it++)
        this->continentPoints.push_back(*it);
}
Map::~Map()
{
    territories->clear();
    //delete territories;
    //delete adjacencyList;
}
Map::Map(const Map& m)
{
    territories = new vector<Territory*>();
    for(int i=0;i<m.territories->size();i++)
        this->territories->push_back(new Territory(*m.territories->at(i)));

    this->numOfContinents = m.numOfContinents;

    this->numOfTerritories = m.numOfTerritories;

    for (int i = 1; i<=numOfContinents;i++)
        this->endofContinents[i]=m.endofContinents[i];
    for(int i=0;i<m.continentPoints.size();i++)
        this->continentPoints.push_back(m.continentPoints[i]);
}
Map::Map()
{
    numOfContinents = 0;
    numOfTerritories = 0;
}
//assignment operator
Map& Map::operator=(const Map& m)
{
    territories = new vector<Territory*>();
    for(int i=0;i<m.territories->size();i++)
        this->territories->push_back(m.territories->at(i));

    this->numOfContinents = m.numOfContinents;

    this->numOfTerritories = m.numOfTerritories;

    for (int i = 1; i<=numOfContinents;i++)
        this->endofContinents[i]=m.endofContinents[i];
    for(int i=0;i<m.continentPoints.size();i++)
        this->continentPoints.push_back(m.continentPoints[i]);
    return *this;
}



bool Map::isAdjacentto(Territory* t1, Territory* t2)
{
    int index1=0,index2;
    /*for (int i = 1; i<= numOfTerritories;i++)
        if (territories->at(i)->getName() == t1.getName())
                index1= i;
    for (int i = 1; i<= numOfTerritories;i++)
        if (territories->at(i)->getName() == t2.getName())
                index2= i;
    cout<<index1<<" "<<index2<<endl;*/
    for (auto x: *t1->adjacentTerritories)
        if (x == t2)
            return true;
    return false;

}
//stream operator
ostream& operator<<(ostream& strm, Map& m)
{
    /*for (int i = 1; i < m.territories.size();i++)
    {
        strm<<m.territories.at(i).getTerritoryNum()<<" ";
        for (int j = 0; j < m.territories.at(i).adjacentTerritories.size();j++)
            strm<<m.territories.at(i).adjacentTerritories.at(j)->getTerritoryNum()<<" ";
        strm<<endl;
    }*/

    /*if (m.territories[1].isAdjacentTo(m.territories[18]))  //checking to see if vectors are correctly stored in each territory object
        strm<<"connected"<<endl;
    else
        strm<<"not connected"<<endl;*/

    strm <<"Number of Territories in this map: "<< m.numOfTerritories <<endl;
    strm <<"Number of Continents in this map: "<< m.numOfContinents<<endl;
    //for (int i=1;i<=m.numOfContinents;i++)
     //   cout<< "end of continent "<<i<<" : "<<m.endofContinents[i]<<endl;
    return strm;
}

bool Map::validate() //checks if a given map is valid
{
    bool Continent=false,AllContinents[numOfContinents+1]={false},t;
    int startOf = 1;
    for (int i = 1; i<=numOfTerritories; i++) //checks that each country belongs to only one continent
    {
        for (int j = i+1; j<=numOfTerritories;j++)
            if (territories->at(i)->getName() == territories->at(j)->getName()
                && territories->at(i)->getContinent()!=territories->at(j)->getContinent())
            {
                cout<<"Territory "<<territories->at(i)->getName()<<" is defined in more than one continent! Map is invalid.";
                return false;
            }
    }
    for (int i = 1; i<=numOfContinents; i++)
    {
        for (int j = startOf; j<=endofContinents[i];j++)
        {
            t = false;
            for (auto x: *territories->at(j)->adjacentTerritories)//adjacencyList[j])
            {
                if (x->continentNumber == territories->at(j)->continentNumber) //checks if this territory is connected to at least one other territory in this continent
                    t= true;
                if (x->continentNumber!=territories->at(j)->continentNumber)
                {
                    AllContinents[x->continentNumber] = true; //this two continents connect
                    AllContinents[territories->at(j)->continentNumber] = true;
                }
            }
            if (!t) //continent is not interconnected
            {
                cout<<"Territory "<<j<<" not connected"<<endl;
                cout<< "not a valid map! Continent "<<i<<" is not interconnected."<<endl;
                return false;
            }
        }
        startOf= endofContinents[i]+1;
    }
    for (int i = 1; i<=numOfContinents;i++)
        if (!AllContinents[i]) //this continent is not connected to any other continent
        {
            cout<<"not a valid map! Continent "<<i<<" is not connected to any other continent"<<endl;
            return false;
        }

    cout<<"Map is valid!"<<endl; //Every condition was met
    return true;
}

void Map::setAdjacency(vector<int>* adjacency)
{
    //adjacencyList = adjacency;
}
void Map::setTerritories(vector<Territory*>* t)
{
    territories = t;
}
vector <Territory*>* Map::getTerritories() const
{
    return territories;
}
void Map::setNumberOfContinents(int n)
{
    numOfContinents = n;
}
void Map::setContinentPoints(vector<int> contPoints)
{
    for(vector<int>::iterator it = contPoints.begin(); it != contPoints.end(); ++it)
        cout<<*it;
        //continentPoints.push_back(*it);
}
void Map::setEndOfContinents(const int* arr)
{
    for (int i = 1; i <= numOfContinents; i++)
        endofContinents[i]=arr[i];
}

void Map::setNumberOfTerritories(int n)
{
    numOfTerritories = n;
}
Territory::Territory(int tnum,int x,int y,int c,int num,Player* ownedP, string n)
{
    TerritoryNumber = tnum;
    xCoordinate = x;
    yCoordinate = y;
    continentNumber = c;
    amountOfArmies = num;
    ownedplayer = ownedP;
    name = n;
    adjacentTerritories = new vector<Territory*>();
    isUnderAttack = false;
}
Territory::Territory(const Territory& t)
{
    this->TerritoryNumber = t.TerritoryNumber;
    this->xCoordinate = t.xCoordinate;
    this->yCoordinate = t.yCoordinate;
    this->continentNumber = t.continentNumber;
    this->amountOfArmies = t.amountOfArmies;
    this->ownedplayer = t.ownedplayer;
    this->name = t.name;
    adjacentTerritories = new vector<Territory*>();
    this->adjacentTerritories = t.adjacentTerritories;
    isUnderAttack = false;
}
Territory::Territory()
{
    adjacentTerritories = new vector<Territory*>();
}
Territory::~Territory()
{
    adjacentTerritories->clear();
    delete adjacentTerritories;
    ownedplayer = NULL;
}
void Territory::setContinent(int c)
{
    continentNumber=c;
}

void Territory::setName(string n)
{
    name=n;
}
void Territory::setCoordinates(int x, int y)
{
    xCoordinate = x;
    yCoordinate = y;
}
void Territory::setTerritoryNum(int t)
{
    TerritoryNumber = t;
}
int Territory::getTerritoryNum()
{
    return TerritoryNumber;
}
void Territory::setPlayer(Player* p)
{
    ownedplayer = p;
}
Player* Territory::getPlayer()
{
    return ownedplayer;
}
int Territory::getContinent()
{
    return continentNumber;
}
string Territory::getName()
{
    return name;
}
int Territory::getAmountOfArmies()
{
    return amountOfArmies;
}
void Territory::setAmountOfArmies(int nOfArmies)
{
    amountOfArmies = nOfArmies;
}
bool Territory::isTerritoryUnderAttack()
{
    return isUnderAttack;
}
void Territory::setAttackStatus(bool attack)
{
    isUnderAttack = attack;
}
bool Territory::isAdjacentTo(Territory* t2)
{
    for (auto x: *this->adjacentTerritories)
    {
        if (x->getTerritoryNum() == t2->getTerritoryNum())
        {
            return true;
        }

    }
    return false;
}
ostream& operator <<(ostream &strm, const Territory &terr)
{
    return strm << terr.name << ": Continent: " << terr.continentNumber << ": nOfArmies: " << terr.amountOfArmies;
}
MapLoader::MapLoader(string fpath)
{
    filepath=fpath;
}
Map* MapLoader::Load()
{
    string s;
    int endOf[100];
    ifstream inputstream(filepath);
    vector<Territory*>* territories = new vector<Territory*>;
    int u, v;
    Territory* f;
    int numOfTerritories=0,numOfContinents=0,i;
    vector<int> contPoints;
    string name;
    int x,y,cnumber;
    int round=0,integer=0;
    bool flag=false;

    while (s!="[continents]") //skip over the [files] in the .map file
        inputstream>>s;
    inputstream>>s;
    while (s!="[countries]")
    {
        inputstream>>s;
        if (numOfContinents%3==0) contPoints.push_back(stoi(s));
        numOfContinents++;
    }
    //for(vector<int>::iterator it = contPoints.begin(); it != contPoints.end(); ++it)
    //    cout<<*it<<endl;

    numOfContinents/=3;


    cnumber = 1;
    Territory *t= new Territory();
    territories->push_back(t);
    while (s!="[borders]" )
    {
        inputstream>>s;
        if (round==0) numOfTerritories++;
        if (round==1) { name=s;
        // t.setName(name);
        }
        if (round==2) {
                        if (stoi(s)!=cnumber)
                            endOf[cnumber]=numOfTerritories-1;
                        cnumber=stoi(s);
                        //t.setContinent(cnumber);
                      }
        if (round==3) x=stoi(s);
        if (round==4) {
            y=stoi(s);
            Territory* t= new Territory(numOfTerritories,x,y,cnumber,0,NULL,name);
            //t.setCoordinates(x,y);
            //t.setTerritoryNum(numOfTerritories);
            territories->push_back(t);
        }
        round = (round+1)%5;
    }

    endOf[numOfContinents] = numOfTerritories-1;

    numOfTerritories--; //exclude [borders]

    while (!inputstream.eof())
    {
        if (flag) //start of each border, if true, first value read is head of the connection
        {
            if (inputstream.peek()==EOF) break;
            u=stoi(s); //connection head
            flag=false;
        }
        else
        {
            if(s!="[borders]")
                v=stoi(s);//if we're reading a number,this is where the head is connecting to.
            if (u!=0)
                territories->at(u)->adjacentTerritories->push_back(territories->at(v));
        }
        if (inputstream.peek()=='\n')
            flag=true;
        inputstream>>s;
    }
    inputstream.close();
    Map* m=new Map(territories,numOfContinents,numOfTerritories,endOf,contPoints);
    return m;
}
int Map::getNumberOfContinents() {
    return numOfContinents;
}
int* Map::getEndOfContinents() {
    return endofContinents;
}

