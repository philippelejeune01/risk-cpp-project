#include "CommandProcessing.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;
/**
*Default constructor that creates a Command object, which command and effect are both initialized to "".
*/
Command::Command()
{
    this->command = "";
    this->effect = "";
}
/**
*Parameterized constructor that creates a Command object, which command is initialized to the passed c as a parameter
*and effect is initialized to the passed e as a parameter.
*@param c is a string that corresponds to the desired command of the Command object.
*@param e is a string that corresponds to the desired effect of the Command object.
*/
Command::Command(string c, string e)
{
    this->command = c;
    this->effect = e;
    lo = new LogObserver();
    Attach(lo);
}
/**
*Copy constructor that creates a Command object, which is a copy of the passed object.
*@param c is a constant reference to its own class type (Command class in this case).
*/
Command::Command(const Command& c)
{
    this->command = c.command;
    this->effect = c.effect;
}
/**
*Overloaded assignment operator that replaces the contents of an exiting Command object with the passed Command object.
*@param c is a constant reference to its own class type (Command class in this case).
*@return the current object by reference.
*/
Command& Command::operator = (const Command& c)
{
    this->command = c.command;
    this->effect = c.effect;
    return *this;
}
/**
*Getter method that returns the current command of a Command object.
*@return a string that corresponds to the current command of a Command object.
*/
string Command::getCommand()
{
    return this->command;
}
/**
*Getter method that returns the current effect of a Command object.
*@return a string that corresponds to the current effect of a Command object.
*/
string Command::getEffect()
{
    return this->effect;
}
/**
*Setter method that sets the command of a Command object.
*@param c is a string that corresponds to the new command of a Command object.
*/
void Command::setCommand(string c)
{
    this->command = c;
}
/**
*Setter method that sets the effect of a Command object.
*@param e is a string that corresponds to the new effect of a Command object.
*/
void Command::setEffect(string e)
{
    effect = e;
}
/**
*stringToLog method that creates a string that stores the effect of the Command.
*@return a string that stores the effect of the Command.
*/
string Command::stringToLog()
{
    string s = getEffect();
    s = ("Command's effect: " + s);
    return s;
}

/**
*Saves the effect of a Command object.
*@param eff is a string that corresponds to the new effect of a Command object.
*/
void Command::saveEffect(string eff)
{
    setEffect(eff);
    Notify(this);
}
/**
*Overloaded stream insertion operator that outputs the current command and effect of the Command object.
*@param out is a reference to the ostream class type.
*@param c is a reference to the Command class type.
*/
std::ostream &operator << (std::ostream &out, const Command &c)
{
    out << "command: "
    << c.command << endl
    << "effect : "
    << c.effect << endl;
    return out;
}


/**
*Default constructor that creates a CommandProcessor object, which has an empty list of Command objects.
*/
CommandProcessor::CommandProcessor()
{
    list<Command*> l;
    this->lc = l;
    lo = new LogObserver();
    Attach(lo);
}
/**
*Parameterized constructor that creates a CommandProcessor object, which list of Command objects is initialized to the passed lc as a parameter.
*@param lc is a list of Command objects that corresponds to the desired list of Command objects of the CommandProcessor object.
*/
CommandProcessor::CommandProcessor(list<Command*> lc)
{
    this->lc = lc;
}
/**
*Destructor that deletes the each Command object from the list of Command objects of the CommandProcessor object.
*/
CommandProcessor::~CommandProcessor()
{
    while(!lc.empty()) delete lc.front(), lc.pop_front();
    lc.clear();
}
/**
*Copy constructor that creates a CommandProcessor object, which is a copy of the passed object.
*@param cp is a constant reference to its own class type (CommandProcessor class in this case).
*/
CommandProcessor::CommandProcessor(const CommandProcessor& cp)
{
    this->lc = cp.lc;
}
/**
*Overloaded assignment operator that replaces the contents of an exiting CommandProcessor object with the passed CommandProcessor object.
*@param cp is a constant reference to its own class type (CommandProcessor class in this case).
*@return the current object by reference.
*/
CommandProcessor& CommandProcessor::operator = (const CommandProcessor& cp)
{
    this->lc = cp.lc;
    return *this;
}
/**
*Getter method that returns the current list of Command objects of a CommandProcessor object.
*@return a list of Command objects that corresponds to the current list of Command objects of a CommandProcessor object.
*/
list<Command*> CommandProcessor::getCommandList()
{
    return lc;
}
/**
*Setter method that sets the list of Command objects of a CommandProcessor object.
*@param lc is a list of Command objects that corresponds to the new list of Command objects of a CommandProcessor object.
*/
void CommandProcessor::setCommandList(list<Command*> lc)
{
    lc = lc;
}
/**
*saveCommand stores the Command objects in a list.
*/
void CommandProcessor::saveCommand(Command* obj)
{
    lc.push_back(obj);
    Notify(this);
}
/**
*stringToLog method that creates a string that stores the command of the CommandProcessor.
*@return a string that stores the command of the CommandProcessor.
*/
string CommandProcessor::stringToLog()
{
    string s = getCommandList().back()->getCommand();
    s = ("Command: " + s);
    return s;
}

/**
*getCommand reads the command from the console, stores this command in a string, creats a Command object based on the entered command,
*saves the Command object in a list of Command objects of the CommandProcessor objects and then returns the stored command.
*@return a string that corresponds to the command entered by the user.
*/
std::string CommandProcessor::getCommand()
{
    string command = readCommand();
    Command* c = new Command(command, " ");
    saveCommand(c);
    return command;
}
/**
*readCommand reads the command from the console, stores this command in a string and then returns the stored command.
*@return a string that corresponds to the command entered by the user.
*/
std::string CommandProcessor::readCommand()
{
    string command;
    cout << "\nPlease enter a valid command:" << endl;
    getline(std::cin, command);
    return command;
}
/**
*Overloaded stream insertion operator that outputs the current list of Command objects of the CommandProcessor object.
*@param out is a reference to the ostream class type.
*@param cp is a reference to the CommandProcessor class type.
*/
std::ostream & operator << (std::ostream &out, const CommandProcessor &cp)
{
    list<Command*> l = cp.lc;
    out << "The list of commands is:\n" << endl;
    for (const auto& i: l)
    {
        out << *(i) << endl;
    }
    return out;
}

/**
*Parameterized constructor that creates a FileLineReader object, which filename is initialized to the passed f as a parameter and opened by ifstream stream.
*@param lf is a string that corresponds to the desired filename of FileLineReader object.
*/
FileLineReader::FileLineReader(string f)
{
    filename = f;
    stream.open(filename);
}
/**
*Destructor that closes the ifstream of the FileLineReader object.
*/
FileLineReader::~FileLineReader()
{
    stream.close();
}
/**
*Copy constructor that creates a FileLineReader object, which is a copy of the passed object.
*@param flr is a constant reference to its own class type (FileLineReader class in this case).
*/
FileLineReader::FileLineReader(const FileLineReader& flr)
{
    filename = flr.filename;
    stream.open(filename);
}
/**
*readLineFromFile reads the command from the file, stores this command in a string and then returns the stored command.
*@return a string that corresponds to the command stored in the file.
*/
string FileLineReader::readLineFromFile()
{
    string line;
    //if (stream.peek()==EOF) { cout<<"end of test file"; exit(0); }
    getline(stream, line);
    return line;
}
/**
*Overloaded stream insertion operator that outputs the current filename of FileLineReader object.
*@param out is a reference to the ostream class type.
*@param flr is a reference to the FileLineReader class type.
*/
std::ostream & operator << (std::ostream &out, const FileLineReader &flr)
{
    out << "The file name is: " << flr.filename << endl;
    return out;
}

/**
*Parameterized constructor that creates a FileCommandProcessorAdapter object, which FileLineReader object is initialized to the passed obj as a parameter.
*@param obj is a FileLineReader object that corresponds to the desired FileLineReader object of FileCommandProcessorAdapter object.
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* obj)
{
    flr = obj;
}
/**
*Destructor that deletes the each FileLineReader object of the FileCommandProcessorAdapter object.
*/
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete flr;
   flr = NULL;
}
/**
*Copy constructor that creates a FileCommandProcessorAdapter object, which is a copy of the passed object.
*@param fcpa is a constant reference to its own class type (FileCommandProcessorAdapter class in this case).
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcpa)
{
    flr = fcpa.flr;
}
/**
*Overloaded assignment operator that replaces the contents of an exiting FileCommandProcessorAdapter object with the passed FileCommandProcessorAdapter object.
*@param fcpa is a constant reference to its own class type (FileCommandProcessorAdapter class in this case).
*@return the current object by reference.
*/
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator = (const FileCommandProcessorAdapter& fcpa)
{
    flr = fcpa.flr;
    return *this;
}

FileLineReader* FileCommandProcessorAdapter::getFileLineReader()
{
    return flr;
}
/**
*readCommand overrides the readCommand from CommandProcessor class, it reads the command using the readLineFromFile method from FileLineReader,
*stores this command in a string and then returns the stored command.
*@return a string that corresponds to the command stored in the file.
*/
string FileCommandProcessorAdapter::readCommand()
{
    string command = flr->readLineFromFile();
    return command;
}
