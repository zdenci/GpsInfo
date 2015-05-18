#include "LocationObserver.h"
#include "GeoCoordinates.h"

#include <QVariant>
#include <QDateTime>
#include <QQmlProperty>

CLocationObserver::CLocationObserver(const QObject* pQmlObj)
{
    m_pQmlObj = const_cast<QObject*>(pQmlObj);

    m_pLat = pQmlObj->findChild<QObject*>("lat");
    m_pLon = pQmlObj->findChild<QObject*>("lon");
    m_pAlt = pQmlObj->findChild<QObject*>("alt");
    m_pSpeed = pQmlObj->findChild<QObject*>("speed");
    m_pTime = pQmlObj->findChild<QObject*>("time");
}

void CLocationObserver::UpdateData(const CLocationInfo& info)
{
    CGeoCoordinates geoCoordinate(info.GetLatitude(), info.GetLongitude());

    m_pLat->setProperty("text", QVariant(geoCoordinate.getLatString(CGeoCoordinates::DegreesWithHemisphere)));
    m_pLon->setProperty("text", QVariant(geoCoordinate.getLongString(CGeoCoordinates::DegreesWithHemisphere)));
    m_pAlt->setProperty("text", QVariant(QString::number(info.GetAltitude()) + " m"));
    m_pSpeed->setProperty("text", QVariant(QString::number(info.GetSpeed()) + " km/h"));
    m_pTime->setProperty("text", QVariant(QDateTime::fromMSecsSinceEpoch(info.GetTimeStamp()).toString(Qt::DefaultLocaleLongDate)));

    QQmlProperty::write(m_pQmlObj, "sharedValue", QVariant(geoCoordinate.getLatString(CGeoCoordinates::DegreesWithHemisphere) +
                                                           "\n" + geoCoordinate.getLongString(CGeoCoordinates::DegreesWithHemisphere)));
}
