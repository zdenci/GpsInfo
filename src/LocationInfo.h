#ifndef LOCATIONINFO_H
#define LOCATIONINFO_H

#include <QtGlobal>

class CLocationInfo
{
private:
    bool m_bIsValid;
    qint64 m_lTime;
    double m_dLatitude, m_dLongitude, m_dAltitude;
    int m_iFix;
    qreal m_fSpeed;

public:
    CLocationInfo() : m_bIsValid(false), m_lTime(0), m_dLatitude(0), m_dLongitude(0),
        m_dAltitude(0), m_iFix(0), m_fSpeed(0) {}

public:
    void SetValid(const bool bValid) { m_bIsValid = bValid; }
    bool IsValid() const { return m_bIsValid; }

    void SetTimeStamp(const qint64 lTime) { m_lTime = lTime; }
    qint64 GetTimeStamp() const { return m_lTime; }

    void SetLatitude(const double dLat) { m_dLatitude = dLat; }
    double GetLatitude() const { return m_dLatitude; }

    void SetLongitude(const double dLon) { m_dLongitude = dLon; }
    double GetLongitude() const { return m_dLongitude; }

    void SetAltitude(const double dAlt) { m_dAltitude = dAlt; }
    double GetAltitude() const { return m_dAltitude; }

    void SetFix(const int iFix) { m_iFix = iFix; }
    int GetFix() const { return m_iFix; }

    void SetSpeed(const qreal fSpeed) { m_fSpeed = fSpeed; }
    qreal GetSpeed() const { return m_fSpeed; }
};

#endif // LOCATIONINFO_H
