/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c NetworkStatusProxy -p NetworkStatusProxy NetworkStatusInterface.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NETWORKSTATUSPROXY_H
#define NETWORKSTATUSPROXY_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

typedef QMap<QString, QVariant> PropertiesList;
/*
 * Proxy class for interface org.freedesktop.DBus.Properties
 */
class NetworkStatusProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.DBus.Properties"; }

public:
    NetworkStatusProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NetworkStatusProxy();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusVariant> Get(const QString &interface, const QString &property)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(interface) << QVariant::fromValue(property);
        return asyncCallWithArgumentList(QStringLiteral("Get"), argumentList);
    }

    inline QDBusPendingReply<PropertiesList> GetAll(const QString &interface)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(interface);
        return asyncCallWithArgumentList(QStringLiteral("GetAll"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QString &interface, PropertiesList changed_properties, const QStringList &invalidated_properties);
};

namespace org {
  namespace freedesktop {
    namespace DBus {
      typedef ::NetworkStatusProxy Properties;
    }
  }
}
#endif
