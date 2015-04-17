import QtQuick 2.0
import com.zdeno 1.0

Rectangle {
    id: rec
    width: parent.width
    height: parent.height
    color: "transparent"
    border.color: "#60F4F4F8"
    radius: 4

    property int satSpacing: 4
    property int satCount: 12

    SatellitesInfoModel {
        id: satModel
    }

    Row {
        id: row
        spacing: satSpacing

        Repeater {
            id: repeater
            model: satModel
//            model: SatellitesInfoModel {}
//            width: rec.width/satCount - satSpacing
            height: row.height

            delegate: Rectangle {
                anchors.bottom: row.bottom
                width: (rec.width - (satSpacing * (satCount-1))) / satCount
                height: rec.height
                color: "transparent"

                Rectangle {
                    id: satRec
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: satStrength == 0 ? 5 : parent.height * satStrength/100
                    color: satInUse ? "blue" : "#9EB0C8"
//                    color: satInUse ? "blue" : "#B0C4DE"
                    radius: 2
                }
                Text {
                    text: satId
                    style: Text.Outline; styleColor: "black"; color: "white"
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        } // Repeater
    }

}
