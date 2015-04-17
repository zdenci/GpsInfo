import QtQuick 2.0
import QtGraphicalEffects 1.0
import com.zdeno 1.0
import "../content"

Item {
    id: satRect
    width: parent.width
    height: width

    property int outerCircleSize: 24

    Canvas {
        anchors.fill: parent
        anchors.margins: 20

        Component.onCompleted: {
            loadImage("../images/sat.png");
        }

        onPaint: {
            var ctx = getContext("2d");
            var x = width/2;
            var y = height/2;
            var r = x - outerCircleSize;

            // white canvas
            ctx.beginPath();
            ctx.clearRect(0, 0, width, height);
            ctx.fill();

            // circle
            ctx.fillStyle = "midnightblue" // #191970
            ctx.strokeStyle = "gainsboro"
//            ctx.lineWidth = 2;
            ctx.moveTo(x+r, y);
            ctx.arc(x, y, r, 0, 2*Math.PI, true);
            ctx.fill();
//            ctx.stroke();

            // line
            var lines = 8;
            var angle = 2*Math.PI / lines;
            for (var i = 0; i < lines; i++) {
                ctx.strokeStyle = "#F4F4F8";
                ctx.lineWidth = 1;
                ctx.moveTo(x, y);
                ctx.lineTo(x + r*Math.cos(angle*i), y + r*Math.sin(angle*i));
                ctx.stroke();
            }

            // inner circles
            var circles = 4;
            var distance = 2*r / (2*circles);
            for (var j = 1; j <= circles; j++) {
                var radius = distance * j;
                ctx.strokeStyle = "gainsboro";
                ctx.lineWidth = 1;
                ctx.moveTo(x + radius, y);
                ctx.arc(x, y, radius, 0, 2*Math.PI, true);
                ctx.stroke();
            }

            // letters
            ctx.font = "bold 24px sans-serif";
            ctx.fillStyle = "white";
            ctx.textAlign = "center";
            ctx.textBaseline = "top";//top, hanging, middle, alphabetic, ideographic, bottom
            ctx.save();
            ctx.translate(0, 0);
            ctx.rotate(0*Math.PI);
            ctx.fillText("N", x, 0);
            ctx.restore();
            ctx.save();
            ctx.translate(2*x, 0);
            ctx.rotate(0.5*Math.PI);
            ctx.fillText("E", x, 0);
            ctx.restore();
            ctx.save();
            ctx.translate(2*x, 2*y);
            ctx.rotate(Math.PI);
            ctx.fillText("S", x, 0);
            ctx.restore();
            ctx.save();
            ctx.translate(0, 2*y);
            ctx.rotate(1.5*Math.PI);
            ctx.fillText("W", x, 0);
            ctx.restore();
        } // onPaint
    } // Canvas

    Repeater {
        model: SatellitesInfoModel {}
        delegate: Item {
            property int radius: (90-satElevation) * (satRect.width-outerCircleSize)/2 / 100
            property int cx: satRect.width/2 + Math.cos(satAzimuth*Math.PI/180 + Math.PI/2) * radius
            property int cy: satRect.height/2 - Math.sin(satAzimuth*Math.PI/180 + Math.PI/2) * radius
            Image {
                id: img
//                source: "../images/sat.png"
                source: satInUse ? "../images/satInUse.png" : "../images/satInView.png"
                x: cx; y: cy
            }
//            ColorOverlay {
//                anchors.fill: img
//                source: img
//                color: satInUse ? "#0055FF" : "#9EB0C8"
//            }
            Text {
                x: cx; y: cy
                text: satId
//                color: "#F2F2F9"
//                color: "black"
                style: Text.Outline; styleColor: "black"; color: "white"
                font.pointSize: 16
                width: img.width
                height: img.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    } // Repeater

    // radar
    Canvas {
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            var x = width/2;
            var y = height/2;

            var gradient = ctx.createConicalGradient(x, y, Math.PI);
            gradient.addColorStop(1, "#80191970")
            gradient.addColorStop(0, "#60DCDCEA")

            ctx.beginPath();
            ctx.fillStyle = gradient;
            ctx.moveTo(x, y);
            ctx.arc(x, y, x, 0, 2*Math.PI, true);
            ctx.fill();
        }

        RotationAnimation on rotation {
            from: 0
            to: 360
            duration: 5000
            loops: Animation.Infinite
        }
    } // Canvas
}
