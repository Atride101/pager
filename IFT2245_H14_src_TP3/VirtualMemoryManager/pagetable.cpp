#include "pagetable.h"

PageTable::PageTable(QString str,uint nb_pages):TObject(str),mNbPages(nb_pages)
{
    mPages = new Page[nb_pages];
}

PageTable::~PageTable()
{
    delete []mPages;
}

uint PageTable::nbPages()const
{
    return mNbPages;
}

void PageTable::insertPage(const Page &page)
{
    //TP2_IFT2245_TO_DO

    //TP2_IFT2245_END_TO_DO
}

bool PageTable::frameIndex(uint page_number, int& frame_index)
{
    //TP2_IFT2245_TO_DO
    return false;
    //TP2_IFT2245_END_TO_DO
}

void PageTable::setInvalid(uint page_number)
{
    mPages[page_number].setInvalid();
}
