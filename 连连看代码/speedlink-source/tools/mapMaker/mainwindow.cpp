#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mapLabel,SIGNAL(mapChanged()),this,SLOT(calc()));
    ui->mapLabel->resizePix(ui->xMax->value(),ui->yMax->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QMessageBox>
void MainWindow::on_generateMap_clicked()
{
    ui->mapLabel->generateMap(ui->kindNum->value());
    QString fileName=ui->fileNameInput->text();
    if(!fileName.isEmpty()){
        if(ui->mapLabel->checkMap()){
            ui->mapLabel->saveMap(fileName);
            QMessageBox::information(this,tr("Ok"),tr("Map Generated successfully"));
        }
    }
}

void MainWindow::calc()
{
    ui->patternNum->setText(tr("%1").arg(ui->mapLabel->patternNum()));
    ui->pairNum->setText(tr("%1").arg(ui->mapLabel->pairNum()));
}

void MainWindow::on_clear_clicked()
{
    ui->mapLabel->setBlank();
}

void MainWindow::on_fill_clicked()
{
    ui->mapLabel->fillAll();
}

void MainWindow::on_yMax_valueChanged(int arg1)
{
    ui->mapLabel->resizePix(ui->xMax->value(),arg1);
}

void MainWindow::on_xMax_valueChanged(int arg1)
{
    ui->mapLabel->resizePix(arg1,ui->yMax->value());
}

void MainWindow::on_kindNum_valueChanged(int arg1)
{
    ui->numPerPair->setText(tr("%1").arg(ui->mapLabel->pairNum()/arg1));
}
