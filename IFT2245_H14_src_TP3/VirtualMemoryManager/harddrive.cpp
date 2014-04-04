#include "harddrive.h"


HardDrive::HardDrive(QString str, uint nb_pages, uint page_size):
    TObject(str),mNbPages(nb_pages),mPageSize(page_size)
{
    mBackupFile = new QFile(str);
    if(!mBackupFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cerr<<"Could not open "<<mBackupFile->fileName().toStdString()<<endl;
        assert(false);
        return;
    }
    QFile::remove(str.append("-work_copy"));
    mBackupFile->copy(str);

    mHDFile = new QFile(str);
    if(!mHDFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        cerr<<"Could not open "<<mHDFile->fileName().toStdString()<<endl;
        assert(false);
        return;
    }
}

HardDrive::~HardDrive()
{
    mHDFile->close();
    delete mHDFile;

    mBackupFile->close();
    delete mBackupFile;
}

uint HardDrive::nbPages() const
{
    return mNbPages;
}

void HardDrive::ResetFromBackup()
{
    mHDFile->close();
    delete mHDFile;
    QFile::remove(name().append("-work_copy"));
    mBackupFile->copy(name());
    mHDFile = new QFile(name().append("-work_copy"));
}

QByteArray * HardDrive::read(uint page_number)
{
    assert(page_number<mNbPages);
    QByteArray page;
    if (mHDFile->seek(page_number*mPageSize))
    {
        page = mHDFile->read(mPageSize);
    }else{
        assert(false);
        cerr<<"Seek position too large"<<endl;
    }
    assert(page.size()==(int)mPageSize);
    return new QByteArray(page);
}

void HardDrive::write(uint page_number, const QByteArray *bytes)
{
    assert(page_number<mNbPages);
    assert(bytes->size() == (int)mPageSize);
    if (mHDFile->seek(page_number*mPageSize))
    {
        mHDFile->write(*bytes);
    }else{
        assert(false);
        cerr<<"Seek position too large"<<endl;
    }
}
