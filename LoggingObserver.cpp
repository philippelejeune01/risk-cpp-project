#include "LoggingObserver.h"
#include <iostream>
#include <list>
#include <fstream>
using std::list;
using std::ofstream;
using std::string;
using std::endl;
using std::cout;
//ILoggable constructor. It is an interface
ILoggable::ILoggable()
{

}
//Subject class implementation
//Constructor
Subject::Subject()
{
    observers = new list<Observer*>;
}
Subject::~Subject()
{
    observers->clear();
    delete observers;
}
//Necessary methods for a Subject
//
void Subject::Attach(Observer* o)
{
    observers->push_back(o);
}
void Subject::Detach(Observer* o)
{
    observers->remove(o);
}
void Subject::Notify(ILoggable* ILog)
{
    for(list<Observer*>::iterator it = observers->begin(); it != observers->end(); ++it)
    {

        (*it)->Update(ILog);
    }
}
//Observer class implementation
Observer::Observer()
{

}
Observer::~Observer()
{
    //Does something
}

//LogObserver class Implementation
LogObserver::LogObserver():Observer()
{

}
LogObserver::~LogObserver()
{
    //output.close();
}
//This erases the content of the file gamelog.txt
ofstream LogObserver::output;
//Update method
void LogObserver::Update(ILoggable* ILog)
{
    //Creates and output stream

    if (!output.is_open())
    {
        output.open("gamelog.txt");
        output << ILog->stringToLog() << endl ;
    }
    else
        output << ILog->stringToLog() << endl;
}
