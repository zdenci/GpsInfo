#include "GeoCoordinates.h"

CGeoCoordinates::CGeoCoordinates(const double latitude, const double longitude)
{
    m_dLatitude = latitude;
    m_dLongitude = longitude;
}

QString CGeoCoordinates::getLatString(const ECoordinateFormat eFormat)
{
    QString strValue = formatValue(m_dLatitude, eFormat);

    // now add the "-" to the start, or append the hemisphere char
    switch (eFormat)
    {
        case Degrees:
        case DegreesMinutes:
        case DegreesMinutesSeconds:
            if (m_dLatitude < 0)
                strValue.insert(0, "-");
            break;
        case DegreesWithHemisphere:
        case DegreesMinutesWithHemisphere:
        case DegreesMinutesSecondsWithHemisphere:
            if (m_dLatitude < 0)
                strValue.append(QString(" S"));
            else if (m_dLatitude > 0)
                strValue.append(QString(" N"));
            break;
    }

    return strValue;
}

QString CGeoCoordinates::getLongString(const ECoordinateFormat eFormat)
{
    QString strValue = formatValue(m_dLongitude, eFormat);

    // now add the "-" to the start, or append the hemisphere char
    switch (eFormat)
    {
        case Degrees:
        case DegreesMinutes:
        case DegreesMinutesSeconds:
            if (m_dLongitude < 0)
                strValue.insert(0, "-");
            break;
        case DegreesWithHemisphere:
        case DegreesMinutesWithHemisphere:
        case DegreesMinutesSecondsWithHemisphere:
            if (m_dLongitude < 0)
                strValue.append(QString(" W"));
            else if (m_dLongitude > 0)
                strValue.append(QString(" E"));
            break;
    }

    return strValue;
}

QString CGeoCoordinates::formatValue(const double dValue, const ECoordinateFormat eFormat)
{
    QString strValue;

    double dAbsValue = qAbs(dValue);
    QChar symbol(0x00B0);   // degrees symbol

    switch (eFormat)
    {
        case Degrees:
        case DegreesWithHemisphere:
            strValue = QString::number(dAbsValue, 'f', 5) + symbol;
            break;
        case DegreesMinutes:
        case DegreesMinutesWithHemisphere: {
            double dMin = (dAbsValue - int(dAbsValue)) * 60;
            strValue = QString("%1%2 %3'")
                     .arg(QString::number(int(dAbsValue)))
                     .arg(symbol)
                     .arg(QString::number(dMin, 'f', 3));
            break;
        }
        case DegreesMinutesSeconds:
        case DegreesMinutesSecondsWithHemisphere: {
            double dMin = (dAbsValue - int(dAbsValue)) * 60;
            double dSec = (dMin - int(dMin)) * 60;

            strValue = QString("%1%2 %3' %4\"")
                     .arg(QString::number(int(dAbsValue)))
                     .arg(symbol)
                     .arg(QString::number(int(dMin)))
                     .arg(QString::number(dSec, 'f', 1));
            break;
        }
    }

    return strValue;
}
