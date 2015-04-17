#include "LocationObserver.h"
#include <QVariant>
#include <QDateTime>

CLocationObserver::CLocationObserver(const QObject* pQmlObj)
{
    m_pLat = pQmlObj->findChild<QObject*>("lat");
    m_pLon = pQmlObj->findChild<QObject*>("lon");
    m_pAlt = pQmlObj->findChild<QObject*>("alt");
    m_pSpeed = pQmlObj->findChild<QObject*>("speed");
    m_pTime = pQmlObj->findChild<QObject*>("time");
}

void CLocationObserver::UpdateData(const CLocationInfo& info)
{
    m_pLat->setProperty("text", QVariant(QString::number(info.GetLatitude())));
    m_pLon->setProperty("text", QVariant(QString::number(info.GetLongitude())));
    m_pAlt->setProperty("text", QVariant(QString::number(info.GetAltitude()) + " m"));
    m_pSpeed->setProperty("text", QVariant(QString::number(info.GetSpeed()) + " km/h"));
    m_pTime->setProperty("text", QVariant(QDateTime::fromMSecsSinceEpoch(info.GetTimeStamp()).toString(Qt::DefaultLocaleLongDate)));
}
