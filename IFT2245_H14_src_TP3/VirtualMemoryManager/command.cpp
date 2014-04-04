#include "command.h"

Command::Command(QString str, ActionType action, uint page_number, uint offset, char data):
    TObject(str),mActionRequired(action),mPageNumber(page_number),mOffset(offset),mData(new char(data))
{

}

void Command::apply(VirtualMemoryManager *vmm)
{
    cout << "Applying Command : " <<endl;
    switch(mActionRequired)
    {
    case READ :
        cout << "READ(1). Page : " << mPageNumber << ". Offset : "<< mOffset << endl;
        vmm->read(mPageNumber,mOffset,mData);
        cout << "READ(2). Value Read from Virtual Memory Manager : "<< *mData << endl;
        break;
    case WRITE :
        cout << "WRITE(1). Page : " << mPageNumber << ". Offset : "<< mOffset << " Data : "<< *mData << endl;
        vmm->write(mPageNumber,mOffset,mData);
        cout << "WRITE(2). " << endl;
        break;
    default :
        cerr<<"WRONG COMMAND"<<endl;
        assert(false);
    }
}
