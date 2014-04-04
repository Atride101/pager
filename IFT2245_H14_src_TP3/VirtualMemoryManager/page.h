#ifndef PAGE_H
#define PAGE_H

#include <object.h>

class Page:public TObject
{
    friend class PageTable;

public:
    Page(QString str, int page_number, uint page_size, int frame_index, uint valid = true);
    ~Page();
    uint frameIndex();
    void setInvalid();
    bool isValid();
protected:
    Page();
private:
    uint mPageNumber;
    uint mPageSize;
    uint mFrameIndex;
    bool mValid;
};

#endif // PAGE_H
