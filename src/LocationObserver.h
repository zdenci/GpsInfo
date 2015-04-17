#ifndef LOCATIONOBSERVER_H
#define LOCATIONOBSERVER_H

#include "LocationInfo.h"
#include <QObject>
#include <QVariant>

class CLocationObserver
{
private:
    QObject* m_pLat;
    QObject* m_pLon;
    QObject* m_pAlt;
    QObject* m_pSpeed;
    QObject* m_pTime;

public:
    CLocationObserver() {}
    CLocationObserver(const QObject* pQmlObj);

    void UpdateData(const CLocationInfo& info);
};

#endif // LOCATIONOBSERVER_H
