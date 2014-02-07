#include <QCoreApplication>
#include <QThread>
#include "mythreadobject.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread *thread = new QThread;
    MyThreadObject *obj = new MyThreadObject;
    obj->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), obj, SLOT(whoami()));
    thread->start();
    qDebug() << "Main: " << QThread::currentThread();

    return a.exec();
}
