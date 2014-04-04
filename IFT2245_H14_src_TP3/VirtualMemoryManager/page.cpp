#include "page.h"

Page::Page(QString str, int page_number, uint page_size, int frame_index, uint valid):
    TObject(str),mPageNumber(page_number),mPageSize(page_size),mFrameIndex(frame_index),mValid(valid)
{

}

Page::Page():TObject("default_empty_page")
{
     mPageNumber = -1;
     mPageSize = 0;
     mFrameIndex = -1;
     mValid = false;
}

Page::~Page()
{
//    cout<<"Deleted Page"<<endl;
}

uint Page::frameIndex()
{
    return mFrameIndex;
}

void Page::setInvalid()
{
    mValid=false;
}

bool Page::isValid()
{
    return mValid;
}
