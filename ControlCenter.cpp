#include "ControlCenter.h"

#include <QDebug>

#include <QDBusConnection>

#define SYSTEM_STATUS_SERVICE "vp9.system_status"
#define SYSTEM_STATUS_PATH "/vp9/system_status"

ControlCenter::ControlCenter() :
  speaker("/sys/devices/platform/speakerled/leds/led-speaker/brightness"),
  networkLed("/sys/devices/platform/networkled/leds/led-network/brightness"),
  hddLed("/sys/devices/platform/hddled/leds/led-hdd/brightness"),
  sysLed("/sys/devices/platform/sysled/leds/led-sys/brightness"),
  opLed("/sys/devices/platform/opled/leds/led-op/brightness")
{
  // connect signals

  sysStatus = new SystemStatus(0,0);
  sysStatusAdaptor = new SystemStatusAdaptor(sysStatus);

  connect(&networkMonitor, &NetworkMonitor::networkChanged,
          this , &ControlCenter::handleNetworkChange);
  connect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          this, &ControlCenter::handleHddChange);

  connect(&networkMonitor, &NetworkMonitor::networkChanged,
          sysStatus , &SystemStatus::setNetworkStatus);
  connect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          sysStatus , &SystemStatus::setHddStatus);

  qDebug() << "signals and slots connected";
}

ControlCenter::~ControlCenter()
{
  // disconnect signals
  disconnect(&networkMonitor, &NetworkMonitor::networkChanged,
          this , &ControlCenter::handleNetworkChange);
  disconnect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          this, &ControlCenter::handleHddChange);
  disconnect(&networkMonitor, &NetworkMonitor::networkChanged,
          sysStatus , &SystemStatus::setNetworkStatus);
  disconnect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          sysStatus , &SystemStatus::setHddStatus);

}
void ControlCenter::init()
{
  eNetworkStatus netStatus  = networkMonitor.getNetworkStatus();
  handleNetworkChange(netStatus);
  sysStatus->setNetworkStatus(netStatus);
  eHddStatus hddStatus = hddMonitor.getHddStatus();
  handleHddChange(hddStatus);
  sysStatus->setHddStatus(hddStatus);

  QDBusConnection connection = QDBusConnection::systemBus();
  if (!connection.interface()->isServiceRegistered(SYSTEM_STATUS_SERVICE)){
    if (!connection.registerService(SYSTEM_STATUS_SERVICE))
    {
      qDebug() << "Could not register system status service";
    }
    if (!connection.registerObject(SYSTEM_STATUS_PATH, sysStatus))
    {
      qDebug() << "Could not register system status object";
    }
  }
}

void ControlCenter::handleNetworkChange(eNetworkStatus netStatus)
{
  if (netStatus >= NETWORK_STATUS_CARRIER) {
    qDebug() << "network changed: ON ";
    //networkLed.turnOn();
    networkLed.stopBlinking(LedControl::LED_STATE_ON);
  } else {
    //networkLed.turnOff();
    qDebug() << "network changed: OFF ";
    networkLed.startBlinking(500);
  }
}

void ControlCenter::handleHddChange(eHddStatus hddStatus)
{
  qDebug() << "HandleHddChange()";
  if (hddStatus == HDD_STATUS_OFF) {
    qDebug() << "hdd changed: OFF ";
    hddLed.turnOff();
  } else if (hddStatus == HDD_STATUS_NORMAL) {
    qDebug() << "hdd changed: NOT FULL ";
    hddLed.turnOn();
  } else {
    qDebug() << "hdd changed: FULL ";
    hddLed.startBlinking(500);
  }
}


