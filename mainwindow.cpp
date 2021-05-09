#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <xmlparser.h>
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle(QString::fromLocal8Bit("send Cmd"));
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  parser = new XmlParser;
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::on_pushButton_open_clicked() {
  QString file_name = QFileDialog::getOpenFileName(this,
                                                   tr("choose execute file"),
                                                   "",
                                                   "*.exe",
                                                   0);
  if (!file_name.isNull()) {
    ui->lineEdit->setText(file_name);
    return;
  } else {
    return;
  }
}

void MainWindow::on_pushButton_add_clicked() {
  int line = ui->tableWidget->rowCount();
  ui->tableWidget->setRowCount(line + 1);
}

void MainWindow::on_pushButton_del_clicked() {
  ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void MainWindow::on_pushButton_exec_clicked() {
  int times = ui->tableWidget->rowCount();
  if (ui->lineEdit->text().isEmpty() || times <= 0) {
    qDebug() << "empty name or no item";
    return;
  }
  QProcess* process ;
  for (int i = 0; i < times ; i++) {
    process = new QProcess();
    QString program =  ui->lineEdit->text();
    QStringList arguments;
    arguments << ui->tableWidget->item(i, 0)->text() << ui->tableWidget->item(i, 1)->text()
              << ui->tableWidget->item(i, 02)->text();
    process->start(program, arguments);
  }
}

void MainWindow::on_pushButton_save_clicked() {
  int times = ui->tableWidget->rowCount();
  if (ui->lineEdit->text().isEmpty() || times <= 0) {
    qDebug() << "empty name or no item";
    return;
  }
  QList<Config> cfg_list;
  for (int i = 0; i < times ; i++) {
    Config cfg(i,
               ui->tableWidget->item(i, 0)->text(),
               ui->tableWidget->item(i, 1)->text(),
               ui->tableWidget->item(i, 2)->text());
    cfg_list.append(cfg);

  }
  QString file_name;
  file_name = QFileDialog::getSaveFileName(this, tr("Open File"), tr(""), tr("xml File (*.xml)"));
  if (file_name == "") {               //如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
    qDebug() << "empty name";
    return;
  }
  parser->Writer(cfg_list, file_name, ui->lineEdit->text());
}

void MainWindow::on_pushButton_Load_clicked() {
  QString file_name;
  QList<Config> cfg_list;
  QString exec_path;
  file_name = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), tr("xml File (*.xml)"));
  parser->Reader(file_name, cfg_list, exec_path);
  ui->lineEdit->setText(exec_path);
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(cfg_list.size());
  for (int i = 0; i < cfg_list.size(); i++) {
    int column = 0;
    ui->tableWidget->setItem(i, column++, new QTableWidgetItem(cfg_list.at(i).username_));
    ui->tableWidget->setItem(i, column++, new QTableWidgetItem(cfg_list.at(i).password_));
    ui->tableWidget->setItem(i, column++, new QTableWidgetItem(cfg_list.at(i).path_));
  }
}
