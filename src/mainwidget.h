#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QList>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onEventLoopDestroy(const QString& id);

    void on_btn_process_clicked();

    void on_btn_continue_clicked();

private:
    void addLog(const QString& text);

private:
    Ui::MainWidget *ui;

    QStringList m_listIDs;
};

#endif // MAINWIDGET_H
