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
Map::Map(vector<int>* adjacency,vector<Territory*> listOfTerritories,int nOfContinents,int nOfTerritories,int endOf[],vector<int> contPoints)
{
    this->adjacencyList=adjacency;

    for(vector<Territory*>::iterator it = listOfTerritories.begin(); it != listOfTerritories.end(); ++it)
        this->territories.push_back(*it);

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
    territories.clear();
    adjacencyList = NULL;
}
Map::Map(const Map& m)
{
    this->adjacencyList=m.adjacencyList;

    for(vector<Territory*>::const_iterator it = m.territories.begin(); it != m.territories.end(); ++it)
        this->territories.push_back(*it);

    this->numOfContinents = m.numOfContinents;

    this->numOfTerritories = m.numOfTerritories;

    for (int i = 1; i<=numOfContinents;i++)
        this->endofContinents[i]=m.endofContinents[i];
    for(vector<int>::const_iterator it = m.continentPoints.begin(); it != m.continentPoints.end(); it++)
        this->continentPoints.push_back(*it);
}
Map::Map()
{
    numOfContinents = 0;
    numOfTerritories = 0;
}
//assignment operator
Map& Map::operator=(const Map& m)
{
    this->adjacencyList = m.adjacencyList;
    this->territories = m.territories;
    this->numOfContinents = m.numOfContinents;
    this->numOfTerritories = m.numOfTerritories;
    return *this;
}



bool Map::isAdjacentto(Territory t1, Territory t2)
{
    int index1=0,index2;
    for (int i = 1; i<= numOfTerritories;i++)
        if (territories[i]->getName() == t1.getName())
                index1= i;
    for (int i = 1; i<= numOfTerritories;i++)
        if (territories[i]->getName() == t2.getName())
                index2= i;
    cout<<index1<<" "<<index2<<endl;
    for (auto x: adjacencyList[index1])
        if (x == index2)
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
            if (territories[i]->getName() == territories[j]->getName()
                && territories[i]->getContinent()!=territories[j]->getContinent())
            {
                cout<<"Territory "<<territories[i]->getName()<<" is defined in more than one continent! Map is invalid.";
                return false;
            }
    }
    for (int i = 1; i<=numOfContinents; i++)
    {
        for (int j = startOf; j<=endofContinents[i];j++)
        {
            t = false;
            for (auto x: adjacencyList[j])
            {
                if (x<=endofContinents[i] &&x>=startOf) //checks if this territory is connected to at least one other territory in this continent
                    t= true;
                if (territories[x]->continentNumber!=territories[j]->continentNumber)
                {
                    AllContinents[territories[x]->continentNumber] = true; //this two continents connect
                    AllContinents[territories[j]->continentNumber] = true;
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
    adjacencyList = adjacency;
}
void Map::setTerritories(vector<Territory*> t)
{
    territories = t;
}
vector <Territory*> Map::getTerritories() const
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
    isUnderAttack = false;
}
Territory::Territory()
{

}
Territory::~Territory()
{
    adjacentTerritories.clear();
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
bool Territory::isAdjacentTo(Territory &t2)
{
    for (auto x: adjacentTerritories)
        if (x->getTerritoryNum() == t2.getTerritoryNum())
            return true;
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
    Map* m;
    string s;
    int endOf[100];
    ifstream inputstream(filepath);
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
    vector<Territory*> territories;
    Territory t;
    cnumber = 1;
    territories.push_back(&t); //add a null, so our territory number starts with 1 not 0
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
            territories.push_back(t);
        }
        round = (round+1)%5;
    }
    endOf[numOfContinents] = numOfTerritories-1;

    numOfTerritories--; //exclude [borders]

    static vector<int> adjacency[200];

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
                adjacency[u].push_back(v);
            territories[u]->adjacentTerritories.push_back(territories[v]);
        }
        if (inputstream.peek()=='\n')
            flag=true;
        inputstream>>s;
    }
    inputstream.close();
    m = new Map(adjacency,territories,numOfContinents,numOfTerritories,endOf,contPoints);
   /* m.setNumberOfContinents(numOfContinents);
    m.setNumberOfTerritories(numOfTerritories);
    m.setEndOfContinents(endOf);
    m.setTerritories(territories);
    m.setAdjacency(adjacency);
    m.setContinentPoints(contPoints);*/
    //PrintList(m.adjacencyList,numOfTerritories); //test of adjacency list

    return m;
}
int Map::getNumberOfContinents() {
    return numOfContinents;
}
int* Map::getEndOfContinents() {
    return endofContinents;
}

