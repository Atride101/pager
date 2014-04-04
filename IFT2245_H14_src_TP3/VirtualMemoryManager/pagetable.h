#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <object.h>
#include <page.h>
#include <vector>

class PageTable:public TObject
{
public:
    PageTable(QString str,uint nb_pages);
    ~PageTable();

    uint nbPages() const;

    //TP2_IFT2245_TO_DO
    /**
     * @brief insertPage
     * add a page to the page table. this replace the previous
     * page which had the same page number
     * @param page_number
     * @param page
     */
    void insertPage(const Page &page);

    //TP2_IFT2245_TO_DO
    /**
     * @brief frameIndex
     * return the frame index where the page is mapped-to
     * in the physical memory
     * @param page_number
     * @param frame_index
     * @return true if the page is currently loaded into
     * physical memory else false
     */
    bool frameIndex(uint page_number, int &frame_index);

    /**
     * @brief setInvalid
     * @param page_number
     */
    void setInvalid(uint page_number);

private:
    uint mNbPages;
    Page* mPages;
};

#endif // PAGETABLE_H
