#ifndef COMMAND_H
#define COMMAND_H

#include <object.h>
#include <virtualmemorymanager.h>

class Command:public TObject
{
public:

    typedef enum{READ = 0, WRITE = 1} ActionType;

    Command(QString str, ActionType action, uint page_number, uint offset, char data);

    /**
     * @brief apply
     * Apply the command.
     * ActionType == READ. At the end of this function mData should contain the data retrieved from the memory manager for a READ operation.
     * ActionType == WRITE. At the end of this function the information has been uploaded to logical memory.
     */
    void apply(VirtualMemoryManager * vmm);

private:
    ActionType mActionRequired;
    uint mPageNumber;
    uint mOffset;
    char* mData;

};

#endif // COMMAND_H
