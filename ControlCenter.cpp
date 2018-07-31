#include "ControlCenter.h"

#include <QDebug>

ControlCenter::ControlCenter() :
  speaker("/sys/devices/platform/speakerled/leds/led-speaker/brightness"),
  networkLed("/sys/devices/platform/networkled/leds/led-network/brightness"),
  hddLed("/sys/devices/platform/hddled/leds/led-hdd/brightness"),
  sysLed("/sys/devices/platform/sysled/leds/led-sys/brightness"),
  opLed("/sys/devices/platform/opled/leds/led-op/brightness")
{
  // connect signals

  connect(&networkMonitor, &NetworkMonitor::networkChanged,
          this , &ControlCenter::handleNetworkChange);
  connect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          this, &ControlCenter::handleHddChange);

  qDebug() << "network led slot connected";
}

ControlCenter::~ControlCenter()
{
  // disconnect signals
  disconnect(&networkMonitor, &NetworkMonitor::networkChanged,
          this , &ControlCenter::handleNetworkChange);
  disconnect(&hddMonitor, &HddMonitor::newHddStatusEvent,
          this, &ControlCenter::handleHddChange);
  qDebug() << "network led slot disconnected";

}
void ControlCenter::init()
{
  eNetworkStatus netStatus  = networkMonitor.getNetworkStatus();
  handleNetworkChange(netStatus);
  eHddStatus hddStatus = hddMonitor.getHddStatus();
  handleHddChange(hddStatus);
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
  } else if (hddStatus == HDD_STATUS_NOT_FULL) {
    qDebug() << "hdd changed: NOT FULL ";
    hddLed.turnOn();
  } else {
    qDebug() << "hdd changed: FULL ";
    hddLed.startBlinking(500);
  }
}


