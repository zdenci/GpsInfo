#include "SatellitesInfoModel.h"
#include "LocationService.h"

CSatellitesInfoModel::CSatellitesInfoModel(QObject* parent/* = 0*/)
{
    Q_UNUSED(parent);

    m_roleNames[RNId] = "satId";
    m_roleNames[RNInUse] = "satInUse";
    m_roleNames[RNStrength] = "satStrength";
    m_roleNames[RNAzimuth] = "satAzimuth";
    m_roleNames[RNElevation] = "satElevation";
    m_roleNames[RNSystem] = "satSystem";
}

int CSatellitesInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return qMin(m_lstSatInView.size(), 12);
}

QVariant CSatellitesInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_lstSatInView.size())
        return QVariant();

    const QGeoSatelliteInfo& satInfo = m_lstSatInView.at(index.row());
    switch (role) {
    case RNId:
        return satInfo.satelliteIdentifier();
    case RNInUse:
        return m_setSatInUse.contains(satInfo.satelliteIdentifier());
    case RNStrength:
        return satInfo.signalStrength();
    case RNAzimuth:
        if (satInfo.hasAttribute(QGeoSatelliteInfo::Azimuth))
            return satInfo.attribute(QGeoSatelliteInfo::Azimuth);
        break;
    case RNElevation:
        if (satInfo.hasAttribute(QGeoSatelliteInfo::Elevation))
            return satInfo.attribute(QGeoSatelliteInfo::Elevation);
        break;
    case RNSystem:
        return satInfo.satelliteSystem();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> CSatellitesInfoModel::roleNames() const
{
    return m_roleNames;
}

void CSatellitesInfoModel::componentComplete()
{
    CLocationService::registerSatelliteModel(this);
    clearModel();
}

void CSatellitesInfoModel::clearModel()
{
    beginResetModel();

    m_setSatInUse.clear();
    m_lstSatInView.clear();

    endResetModel();
}

void CSatellitesInfoModel::update(const QList<QGeoSatelliteInfo>& satellites, bool bInUse)
{
    if (bInUse)
    {
        m_setSatInUse.clear();
        foreach (QGeoSatelliteInfo satInfo, satellites)
        {
            m_setSatInUse << satInfo.satelliteIdentifier();
        }
    }
    else
    {
        beginResetModel();

        m_lstSatInView = satellites;

        endResetModel();
    }
}
