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

}
ofstream LogObserver::logOutput;
//Opens the output stream to the file. Should be called at the beginning of the program.
void LogObserver::openOutput()
{
    logOutput.open("gamelog.txt");
}
//Closes the output stream to the file. Should be called at the end of the program.
void LogObserver::closeOutput()
{
    logOutput.close();
}
//Update method
void LogObserver::Update(ILoggable* ILog)
{
    //Creates and output stream
    /*
    ofstream output;
    output.open("gamelog.txt");
    output << ILog->stringToLog() << endl;
    output.close();
    */
    logOutput << ILog->stringToLog() << endl;
}
