#ifndef SATELLITESINFOMODEL_H
#define SATELLITESINFOMODEL_H

#include <QAbstractListModel>
#include <QGeoSatelliteInfo>
#include <QtQml/QQmlParserStatus>
#include <QtQml/qqml.h>
#include <QSet>

class CSatellitesInfoModel : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(int inViewCount READ inViewCount NOTIFY inViewCountChanged)
    Q_PROPERTY(int inUseCount READ inUseCount NOTIFY inUseCountChanged)

    Q_INTERFACES(QQmlParserStatus)

public:
    enum ERoleNames {
        RNId = Qt::UserRole + 1,
        RNInUse,
        RNStrength,
        RNAzimuth,
        RNElevation,
        RNSystem
    };

private:
    QList<QGeoSatelliteInfo> m_lstSatInView;
    QSet<int> m_setSatInUse;
    QHash<int, QByteArray> m_roleNames;

public:
    explicit CSatellitesInfoModel(QObject* parent = 0);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    // QQmlParserStatus interface
public:
    void classBegin() {}
    void componentComplete();

    int inViewCount() const;
    int inUseCount() const;

signals:
    void inViewCountChanged();
    void inUseCountChanged();

public slots:
    void clearModel();

public:
    void update(const QList<QGeoSatelliteInfo>& satellites, bool bInUse);
};

QML_DECLARE_TYPE(CSatellitesInfoModel)

#endif // SATELLITESINFOMODEL_H
