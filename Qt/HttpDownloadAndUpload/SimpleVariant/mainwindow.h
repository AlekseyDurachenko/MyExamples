#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QNetworkAccessManager>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() override final;

private slots:
    void on_action_Quit_triggered();
    void on_start_pushButton_clicked();

    void srcReply_readyRead();
    void srcReply_finished();
    void dstReply_uploadProgress(qint64 bytes, qint64 totalBytes);
    void dstReply_finished();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_nam;
    QNetworkReply *m_srcReply;
    QNetworkReply *m_dstReply;
};


#endif // MAINWINDOW_H
