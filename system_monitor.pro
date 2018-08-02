#****************************************************
#*
#****************************************************

QT += core dbus
LIBS += -lsystemd

CONFIG += c++11
CONFIG += console
CONFIG += debug



SOURCES = system_monitor.cpp \
          ControlCenter.cpp \
          LedControl.cpp \
          HddMonitor.cpp \
          NetworkMonitor.cpp \
          NetworkStatusProxy.cpp \
          SystemStatus.cpp \
          SystemStatusAdaptor.cpp
HEADERS =  \
          ControlCenter.h \
          LedControl.h \
          HddMonitor.h\
          NetworkMonitor.h\
          NetworkStatusProxy.h \
          SystemStatus.h \
          SystemStatusAdaptor.h 

TARGET = system_monitor

target.path = /usr/bin

INSTALLS += target


