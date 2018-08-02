#ifndef _PROPERTY_LIST_H
#define _PROPERTY_LIST_H

#include <QtDBus>
#include <QMap>
#include <QString>
#include <QVariant>


typedef QMap<QString, QVariant> PropertiesList;
Q_DECLARE_METATYPE(PropertiesList);
Q_DECLARE_METATYPE(QStringList);


#endif // _PROPERTY_LIST_H
