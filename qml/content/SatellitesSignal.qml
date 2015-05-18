import QtQuick 2.0
import harbour.gpsinfo 1.0

Rectangle {
    id: rec
    width: parent.width
    height: parent.height
    color: "transparent"
    border.color: "#60F4F4F8"
    radius: 4

    // horizontal lines to help vizualize percentage
    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");

            ctx.strokeStyle = "#30F4F4F8";
            ctx.lineWidth = 1;
            for (var i = 1; i < 4; i++) {
                ctx.moveTo(0, parent.height*i/4);
                ctx.lineTo(parent.width, parent.height*i/4);
                ctx.stroke();
            }
        }
    }

    Text {
        text: qsTr("In View: ") + repeater.model.inViewCount
        color: fontColor
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 8
    }
    Text {
        text: qsTr("In Use: ") + satModel.inUseCount
        color: fontColor
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 8
    }


    property int satSpacing: 4
    property int satCount: 12

    Row {
        id: row
        anchors.fill: parent
        spacing: satSpacing

        Repeater {
            id: repeater
            model: SatellitesInfoModel {
                id: satModel
            }
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
