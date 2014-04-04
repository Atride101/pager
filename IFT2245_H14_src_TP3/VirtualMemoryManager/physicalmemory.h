#ifndef PHYSICALMEMORY_H
#define PHYSICALMEMORY_H

#include <object.h>
#include <frame.h>

class PhysicalMemory:public TObject
{
public:
    PhysicalMemory(QString str, uint nb_frames);
    ~PhysicalMemory();

    //TP2_IFT2245_TO_DO
    /**
     * @brief read
     * @param frame_number
     * @param offset
     * @param data
     */
    void read(uint frame_number, uint offset, char *data);

    //TP2_IFT2245_TO_DO
    /**
     * @brief write
     * @param frame_number
     * @param offset
     * @param data
     */
    void write(uint frame_number, uint offset, char *data);

    /**
     * @brief nbFrames
     * @return
     */
    uint nbFrames()const;

    //TP2_IFT2245_TO_DO
    /**
     * @brief insertFrameInNextFreeSpace
     * inserts the bytes at first empty location
     * @param frame_bytes
     * @return nextFreeSpace
     */
    uint insertFrameInNextFreeSpace(uint page_number, QByteArray * frame_bytes);

    //TP2_IFT2245_TO_DO
    /**
     * @brief insertFrame
     * insert the bytes as a replacement of the previous
     * bytes for frame frame_number. Warning : this function
     * deletes previous QByteArray (frame data). the user is
     * responsible for saving this array to somewhere else.
     * @param frame_bytes
     * @return
     */
    void insertFrame(uint frame_number, uint page_number, QByteArray * frame_bytes);

    /**
     * @brief hasEmptyFrame
     * @return
     */
    bool hasEmptyFrame()const;

    /**
     * @brief frame
     * @param frame_number
     * @return the frame data pointed at frame_number index
     */
    QByteArray *frame(uint frame_number);

    /**
     * @brief pageNumber
     * @param frame_nuumber
     * @return
     */
    uint pageNumber(uint frame_nuumber);

    /**
     * @brief setModified
     * @param frame_number
     */
    void setModified(uint frame_number);

    /**
     * @brief setUnModified
     * @param frame_number
     */
    void setUnModified(uint frame_number);

    /**
     * @brief isFrameModified
     * @return
     */
    bool isFrameModified(uint frame_number);

private :
    uint mNbFrames;
    uint mNextEmptyFrame;

    Frame *mFrames;
};

#endif // PHYSICALMEMORY_H
