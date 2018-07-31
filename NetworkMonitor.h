
#ifndef _NETWORK_MONITOR_H
#define _NETWORK_MONITOR_H

#include <QObject>
#include <QtDBus>

#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>

#include "NetworkStatusProxy.h"

enum eNetworkStatus {
  NETWORK_STATUS_OFF = 0,
  NETWORK_STATUS_NO_CARRIER = 1,
  NETWORK_STATUS_DORMANT = 2,
  NETWORK_STATUS_CARRIER = 3,
  NETWORK_STATUS_DEGRADED = 4,
  NETWORK_STATUS_ROUTABLE = 5
};

class NetworkMonitor : public QObject {
  Q_OBJECT

  public:

  public:
    NetworkMonitor();
    ~NetworkMonitor();

    eNetworkStatus getNetworkStatus();
    bool isServiceAvailable();
    bool isSystemBusConnected();
  public:
    Q_SIGNALS:
    void networkChanged(eNetworkStatus netStatus);
  public Q_SLOTS:
    void onPropertiesChanged(QString interface,
                        QMap<QString, QVariant> changedProperties,
                        QStringList invalidated_properties);

  private:
    NetworkStatusProxy *netStatusProxy;

};


#endif // _NETWORK_MONITOR_H

