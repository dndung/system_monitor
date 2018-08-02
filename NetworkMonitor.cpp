#include <QDebug>
#include "NetworkMonitor.h"

NetworkMonitor::NetworkMonitor()
{
  qDebug() << "New Network monitor object";
  qDBusRegisterMetaType<PropertiesList>();
  qDBusRegisterMetaType<QStringList>();
  netStatusProxy = new NetworkStatusProxy(
                                "org.freedesktop.network1",
                                "/org/freedesktop/network1",
                                QDBusConnection::systemBus(), NULL);

  if (netStatusProxy->isValid()) {
    bool ret;
    
    /*
    ret = QDBusConnection::systemBus().connect(
                                        "org.freedesktop.network1",
                                        "/org/freedesktop/network1",
                                        "org.freedesktop.DBus.Properties",
                                        "PropertiesChanged",
                                        this, 
                                        SLOT(onPropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));
    */
    ret = connect(netStatusProxy, &NetworkStatusProxy::PropertiesChanged,
                  this, &NetworkMonitor::onPropertiesChanged);
    if (ret) {
      qDebug() << "CONNECTED";

    } else {
      qDebug() << "Connect failed";

    }
  }
  else {
    qDebug() << "NOT VALID";
  }

}

NetworkMonitor::~NetworkMonitor() {
  qDebug() << "Delete Network monitor object\n";
}

bool NetworkMonitor::isSystemBusConnected() {
  if (!QDBusConnection::systemBus().isConnected()) {
    qCritical() << "Cannot connect to DBus system\n";
    return false;
  }
  else {
    qDebug() << "System bus connected\n";
    return true;
  }
}

eNetworkStatus getNetworkStatusFromStr(QString netStatusStr) {
  eNetworkStatus netStatus = NETWORK_STATUS_OFF;
  if (netStatusStr == "routable") {
    netStatus = NETWORK_STATUS_ROUTABLE;
  } else if (netStatusStr == "degraded") {
    netStatus = NETWORK_STATUS_DEGRADED;
  } else if (netStatusStr == "carrier") {
    netStatus = NETWORK_STATUS_CARRIER;
  } else if (netStatusStr == "dormant") {
    netStatus = NETWORK_STATUS_DORMANT;
  } else if (netStatusStr == "no-carrier") {
    netStatus = NETWORK_STATUS_NO_CARRIER;
  } else {
    netStatus = NETWORK_STATUS_OFF;
  }

  return netStatus;
}

/*
void NetworkMonitor::onPropertiesChanged(QString interface,
                        QMap<QString, QVariant> changedProperties,
                        QStringList invalidated_properties)
*/
void NetworkMonitor::onPropertiesChanged(QString interface,
                        PropertiesList changedProperties,
                        QStringList invalidated_properties)
{
  Q_UNUSED(interface);
  Q_UNUSED(invalidated_properties);
  auto propertiesIter = changedProperties.cbegin();
  while (propertiesIter != changedProperties.cend()) {
    
    if (propertiesIter.key() == "OperationalState") {
      QString value = propertiesIter.value().toString();
      eNetworkStatus netStatus = getNetworkStatusFromStr(value);
      emit networkChanged(netStatus);
    }
    propertiesIter++;
  }
}

eNetworkStatus NetworkMonitor::getNetworkStatus() {
  eNetworkStatus netStatus = NETWORK_STATUS_OFF;

  if (netStatusProxy->isValid()) {
    QDBusPendingReply<QDBusVariant> reply = netStatusProxy->Get("org.freedesktop.network1.Manager", "OperationalState");
    reply.waitForFinished();
    if (reply.isValid()) {
      QString value = reply.value().variant().toString();
      netStatus = getNetworkStatusFromStr(value);

    } else {
      qWarning() << "Reply is not valid\n";
    }

  } else {
    qWarning() << "Interface is not valid\n";
  }

  return netStatus;
}

