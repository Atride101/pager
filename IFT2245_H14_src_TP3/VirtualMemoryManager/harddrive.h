#ifndef HARDDRIVE_H
#define HARDDRIVE_H

#include <object.h>
#include <QFile>

class HardDrive:public TObject
{
public:
    /**
     * @brief HardDrive : creates the hard drive interface
     * from a given file str. The source file cannot be modified.
     * Instead, this creates a work copy file in order to be able
     * to restart the application as many times as needed to debug
     * the application.
     * @param str
     * @param nb_pages
     * @param page_size
     */
    HardDrive(QString str, uint nb_pages, uint page_size);
    ~HardDrive();

    uint nbPages() const;

    void ResetFromBackup();

    /**
     * @brief read
     * reads the page page_number from hard drive and returns it
     * @param page_number
     * @return
     */
    QByteArray * read(uint page_number);

    /**
     * @brief write
     * write a page to hard drive at position page_number
     * @param page_number
     * @param bytes
     */
    void write(uint page_number, const QByteArray *bytes);

private:
    uint mNbPages;
    uint mPageSize;
    QFile * mBackupFile;
    QFile * mHDFile;
};

#endif // HARDDRIVE_H
