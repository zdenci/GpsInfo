#ifndef LOCATIONSERVICE_H
#define LOCATIONSERVICE_H

#include <QtPositioning>
#include "LocationObserver.h"
#include "LocationInfo.h"
#include "SatellitesInfoModel.h"

class CLocationService : public QObject
{
    Q_OBJECT
private:
    QGeoPositionInfoSource* m_pPositionInfoSource;
    QGeoSatelliteInfoSource* m_pSatelliteInfoSource;
    CLocationObserver m_locObserver;
//    static CSatellitesInfoModel* m_pSatModel;
    static QList<CSatellitesInfoModel*> m_lstSatModels;

protected:
    explicit CLocationService(QObject* parent = 0) { Q_UNUSED(parent) }
public:
    CLocationService(const CLocationObserver& observer);
    ~CLocationService();

public:
    static void registerSatelliteModel(CSatellitesInfoModel* pModel) { m_lstSatModels.append(pModel); }

private:
    static bool cmpSat(const QGeoSatelliteInfo& s1, const QGeoSatelliteInfo& s2)
    {
        return s1.signalStrength() > s2.signalStrength();
    }

private slots:
    void positionUpdated(const QGeoPositionInfo& update);

    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &satellites);

};

#endif // LOCATIONSERVICE_H
