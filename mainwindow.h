#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class XmlParser;
class Config {
 public:
  Config(int id, QString username, QString password, QString path)
  {this->id_ = id; this->username_ = username; this->password_ = password; this->path_ = path;};
  int id_ = 0;
  QString username_ = "";
  QString password_ = "";
  QString path_ = "";
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_open_clicked();

  void on_pushButton_add_clicked();

  void on_pushButton_del_clicked();

  void on_pushButton_exec_clicked();

  void on_pushButton_save_clicked();

  void on_pushButton_Load_clicked();

 private:
  Ui::MainWindow* ui;
  XmlParser* parser;
};
#endif // MAINWINDOW_H
