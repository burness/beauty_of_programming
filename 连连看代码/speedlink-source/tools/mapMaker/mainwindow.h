#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void calc();
    void on_generateMap_clicked();
    void on_clear_clicked();
    void on_fill_clicked();

    void on_yMax_valueChanged(int arg1);

    void on_xMax_valueChanged(int arg1);

    void on_kindNum_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
