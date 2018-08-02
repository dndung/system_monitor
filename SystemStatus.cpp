#include "SystemStatus.h"
#include <QDebug>

SystemStatus::SystemStatus(int network, int hdd)
  :mNetworkStatus(network),
   mHddStatus(hdd)
{

}
SystemStatus::~SystemStatus()
{

}

int SystemStatus::getNetworkStatus()
{
  qDebug() << "NetworkStatus: " << mNetworkStatus;
  return mNetworkStatus;
}

int SystemStatus::getHddStatus()
{
  qDebug() << "NetworkStatus: " << mHddStatus;
  return mHddStatus;
}


void SystemStatus::setNetworkStatus(int status)
{
  if (mNetworkStatus != status) {
    mNetworkStatus = status;
    emit networkChanged(status);
  }
}

void SystemStatus::setHddStatus(int status)
{
  if (mHddStatus != status) {
    mHddStatus = status;
    emit hddChanged(status);
  }
}

