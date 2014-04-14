#include <iostream>
#include <commandmanager.h>
#include <QTime>
#include <qglobal.h>

typedef VirtualMemoryManager VMM;

int main(/*int argc, char *argv[]*/)
{
    srand(2245);
    cout<<"Starting Virtual Memory Manager"<<endl;
    CommandManager cmd_manager;

    cout<<"Creating Commands"<<endl;
    //int nb_commands = 10000;
    int nb_commands = 256;
    char random_chars;
    for(int i=0; i < nb_commands; ++i)
    {
        Command::ActionType action_type = Command::READ;
        if((rand()%100)>50)
        {
            action_type = Command::WRITE;
            random_chars =  (char)(rand() % ('z' - 'a' + 1) + 'a');
        }
        Command c("Command",action_type,( (rand()%32))*(rand()%16),rand()%256, random_chars );
        cmd_manager.insertCommand(c);
    }
    cmd_manager.applyCommands();


    /*Printing static TBLHIT and PAGEFAULT counter from VirtualMemoryManager*/
    cout << "TLB hit ratio: " << VMM::TLBHIT / (VMM::TLBHIT+VMM::TLBMISS)
         << "; Page fault ratio: " << VMM::PAGEFAULT / (VMM::PAGEFAULT + VMM::PAGEFOUND) <<endl;

    cout<<"Exiting Virtual Memory Manager"<<endl;
    return 0;
}
