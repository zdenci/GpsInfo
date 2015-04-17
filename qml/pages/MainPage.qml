import QtQuick 2.0
import Sailfish.Silica 1.0
import "../content"

Page {
    id: root
    width: Screen.width
    height: Screen.height

    property string fontColor: "white"
    property int fontSize: 24

    Item {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12

        SatellitesPosition {
            id: satPosition
            width: parent.width * 0.9
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SatellitesSignal {
            id: satSignal
            anchors.top: satPosition.bottom
            anchors.topMargin: 20
            width: parent.width
            height: parent.height * 0.2
        }

        Text {
            id: time
            objectName: "time"
            anchors.top: satSignal.bottom
            anchors.topMargin: 20
            font.pixelSize: fontSize
            color: fontColor
            text: "0:0:0"
        }

        GpsStatus {
            anchors.top: time.bottom
            anchors.topMargin: 20
        }
    }
}
