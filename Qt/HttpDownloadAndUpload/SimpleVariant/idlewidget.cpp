#include "idlewidget.h"
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QPainter>


IdleWidget::IdleWidget(QWidget *parent)
    : QWidget(parent)
{
    m_startTime = QTime::currentTime();

    QTimer *timer = new QTimer(this);
    timer->setInterval(10);
    timer->setSingleShot(false);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void IdleWidget::paintEvent(QPaintEvent *event)
{
    const int msecs = m_startTime.msecsTo(QTime::currentTime());
    const double angle = (msecs % (360 * 5)) / 5.0;

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setBrush(Qt::green);
    painter.setPen(Qt::black);
    painter.save();
    painter.translate(rect().center().x(), rect().center().y());
    painter.rotate(angle);
    painter.drawRect(QRect(-rect().center().x(), -rect().center().y(), rect().width(), rect().height()));
    painter.restore();
}

