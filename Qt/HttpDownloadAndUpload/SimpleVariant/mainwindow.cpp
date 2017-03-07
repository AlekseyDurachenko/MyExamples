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

    // upload file with bloking
    QNetworkReply *srcReply = m_nam->get(QNetworkRequest(srcUrl));
    QNetworkReply *dstReply = m_nam->put(QNetworkRequest(dstUrl), srcReply);
    connect(srcReply, &QNetworkReply::readyRead, [=]() {
        qDebug() << "src readyRead = " << srcReply->bytesAvailable();
    });
    connect(srcReply, &QNetworkReply::finished, [=]() {
        qDebug() << "src finished = " << srcReply->errorString() << srcReply->bytesAvailable();
    });
    connect(dstReply, &QNetworkReply::uploadProgress, [=](qint64 bytes, qint64 bytesTotal) {
        qDebug() << "dst upload progress =" << bytes << bytesTotal;
    });
    connect(dstReply, &QNetworkReply::finished, [=]() {
        qDebug() << "dst finished = " << dstReply->errorString();
    });
}
