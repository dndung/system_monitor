#ifndef _LED_CONTROL_H
#define _LED_CONTROL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTimer>

class LedControl : public QObject {
  Q_OBJECT
public:
  enum eLedState {
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1
  };
private:
  QString mControlFileName;

  QFile mControlFile;
  QTextStream mControlWriteStream;

  bool mIsBlinking;
  eLedState mCurrentState;
  eLedState mDefaultState;

  QTimer mBlinkingTimer;


public:
  LedControl(QString filename);
  ~LedControl();

  void turnOn();
  void turnOff();

public Q_SLOTS:
  void startBlinking(uint32_t durationMs, uint32_t timeout = 0);
  void stopBlinking(eLedState nextState = LED_STATE_OFF);
  void stopBlinkingTimeout();
private Q_SLOTS:
  void onBlinkingInterval();

private:
  void turnLed(eLedState state);

};

#endif // _LED_CONTROL_H
