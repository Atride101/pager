#include "object.h"

TObject::TObject(QString str):mName(str)
{
//    cout<<"Creating object : "<<mName.toStdString().c_str()<<endl;
}

TObject::~TObject()
{
//    cout<<"Deleting object : "<<mName.toStdString().c_str()<<endl;
}

QString TObject::name() const
{
    return mName;
}
