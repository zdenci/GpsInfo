#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

#include <QString>

class CGeoCoordinates
{
public:
    enum ECoordinateFormat {
        Degrees,
        DegreesWithHemisphere,
        DegreesMinutes,
        DegreesMinutesWithHemisphere,
        DegreesMinutesSeconds,
        DegreesMinutesSecondsWithHemisphere
    };

private:
    double m_dLatitude, m_dLongitude;

public:
    CGeoCoordinates(const double latitude, const double longitude);

private:
    QString formatValue(const double dValue, const ECoordinateFormat eFormat);

public:
    QString getLatString(const ECoordinateFormat eFormat);
    QString getLongString(const ECoordinateFormat eFormat);
};

#endif // GEOCOORDINATES_H
