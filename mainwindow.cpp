#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
}

void MainWindow::putData()
{
  int max = ui->Max_slider->value();
  int min = ui->Min_slider->value();

  QDateTime datetime;
  QString str;
  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          QString::number(qrand()%(max-min)+min)+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
  ui->textBrowser->append(str);
}
MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

void MainWindow::on_ButtonConnect_clicked()
{
    socket->connectToHost(ui->servidor->text(),1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Conectado";
    }
    else{
      qDebug() << "Disconectado";
    }
}

void MainWindow::on_ButtonDisconnect_clicked()
{
    socket->close();
}

void MainWindow::on_ButtonStart_clicked()
{
    //Inicia a producao de dados.

    //Armazena o tempo de inicio.
    temporizador = startTimer((ui->Timing_box->value())*1000);
}

void MainWindow::on_ButtonStop_clicked()
{
    //Para o a contagem do temporizador.
    killTimer(temporizador);
    //Funcao predefinida. ver QTimerEvent.
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    putData();
}


