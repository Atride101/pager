#include "virtualmemorymanager.h"

float VirtualMemoryManager::TLBHIT = 0;
float VirtualMemoryManager::TLBMISS = 0;
float VirtualMemoryManager::PAGEFAULT = 0;
float VirtualMemoryManager::PAGEFOUND = 0;

VirtualMemoryManager::VirtualMemoryManager(QString str, uint nb_pages, uint page_size, uint nb_frames):
    TObject(str),mNbPages(nb_pages),mPageSize(page_size),mNbFrames(nb_frames)/*,
              mRdNumberDistribution(uniform_int_distribution<int>(0,nb_frames-1)),
              dice(std::bind ( mRdNumberDistribution, mRdNumberGenerator ))*/
{
    cout<<"Virtual Memory Initialization"<<endl;

    cout<<"Hard Drive Initialization"<<endl;
    mHardDrive = new HardDrive("Hard_Drive",nb_pages,page_size);

    cout<<"Page Table Initialization"<<endl;
    mPageTable = new PageTable("Page table",nb_pages);

    cout<<"Physical Memory Initialization"<<endl;
    mPhysicalMemory = new PhysicalMemory("Physical Memory",nb_frames);

    cout<<"Translation Look-aside Buffer (TLB) Initialization"<<endl;
    mTLB = new TLB("Translation Look-aside Buffer");

    cout <<"Output log Initialisation" << endl;
    QFile::remove("log.txt");
    mLogFile = new QFile("log.txt");
    if(!mLogFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        cerr<<"Could not open "<<mLogFile->fileName().toStdString()<<endl;
        assert(false);
        return;
    }

}


VirtualMemoryManager::~VirtualMemoryManager()
{
    //Before deleting hard drive and physical memory
    //We need to save modified frames to disk
    saveRAMToDisk();

    delete mHardDrive;
    delete mPageTable;
    delete mPhysicalMemory;
    delete mTLB;

    mLogFile->close();
    delete mLogFile;
}

void VirtualMemoryManager::outputToLog( char* data )
{
    /*DO NOT MODIFY THIS FUNCTION*/
    cout << "Read Data: " << *data << endl;
    QByteArray page;
    page.resize(1);
    page[0]=*data;
    mLogFile->write(data, 1);

}

void VirtualMemoryManager::saveRAMToDisk()
{
    //TP2_IFT2245_TO_DO

    for (uint frame_number = 0; frame_number < mNbFrames; frame_number++) {
        if (mPhysicalMemory->isFrameModified(frame_number)) {
            uint page_number = mPhysicalMemory->pageNumber(frame_number);
            mHardDrive->write(page_number, mPhysicalMemory->frame(frame_number));
            mPhysicalMemory->setUnModified(frame_number);
        }
    }

    //TP2_IFT2245_END_TO_DO
}


void VirtualMemoryManager::read(uint page_number, uint offset, char *data)
{
    cout<<"Read Operation : ";
    //TP2_IFT2245_TO_DO

    uint frame_number = fetchPage(page_number);
    mPhysicalMemory->read(frame_number, offset, data);

    //TP2_IFT2245_END_TO_DO

    //Do not remove this function
    outputToLog(data);
}

void VirtualMemoryManager::write(uint page_number, uint offset, char *data)
{
    cout<<"Write Operation : ";
    //TP2_IFT2245_TO_DO

    uint frame_number = fetchPage(page_number);
    mPhysicalMemory->write(frame_number, offset, data);
    saveRAMToDisk();

    //TP2_IFT2245_END_TO_DO
}

uint VirtualMemoryManager::fetchPage(uint page_number)
{
    //TP2_IFT2245_TO_DO

    int frame_number;
    int page_number_int = (int) page_number;

    if (mTLB->findPage(page_number_int, frame_number)) {
        TLBHIT += 1;
        return (uint) frame_number;
    }
    else if (mPageTable->frameIndex(page_number, frame_number)) {
        TLBMISS += 1;
        PAGEFOUND += 1;
        mTLB->addTLBEntry(TLB::TLB_entry(page_number_int, frame_number));
        return (uint) frame_number;
    }

    TLBMISS += 1;
    PAGEFAULT += 1;
    mTLB->addTLBEntry(TLB::TLB_entry(page_number_int, frame_number));
    return mPhysicalMemory->insertFrameInNextFreeSpace(page_number, mHardDrive->read(page_number));

    //TP2_IFT2245_END_TO_DO
}


