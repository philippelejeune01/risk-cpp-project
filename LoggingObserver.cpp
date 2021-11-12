#include "LoggingObserver.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
using std::list;
using std::ofstream;
using std::string;
using std::endl;
using std::cout;
using std::ostream;
//ILoggable constructor. It is an interface
ILoggable::ILoggable()
{

}
ILoggable::~ILoggable()
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

}


ofstream LogObserver::output;
//assignment operator
LogObserver& LogObserver::operator = (const LogObserver& log)
{
    return *this;
}
//copy constructor
LogObserver::LogObserver(const LogObserver& log)
{

}
//stream insertion operator
ostream& operator <<(ostream &strm, const LogObserver &log)
{
    strm <<"Sending data to log file \"gamelog.txt\" \n";
    return strm;
}
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
