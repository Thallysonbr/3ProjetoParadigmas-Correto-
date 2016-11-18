#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void putData();
private slots:
  void on_ButtonConnect_clicked();

  void on_ButtonDisconnect_clicked();

  void on_ButtonStart_clicked();

  void on_ButtonStop_clicked();

  void timerEvent(QTimerEvent *e);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int temporizador;
};

#endif // MAINWINDOW_H
