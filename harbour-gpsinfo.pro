# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-gpsinfo

CONFIG += sailfishapp

QT += positioning

SOURCES += src/GpsInfo.cpp \
    src/LocationService.cpp \
    src/LocationObserver.cpp \
    src/SatellitesInfoModel.cpp \
    src/GeoCoordinates.cpp

OTHER_FILES += qml/GpsInfo.qml \
    qml/cover/CoverPage.qml \
    translations/*.ts \
    qml/content/GpsStatus.qml \
    qml/content/SatellitesPosition.qml \
    qml/images/sat.png \
    qml/content/SatellitesSignal.qml \
    qml/pages/MainPage.qml \
    qml/values/Constants.qml \
    qml/images/satInUse.png \
    qml/images/satInView.png \
    rpm/harbour-gpsinfo.spec \
    harbour-gpsinfo.desktop \
    rpm/harbour-gpsinfo.yaml \
    rpm/harbour-gpsinfo.changes.in

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-gpsinfo-de.ts

HEADERS += \
    src/LocationService.h \
    src/LocationObserver.h \
    src/LocationInfo.h \
    src/SatellitesInfoModel.h \
    src/GeoCoordinates.h

