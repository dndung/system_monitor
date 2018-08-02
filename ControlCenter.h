
#ifndef _CONTROL_CENTER__
#define _CONTROL_CENTER__

#include "LedControl.h"
#include "NetworkMonitor.h"
#include "HddMonitor.h"
#include "SystemStatus.h"
#include "SystemStatusAdaptor.h"

#include <QObject>

class ControlCenter : public QObject 
{
  Q_OBJECT


  public:
    ControlCenter();
    ~ControlCenter();

    void init();
  private:
    LedControl speaker;
    LedControl networkLed;
    LedControl hddLed;
    LedControl sysLed;
    LedControl opLed;


    NetworkMonitor networkMonitor;
    HddMonitor hddMonitor;

    SystemStatus *sysStatus;
    SystemStatusAdaptor *sysStatusAdaptor;

  private Q_SLOTS:
      void handleNetworkChange(eNetworkStatus netStatus);
      void handleHddChange(eHddStatus hddStatus);


};

#endif // _CONTROL_CENTER__
