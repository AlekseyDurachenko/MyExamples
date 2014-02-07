#include "mythreadobject.h"
#include <QThread>
#include <QDebug>

MyThreadObject::MyThreadObject(QObject *parent) :
    QObject(parent)
{
}

void MyThreadObject::whoami()
{
    qDebug() << "Thread: " << QThread::currentThread();
}
