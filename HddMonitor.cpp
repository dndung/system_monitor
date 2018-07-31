
#include <QDebug>

#include "HddMonitor.h"

HddMonitor::HddMonitor(double threshold):
  mThreshold(threshold)
{
  qDebug() << "Start Hdd Monitor";

  mCurrentHddStatus = getHddStatus();
  connect(&mMonitoringTimer, &QTimer::timeout, this, &HddMonitor::checkHddStatus);
  mMonitoringTimer.start(5000);
}

HddMonitor::~HddMonitor() {
  mMonitoringTimer.stop();
  disconnect(&mMonitoringTimer, &QTimer::timeout, this, &HddMonitor::checkHddStatus);
}

void HddMonitor::checkHddStatus()
{
  eHddStatus hddStatus = getHddStatus();

  if (mCurrentHddStatus == HDD_STATUS_OFF) {
    if (hddStatus == HDD_STATUS_FULL) {
      qDebug() << "Emit FULL";
      emit newHddStatusEvent(HDD_STATUS_FULL);
    } else if  (hddStatus == HDD_STATUS_NOT_FULL) {
      qDebug() << "Emit ON";
      emit newHddStatusEvent(HDD_STATUS_NOT_FULL);
    } else {
      //qDebug() << "Still OFF";
    }
  } else if (mCurrentHddStatus == HDD_STATUS_FULL) {
    if (hddStatus == HDD_STATUS_NOT_FULL) {
      qDebug() << "Emit NOT FULL";
      emit newHddStatusEvent(HDD_STATUS_NOT_FULL);
    } else if  (hddStatus == HDD_STATUS_OFF) {
      qDebug() << "Emit OFF";
      emit newHddStatusEvent(HDD_STATUS_OFF);
    } else {
      //qDebug() << "Still FULL";
    }
  } else { // current NOT FULL
    if (hddStatus == HDD_STATUS_FULL) {
      qDebug() << "Emit FULL";
      emit newHddStatusEvent(HDD_STATUS_FULL);
    } else if  (hddStatus == HDD_STATUS_OFF) {
      qDebug() << "Emit OFF";
      emit newHddStatusEvent(HDD_STATUS_OFF);
    } else {
      //qDebug() << "Still NOT FULL";
    }
  }
  mCurrentHddStatus = hddStatus;
}

bool HddMonitor::isHddValid(QStorageInfo &storageInfo) {
  if (!storageInfo.isValid())
    return false;

  if (!storageInfo.isReady())
    return false;

  if (storageInfo.isRoot())
    return false;

  return true;
}

eHddStatus HddMonitor::getHddStatus()
{
  const QString mountPoint = "/mnt/hdd";
  QStorageInfo storageInfo(mountPoint);

  if (isHddValid(storageInfo)) {
    //qDebug() << "Storage is available: " << storageInfo.device();

    qint64 bytesTotal = storageInfo.bytesTotal();
    qint64 bytesFree = storageInfo.bytesFree();

    double rate = ((double)bytesFree/(double)bytesTotal)*100;
    //qDebug() << "bytesFree: " << bytesFree;
    //qDebug() << "bytesTotal: " << bytesTotal;
    //qDebug() << "Rate: " << rate;
      
    if (rate >= mThreshold) {
      return HDD_STATUS_NOT_FULL;
    } else {
      return HDD_STATUS_FULL;
    }
  } else {
    return HDD_STATUS_OFF;
  }
}

