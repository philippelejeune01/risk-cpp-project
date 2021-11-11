#ifndef LOGGINGOBSERVER_H_INCLUDED
#define LOGGINGOBSERVER_H_INCLUDED
#include <iostream>
#include <list>

//Forward Declarations
class Subject;
class ILoggable;
class Observer;
class LogObserver;

using std::string;
using std::list;

//Abstract classes
class ILoggable
{
public:
    virtual string stringToLog()=0;
protected:
    ILoggable();
};

class Subject
{
public:
    Subject();
    ~Subject();
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* Ilog);
private:
    list<Observer*>* observers;
};

class Observer
{
public:
    virtual ~Observer();
    virtual void Update(ILoggable* Ilog) = 0;
protected:
    Observer();
};

class LogObserver: public Observer
{
public:
    ~LogObserver();
    LogObserver();
    void Update(ILoggable* Ilog);
};
#endif // LOGGINGOBSERVER_H_INCLUDED