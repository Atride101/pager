#include "frame.h"

Frame::Frame():TObject("default_frame")
{
    mFrameData = NULL;
    mPageNumber = -1;
    mIsModified = false;
}

Frame::~Frame()
{
    delete mFrameData;
}

void Frame::read(uint offset, char *data)
{
    assert(offset<(uint)mFrameData->size());
    *data = mFrameData->at(offset);
}

void Frame::write(uint offset, char *data)
{
    assert(offset<(uint)mFrameData->size());
    (*mFrameData)[offset]=*data;
}

void Frame::setFrameData(QByteArray *frame_data)
{
    delete mFrameData;
    mFrameData = frame_data;
    assert(mFrameData != NULL);
}

QByteArray *Frame::frameData()
{
    return mFrameData;
}

void Frame::setPageNumber(uint page_number)
{
    mPageNumber = page_number;
}

uint Frame::pageNumber()
{
    assert(mPageNumber>=0);
    return (uint)mPageNumber;
}

void Frame::setModified()
{
    mIsModified = true;
}

void Frame::setUnModified()
{
    mIsModified = false;
}

bool Frame::isModified()
{
    return mIsModified;
}
