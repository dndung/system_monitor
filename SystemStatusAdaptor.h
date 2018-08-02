/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp SystemStatus.xml -a SystemStatusAdaptor -c SystemStatusAdaptor
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef SYSTEMSTATUSADAPTOR_H
#define SYSTEMSTATUSADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface vp9.system_status
 */
class SystemStatusAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "vp9.system_status")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"vp9.system_status\">\n"
"    <signal name=\"networkChanged\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"networkStatus\"/>\n"
"    </signal>\n"
"    <signal name=\"hddChanged\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"hddStatus\"/>\n"
"    </signal>\n"
"    <method name=\"getNetworkStatus\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"    <method name=\"getHddStatus\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    SystemStatusAdaptor(QObject *parent);
    virtual ~SystemStatusAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    int getHddStatus();
    int getNetworkStatus();
Q_SIGNALS: // SIGNALS
    void hddChanged(int hddStatus);
    void networkChanged(int networkStatus);
};

#endif
