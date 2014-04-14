#include "tlb.h"

TLB::TLB(QString str):TObject(str)
{
    _previousEntry = 0;
}

TLB::~TLB()
{
}

void TLB::addTLBEntry(TLB::TLB_entry new_tlb_entry)
{
    //TP2_IFT2245_TO_DO

    //TP2_IFT2245_END_TO_DO
}

void TLB::removeEntryFromTLB(int page_number)
{
    //TP2_IFT2245_TO_DO

    //TP2_IFT2245_END_TO_DO
}

bool TLB::findPage(int page_number, int& frame_index)
{
    //TP2_IFT2245_TO_DO

    for (int entry = 0; entry < 16; entry++) {
        if (_TLBArray[entry].pageNumber == page_number) {
            frame_index = _TLBArray[entry].frameNumber;
            return true;
        }
    }

    return false;

    //TP2_IFT2245_END_TO_DO
}



