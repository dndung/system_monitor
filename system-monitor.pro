#****************************************************
#*
#****************************************************

QT += core dbus
LIBS += -lsystemd

CONFIG += c++11
CONFIG += console
CONFIG += debug



SOURCES = system-monitor.cpp \
          ControlCenter.cpp \
          LedControl.cpp \
          HddMonitor.cpp \
          NetworkMonitor.cpp \
          NetworkStatusProxy.cpp
HEADERS =  \
          ControlCenter.h \
          LedControl.h \
          HddMonitor.h\
          NetworkMonitor.h\
          NetworkStatusProxy.h

TARGET = system-monitor


