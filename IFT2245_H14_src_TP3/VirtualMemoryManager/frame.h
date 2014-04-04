#ifndef FRAME_H
#define FRAME_H

#include <object.h>
#include <QByteArray>

class Frame:public TObject
{
    friend class PhysicalMemory;

public:

protected:
    Frame();
    ~Frame();

    void read(uint offset, char *data);
    void write(uint offset, char *data);

    void setFrameData(QByteArray * frame_data);
    QByteArray * frameData();
    void setPageNumber(uint page_number);
    uint pageNumber();
    void setModified();
    void setUnModified();
    bool isModified();

private:
    QByteArray *mFrameData;
    int mPageNumber;
    bool mIsModified;
};

#endif // FRAME_H
