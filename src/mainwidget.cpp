#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "eventloopmanager.h"
#include "customeventloop.h"
#include <QDateTime>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(EventLoopManager::instance(), SIGNAL(sigEventLoopFinished(QString)), this, SLOT(onEventLoopDestroy(QString)));
    connect(EventLoopManager::instance(), SIGNAL(sigEventLoopTimeout(QString)), this, SLOT(onEventLoopDestroy(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::onEventLoopDestroy(const QString &id)
{
    int iResult = m_listIDs.removeAll(id);
    QString text = "delete event loop: " + id + "[" + QString::number(iResult) + "]";
    addLog(text);
}

void MainWidget::on_btn_process_clicked()
{
    QString textStart("event loop start!");
    addLog(textStart);

    QString id("");
    if (EventLoopManager::instance()->addEventLoop(id) && id.length() > 0)
    {
        m_listIDs.push_back(id);
        EventLoopManager::instance()->startEventLoop(id);
    }

    QString textEnd("event loop end!");
    addLog(textEnd);
}

void MainWidget::on_btn_continue_clicked()
{
    if (m_listIDs.size() > 0)
        EventLoopManager::instance()->stopEventLoop(m_listIDs.last());
}

void MainWidget::addLog(const QString &text)
{
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString strLog = ui->edit_log->toPlainText();
    QString strNew = strDateTime + ": " + text;
    if (strLog.length() > 0)
        strLog = strNew + "\n" + strLog;
    else
        strLog = strNew;
    ui->edit_log->setText(strLog);
}
