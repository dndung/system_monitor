#ifndef _SYSTEM_STATUS_
#define _SYSTEM_STATUS_

#include <QObject>

class SystemStatus : public QObject
{
  Q_OBJECT

  Q_CLASSINFO("D-Bus Interface", "vp9.system_status")
  public:
    SystemStatus(int network, int hdd);
    ~SystemStatus();

  signals:
    void networkChanged(int networkStatus);
    void hddChanged(int hddStatus);

  public slots:
    int getNetworkStatus();
    int getHddStatus();
    void setNetworkStatus(int status);
    void setHddStatus(int status);

  private:
    int mNetworkStatus;
    int mHddStatus;

};

#endif // _SYSTEM_STATUS_
