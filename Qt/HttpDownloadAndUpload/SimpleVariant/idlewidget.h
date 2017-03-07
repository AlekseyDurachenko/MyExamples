#ifndef IDLEWIDGET_H
#define IDLEWIDGET_H


#include <QTime>
#include <QWidget>


class IdleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IdleWidget(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event) override final;

private:
    QTime m_startTime;
};


#endif // IDLEWIDGET_H
