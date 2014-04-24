#include "tlb.h"

TLB::TLB(QString str):TObject(str)
{
    _previousEntry = 0;
}

TLB::~TLB()
{
}

void TLB::addTLBEntry(TLB::TLB_entry new_tlb_entry, bool fifo)
{
    //TP2_IFT2245_TO_DO

    if (_previousEntry < 16) {
        _TLBArray[_previousEntry] = new_tlb_entry;
    }
    else if (fifo == true) {
        int entry = _previousEntry % 16;
        _TLBArray[entry] = new_tlb_entry;
    }
    else if (fifo == false) {
        int entry = 0;
        int min = _usageFrequency[0];

        for (int i = 1; i < 16; i++) {
            if (min > _usageFrequency[i]){
                entry = i;
                min = _usageFrequency[i];
            }
        }

        _TLBArray[entry] = new_tlb_entry;
    }

    _previousEntry += 1;

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
            _usageFrequency[entry]++;
            return true;
        }
    }

    return false;

    //TP2_IFT2245_END_TO_DO
}



