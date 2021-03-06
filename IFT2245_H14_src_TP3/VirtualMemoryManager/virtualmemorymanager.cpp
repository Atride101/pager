#include "virtualmemorymanager.h"

float VirtualMemoryManager::TLBHIT = 0;
float VirtualMemoryManager::TLBMISS = 0;
float VirtualMemoryManager::PAGEFAULT = 0;
float VirtualMemoryManager::PAGEFOUND = 0;

// Cette valeur determine si la strategie de remplacement des frames dans la memoire physique
// et dans le TLB se fait par FIFO ou Least Frequently Used
bool fifo = false;

VirtualMemoryManager::VirtualMemoryManager(QString str, uint nb_pages, uint page_size, uint nb_frames, uint first_frame):
    TObject(str),mNbPages(nb_pages),mPageSize(page_size),mNbFrames(nb_frames),firstFrame(first_frame)/*,
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

    int page_number_int = (int) page_number;
    uint frame_number = fetchPage(page_number);
    mPhysicalMemory->write(frame_number, offset, data);
    mPhysicalMemory->setModified(frame_number);
    mPageTable->insertPage(page_number, Page("new page", page_number_int, mPageSize, frame_number, true));
    mHardDrive->write(page_number, mPhysicalMemory->frame(frame_number));

    //TP2_IFT2245_END_TO_DO
}

uint VirtualMemoryManager::fetchPage(uint page_number)
{
    //TP2_IFT2245_TO_DO

    int frame_number;
    int page_number_int = (int) page_number;

    // Si la page se trouve dans le TLB
    if (mTLB->findPage(page_number_int, frame_number)) {
        TLBHIT += 1;
        _usageFrequency[frame_number]++;
        return (uint) frame_number;
    }

    // Si la page se trouve dans le PageTable
    else if (mPageTable->frameIndex(page_number, frame_number)) {
        TLBMISS += 1;
        PAGEFOUND += 1;
        _usageFrequency[frame_number]++;

        // update de la TLB
        mTLB->addTLBEntry(TLB::TLB_entry(page_number_int, frame_number), fifo);
        return (uint) frame_number;
    }

    // Si la page n'est pas chargee et que la memoire physique n'est pas pleine
    else if (mPhysicalMemory->hasEmptyFrame()) {
        TLBMISS += 1;
        PAGEFAULT += 1;

        // insertion de la page dans une frame libre
        frame_number = mPhysicalMemory->insertFrameInNextFreeSpace(page_number, mHardDrive->read(page_number));
        _usageFrequency[frame_number] = 1;

        // update de la TLB et de la PageTable
        mTLB->addTLBEntry(TLB::TLB_entry(page_number_int, frame_number), fifo);
        mPageTable->insertPage(page_number, Page("new page", page_number_int, mPageSize, frame_number, true));

        return frame_number;
    }

    // Si la page n'est pas chargee et que la memoire physique est pleine
    TLBMISS += 1;
    PAGEFAULT += 1;

    // Si la strategie de remplacement est FIFO, on enleve une frame de la memoire pour faire de la place
    if (fifo == true) {
        frame_number = firstFrame % mNbFrames;
        firstFrame += 1;
    }

    // Si la strategie de remplacement est Least Frequently Used
    if (fifo == false) {
        int min = _usageFrequency[0];

        for (int i = 1 ; i < (int) mNbFrames; i++){
            if (min > _usageFrequency[i]) {
                frame_number = i;
                min = _usageFrequency[i];
            }
        }

        _usageFrequency[frame_number] = 1;
    }

    // invalidation dans le PageTable de la page associee au frame enleve
    mPageTable->setInvalid(mPhysicalMemory->pageNumber(frame_number));

    // insertion de la page par dessus la plus vieille frame
    mPhysicalMemory->insertFrame((uint) frame_number, page_number, mHardDrive->read(page_number));

    // update de la TLB et de la PageTable
    mTLB->addTLBEntry(TLB::TLB_entry(page_number_int, frame_number), fifo);
    mPageTable->insertPage(page_number, Page("new page", page_number_int, mPageSize, frame_number, true));

    return frame_number;

    //TP2_IFT2245_END_TO_DO
}


