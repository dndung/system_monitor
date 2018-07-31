#include "LedControl.h"

#include <QDebug>

#include <stdio.h>


LedControl::LedControl(QString filename)
  : mBlinkingTimer(this)
{
  mIsBlinking = false;
  mCurrentState = LED_STATE_OFF;
  mDefaultState = LED_STATE_OFF;
  mControlFileName = filename;

  mControlFile.setFileName(mControlFileName);
  mControlFile.open(QIODevice::WriteOnly | QIODevice::Text);

  connect(&mBlinkingTimer, &QTimer::timeout, this, &LedControl::onBlinkingInterval);
  qDebug() << "New Led control: " << mControlFileName;
}

LedControl::~LedControl() {
  mControlFile.close();
  disconnect(&mBlinkingTimer, &QTimer::timeout, this, &LedControl::onBlinkingInterval);
}

void LedControl::turnOn() {
  stopBlinking(LED_STATE_ON);
}

void LedControl::turnOff() {
  stopBlinking(LED_STATE_OFF);
}

void LedControl::turnLed(eLedState ledState) {
  QTextStream writeStream;
  writeStream.setDevice(&mControlFile);

  mCurrentState = ledState;
  if (ledState == LED_STATE_OFF) {
    //qDebug() << "Write 0 to " << mControlFileName;
    writeStream << "0";
  } else {
    //qDebug() << "Write 1 to " << mControlFileName;
    writeStream << "1";
  }

}
void LedControl::startBlinking(uint32_t durationMs, uint32_t timeout) {
  mIsBlinking = true;
  mDefaultState = mCurrentState;
  mBlinkingTimer.start(durationMs/2);
  qDebug() << "Start blinking: " << durationMs << timeout;
  if (timeout > 0) {
    QTimer::singleShot(timeout, this, &LedControl::stopBlinkingTimeout);
  }
}

void LedControl::stopBlinkingTimeout() {
  return stopBlinking(mDefaultState);
}

void LedControl::stopBlinking(eLedState nextState) {
  mIsBlinking = false;
  mBlinkingTimer.stop();
  turnLed(nextState);
}

void LedControl::onBlinkingInterval() {
  if (mIsBlinking) {
    if (mCurrentState == LED_STATE_ON) {
      return turnLed(LED_STATE_OFF);
    } else {
      return turnLed(LED_STATE_ON);
    }
  }
}

