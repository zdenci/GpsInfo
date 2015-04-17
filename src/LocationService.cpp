#include "LocationService.h"
#include "LocationInfo.h"

/*static*/
//CSatellitesInfoModel* CLocationService::m_pSatModel = NULL;
QList<CSatellitesInfoModel*> CLocationService::m_lstSatModels;

CLocationService::CLocationService(const CLocationObserver& observer)
{
    m_locObserver = observer;
    m_pPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(0);
    m_pSatelliteInfoSource = QGeoSatelliteInfoSource::createDefaultSource(0);

    if ( !m_pPositionInfoSource )
    {
        qWarning("Position info source failed!!!");
        return;
    }
    if ( !m_pSatelliteInfoSource )
    {
        qWarning("Satellite info source failed!!!");
        return;
    }

    m_pPositionInfoSource->startUpdates();
    connect(m_pPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));

    m_pSatelliteInfoSource->startUpdates();
    connect(m_pSatelliteInfoSource, SIGNAL(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)),
            this, SLOT(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)));
    connect(m_pSatelliteInfoSource, SIGNAL(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)),
            this, SLOT(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)));
}

CLocationService::~CLocationService()
{
    if ( !m_pPositionInfoSource )
    {
        m_pPositionInfoSource->stopUpdates();
        delete m_pPositionInfoSource;
    }

    foreach (CSatellitesInfoModel* pSatModel, m_lstSatModels)
    {
        if ( !pSatModel )
        {
            delete pSatModel;
            pSatModel = NULL;
        }
    }
    m_lstSatModels.clear();
}

/*slot*/
void CLocationService::positionUpdated(const QGeoPositionInfo& update)
{
//    qDebug("direction - %d", update.hasAttribute(QGeoPositionInfo::Direction));
//    qDebug("groundSpeed - %d", update.hasAttribute(QGeoPositionInfo::GroundSpeed));
//    qDebug("hdop- %d", update.hasAttribute(QGeoPositionInfo::HorizontalAccuracy));
//    qDebug("vdop- %d", update.hasAttribute(QGeoPositionInfo::VerticalAccuracy));

    bool bIsValid = update.isValid();
    qint64 lTime = update.timestamp().toMSecsSinceEpoch();
    double dLat = update.coordinate().latitude();
    double dLon = update.coordinate().longitude();
    double dAlt= update.coordinate().altitude();
    QGeoCoordinate::CoordinateType eType = update.coordinate().type();

//    qDebug("%s - %fx%f", (char *)update.timestamp().toString().toUtf8().constData(), dLat, dLon);

    CLocationInfo info;
    info.SetValid(bIsValid);
    info.SetTimeStamp(lTime);
    info.SetLatitude(dLat);
    info.SetLongitude(dLon);
    info.SetAltitude(dAlt);
    info.SetFix((int)eType);
    if (update.hasAttribute(QGeoPositionInfo::GroundSpeed))
        info.SetSpeed(update.attribute(QGeoPositionInfo::GroundSpeed));

    m_locObserver.UpdateData(info);
}

void CLocationService::satellitesInViewUpdated(const QList<QGeoSatelliteInfo>& satellites)
{
    QList<QGeoSatelliteInfo> satList(satellites);
    qSort(satList.begin(), satList.end(), cmpSat);
//    qDebug("Satellites: %d", satellites.size());
//    foreach (QGeoSatelliteInfo satInfo, satList) {
//        qDebug("Sat #%d = %d, %d; %f, %f", satInfo.satelliteIdentifier(), satInfo.signalStrength(),
//               satInfo.satelliteSystem(), satInfo.attribute(QGeoSatelliteInfo::Azimuth), satInfo.attribute(QGeoSatelliteInfo::Elevation));
//    }

    foreach (CSatellitesInfoModel* pSatModel, m_lstSatModels)
    {
        pSatModel->update(satList, false);
    }
}

void CLocationService::satellitesInUseUpdated(const QList<QGeoSatelliteInfo>& satellites)
{
//    QList<QGeoSatelliteInfo> satList(satellites);
//    qSort(satList.begin(), satList.end(), cmpSat);
//    qDebug("Satellites: %d", satellites.size());
//    foreach (QGeoSatelliteInfo satInfo, satList) {
//        qDebug("Sat #%d = %d, %d; %f, %f", satInfo.satelliteIdentifier(), satInfo.signalStrength(),
//               satInfo.satelliteSystem(), satInfo.attribute(QGeoSatelliteInfo::Azimuth), satInfo.attribute(QGeoSatelliteInfo::Elevation));
//    }

    foreach (CSatellitesInfoModel* pSatModel, m_lstSatModels)
    {
        pSatModel->update(satellites, true);
    }
}
