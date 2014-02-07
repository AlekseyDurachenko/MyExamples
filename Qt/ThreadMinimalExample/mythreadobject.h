#ifndef MYTHREADOBJECT_H
#define MYTHREADOBJECT_H

#include <QObject>

class MyThreadObject : public QObject
{
    Q_OBJECT
public:
    explicit MyThreadObject(QObject *parent = 0);
    
signals:
    
public slots:
    void whoami();

};

#endif // MYTHREADOBJECT_H
