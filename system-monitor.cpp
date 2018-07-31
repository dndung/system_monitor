#include <systemd/sd-daemon.h>

#include <QtCore>
#include <QDebug>
#include <QTimer>

#include "ControlCenter.h"

void sendNotify()
{
  //qDebug("Send watchdog notify");
  sd_notify(0, "WATCHDOG=1");
}


int main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  qDebug() << "Started";

  QTimer watchdogTimer;
  QObject::connect(&watchdogTimer, &QTimer::timeout, sendNotify);
  watchdogTimer.start(20000);

  ControlCenter controlCenter;
  controlCenter.init();

  return a.exec();
}
