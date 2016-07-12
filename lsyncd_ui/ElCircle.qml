import QtQuick 2.0
import "Colors.js" as Colors

Item {
    id: elCircle
    property color iconColor
    property bool isFilled

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: 15
        height: 15
        radius: width*0.5
        border.width: 1
        border.color: iconColor

        Rectangle {
            id: insideCircle
            anchors.fill: parent
            anchors.margins: 2
            radius: width*0.5
            border.color: iconColor
            border.width: isFilled ? 0 : 1
            color: isFilled ? iconColor : "transparent"
        }
    }
}
