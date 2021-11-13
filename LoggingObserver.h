#ifndef LOGGINGOBSERVER_H_INCLUDED
#define LOGGINGOBSERVER_H_INCLUDED
#include <iostream>
#include <list>
#include <fstream>
//Forward Declarations
class Subject;
class ILoggable;
class Observer;
class LogObserver;

using std::string;
using std::list;
using std::ofstream;
using std::ostream;
//Abstract classes
class ILoggable
{
public:
    virtual string stringToLog()=0;
    virtual ~ILoggable();
protected:
    ILoggable();
};

class Subject
{
public:
    Subject();
    virtual ~Subject();
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
    LogObserver& operator = (const LogObserver& log);
    LogObserver(const LogObserver& log);
    friend ostream& operator <<(ostream &strm, const LogObserver &log);
    static ofstream output;
};
#endif // LOGGINGOBSERVER_H_INCLUDED
