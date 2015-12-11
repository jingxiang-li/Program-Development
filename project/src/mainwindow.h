#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_makeButton_clicked();

    void on_cleanButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
