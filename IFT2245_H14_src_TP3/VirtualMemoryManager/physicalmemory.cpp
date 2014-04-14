#include "physicalmemory.h"

PhysicalMemory::PhysicalMemory(QString str, uint nb_frames):TObject(str),mNbFrames(nb_frames),mNextEmptyFrame(0)
{
    mFrames = new Frame[nb_frames];
}

PhysicalMemory::~PhysicalMemory()
{
    delete []mFrames;
}

uint PhysicalMemory::nbFrames()const
{
    return mNbFrames;
}

void PhysicalMemory::read(uint frame_number, uint offset, char * data)
{
    //TP2_IFT2245_TO_DO

    mFrames[frame_number].read(offset, data);

    //TP2_IFT2245_END_TO_DO
}

void PhysicalMemory::write(uint frame_number, uint offset, char * data)
{
    //TP2_IFT2245_TO_DO

    mFrames[frame_number].write(offset, data);
    mFrames[frame_number].setModified();

    //TP2_IFT2245_END_TO_DO
}

uint PhysicalMemory::insertFrameInNextFreeSpace(uint page_number, QByteArray *frame_bytes)
{
    //TP2_IFT2245_TO_DO
    //If there is an empty frame

    if (hasEmptyFrame()) {
        mFrames[mNextEmptyFrame].setFrameData(frame_bytes);
        mFrames[mNextEmptyFrame].setPageNumber(page_number);
        mNextEmptyFrame += 1;
        return mNextEmptyFrame - 1;
    }

    //TP2_IFT2245_END_TO_DO
}

void PhysicalMemory::insertFrame(uint frame_number, uint page_number, QByteArray *frame_bytes)
{
    //TP2_IFT2245_TO_DO
    //The frame is not empty but the user should already
    //have saved the data.

    //TP2_IFT2245_END_TO_DO
}

bool PhysicalMemory::hasEmptyFrame() const
{
    return (mNextEmptyFrame<mNbFrames);
}

QByteArray * PhysicalMemory::frame(uint frame_number)
{
    return mFrames[frame_number].frameData();
}

uint PhysicalMemory::pageNumber(uint frame_nuumber)
{
    return mFrames[frame_nuumber].pageNumber();
}

void PhysicalMemory::setModified(uint frame_number)
{
    mFrames[frame_number].setModified();
}

void PhysicalMemory::setUnModified(uint frame_number)
{
    mFrames[frame_number].setUnModified();
}

bool PhysicalMemory::isFrameModified(uint frame_number)
{
    return mFrames[frame_number].isModified();
}
