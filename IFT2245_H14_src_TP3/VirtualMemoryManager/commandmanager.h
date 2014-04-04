#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <object.h>
#include <list>
#include <command.h>

class CommandManager:public TObject
{
public:

    typedef list<Command> CommandList;

    CommandManager();

    ~CommandManager();

    void insertCommand(Command &cmd);

    void clearAllCommands();

    void applyCommands();

private:

    CommandList mCommandList;
    VirtualMemoryManager mVirtualMemoryManager;

};

#endif // COMMANDMANAGER_H
