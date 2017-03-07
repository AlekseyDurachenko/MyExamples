#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QUrl>
#include <QtNetwork>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_nam = new QNetworkAccessManager(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    qApp->quit();
}

void MainWindow::on_start_pushButton_clicked()
{
    const QUrl srcUrl = QUrl(ui->src_lineEdit->text());
    const QUrl dstUrl = QUrl(ui->dst_lineEdit->text());

    if (!srcUrl.isValid()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter source URL"));
        return;
    }

    if (!dstUrl.isValid()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter destination URL"));
        return;
    }

    // download && upload file
    m_srcReply = m_nam->get(QNetworkRequest(srcUrl));
    m_dstReply = 0;

    connect(m_srcReply, SIGNAL(readyRead()), SLOT(srcReply_readyRead()));
    connect(m_srcReply, SIGNAL(finished()), SLOT(srcReply_finished()));
}

void MainWindow::srcReply_readyRead()
{
    qDebug() << "srcReply_readyRead()" << m_srcReply->bytesAvailable();

    if (!m_dstReply) {
        QNetworkRequest dstRequest = QNetworkRequest(QUrl(ui->dst_lineEdit->text()));
        dstRequest.setAttribute(QNetworkRequest::DoNotBufferUploadDataAttribute, true);
        dstRequest.setHeader(QNetworkRequest::ContentLengthHeader, m_srcReply->header(QNetworkRequest::ContentLengthHeader));
        m_dstReply = m_nam->put(dstRequest, m_srcReply);

        connect(m_dstReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(dstReply_uploadProgress(qint64,qint64)));
        connect(m_dstReply, SIGNAL(finished()), this, SLOT(dstReply_finished()));
    }
}

void MainWindow::srcReply_finished()
{
    qDebug() << "srcReply_finished()" << m_srcReply->errorString() << m_srcReply->bytesAvailable();
    // do not remove before dstReply_finished() (!!!!!!!!!)
    //m_srcReply->deleteLater();
}

void MainWindow::dstReply_uploadProgress(qint64 bytes, qint64 totalBytes)
{
    qDebug() << "dstReply_uploadProgress()" << bytes << totalBytes;
}

void MainWindow::dstReply_finished()
{
    qDebug() << "dstReply_finished()" << m_dstReply->errorString();
    m_dstReply->deleteLater();
    m_srcReply->deleteLater();
    QMessageBox::information(this, tr("information"), tr("Done!"));
}
