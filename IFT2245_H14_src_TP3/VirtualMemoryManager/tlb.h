#ifndef TLB_H
#define TLB_H

#include <object.h>

/**
 * @brief The TLB class
 * Translation Look-aside Buffer
 */

class TLB:public TObject
{
public:
    typedef struct TLB_entry{
        int pageNumber;
        int frameNumber;
        TLB_entry(int pNum = -1, int fNum = -1)
            :pageNumber(pNum), frameNumber(fNum){}
                            } TLB_entry;

public:
    TLB(QString str);
    ~TLB();


    //TP2_IFT2245_TO_DO
    /**
     * @brief addTLBEntry : add an entry to the TLB.
     * @param new_tlb_entry
     */
    void addTLBEntry(TLB_entry new_tlb_entry);

    //TP2_IFT2245_TO_DO
    /**
     * @brief removeEntryFromTLB : remove an entry from the TLB.
     * when a page is unloaded from the physical memory
     * @param page_number
     */
    void removeEntryFromTLB(int page_number);

    //TP2_IFT2245_TO_DO
    /**
     * @brief findPage
     * return the frame index where the page is mapped-to
     * in the physical memory
     * @param page_number
     * @param frame_index
     * @return true if the page is currently referenced into
     * the TLB else false
     */
    bool findPage(int page_number, int& frame_index);

private:

    TLB_entry _TLBArray[16];
    int _previousEntry;
};

#endif // TLB_H
