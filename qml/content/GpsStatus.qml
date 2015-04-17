import QtQuick 2.0

Grid {
//    id: infoGrid
//    anchors.top: time.bottom
    columns: 2
    columnSpacing: 2
//    property string fontColor: "white"
//    property int fontSize: 24

    Text {
        font.pixelSize: fontSize
        color: fontColor
        text: qsTr("Latitude: ")
    }
    Text {
        objectName: "lat"
        font.pixelSize: fontSize
        color: fontColor
        text: "0.0"
    }

    Text {
        font.pixelSize: fontSize
        color: fontColor
        text: qsTr("Longitude: ")
    }
    Text {
        objectName: "lon"
        font.pixelSize: fontSize
        color: fontColor
        text: "0.0"
    }

    Text {
        font.pixelSize: fontSize
        color: fontColor
        text: qsTr("Altitude: ")
    }
    Text {
        objectName: "alt"
        font.pixelSize: fontSize
        color: fontColor
        text: "0.0"
    }

    Text {
        font.pixelSize: fontSize
        color: fontColor
        text: qsTr("Speed: ")
    }
    Text {
        objectName: "speed"
        font.pixelSize: fontSize
        color: fontColor
        text: "0.0"
    }
}
