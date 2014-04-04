#ifndef VIRTUALMEMORYMANAGER_H
#define VIRTUALMEMORYMANAGER_H

#include <object.h>
#include <harddrive.h>
#include <pagetable.h>
#include <physicalmemory.h>
#include <tlb.h>
//#include <random>

class VirtualMemoryManager:public TObject
{
public:
    static float TLBHIT;
    static float TLBMISS;
    static float PAGEFAULT;
    static float PAGEFOUND;

public:
    /**
     * @brief VirtualMemoryManager
     * @param str
     * @param nb_pages
     * @param page_size
     * @param nb_frames
     * NOTE : DO NOT CHANGE THESE VALUES 512,256,256 OR IT COULD CRASH THE PROGRAM
     */
    VirtualMemoryManager(QString str = "Virtual Memory Manager", uint nb_pages = 512, uint page_size = 256, uint nb_frames = 256);
    ~VirtualMemoryManager();

    //TP2_IFT2245_TO_DO
    /**
     * @brief read : fetch the frame_number corresponding to page_number
     * (see fetchPage below) and ask physical memory to read the value
     * in that frame at specified offset and put that value into to
     * pointed variable data.
     * @param page_number
     * @param offset
     * @param data
     */
    void read(uint page_number, uint offset, char *data);

    //TP2_IFT2245_TO_DO
    /**
     * @brief write : fetch the frame_number corresponding to page_number
     * (see fetchPage below) and ask physical memory to write the pointed-to
     * value (data) in that frame at specified offset.
     * @param page_number
     * @param offset
     * @param data
     */
    void write(uint page_number, uint offset, char *data);

    //TP2_IFT2245_TO_DO
    /**
     * @brief saveRAMToDisk : save the modified frames to disk
     */
    void saveRAMToDisk();

private:


    //TP2_IFT2245_TO_DO
    /**
     * @brief fetchPage fetch the page associated with page_number
     * from mPageTable. Look into the TLB for a loaded page.
     * If the page is not in the TLB, search into the pageTable.
     * If the page is not loaded into the physical memory, ask the physicalMemory
     * and wait for the page to be loaded from the hardDrive to the physicalMemory.
     * @param page_number
     * @return the frame_number
     */
    uint fetchPage(uint page_number);


    /**
     * @brief outputToLog output the value read from the physical memory
     * into a log file.
     * @param page_number
     * @return the frame_number
     */
    void outputToLog(char *data);

    uint mNbPages;
    uint mPageSize;
    uint mNbFrames;

    HardDrive * mHardDrive;
    PageTable * mPageTable;
    PhysicalMemory * mPhysicalMemory;
    TLB * mTLB;

    QFile * mLogFile;

//    std::mt19937 mRdNumberGenerator;
//    uniform_int_distribution<int> mRdNumberDistribution;
//    std::function<int()> dice;

};

#endif // VIRTUALMEMORYMANAGER_H
