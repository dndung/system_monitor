#ifndef _HDD_MONITOR_H
#define _HDD_MONITOR_H

#include <QObject>
#include <QTimer>
#include <QStorageInfo>

enum eHddStatus {
  HDD_STATUS_OFF = 0,
  HDD_STATUS_NORMAL = 1,
  HDD_STATUS_FULL = 2
};
class HddMonitor : public QObject
{
  Q_OBJECT
  public:
    HddMonitor(double threshold = 30.0);
    ~HddMonitor();

  private:
    double mThreshold;
    QTimer mMonitoringTimer;
    enum eHddStatus mCurrentHddStatus;

  public:
    Q_SIGNALS:
      void newHddStatusEvent(eHddStatus hddStatus);

  private Q_SLOTS:
    void checkHddStatus();
    bool isHddValid(QStorageInfo &storageInfo);
  public:
    eHddStatus getHddStatus();

};


#endif // _HDD_MONITOR_H
