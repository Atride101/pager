#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <QString>
#include <assert.h>

using namespace std;

class TObject
{
public:
    TObject(QString str);
    virtual ~TObject();
    QString name() const;
private:
    QString mName;
};

#endif // OBJECT_H
