import QtQuick 2.0
import "Colors.js" as Colors

Item {
    id: elCircle
    property color borderColor
    property color insideColor
    anchors.verticalCenter: parent.verticalCenter

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: 15
        height: 15
        radius: width*0.5
        border.width: 1
        border.color: borderColor

        Rectangle {
            id: insideCircle
            anchors.fill: parent
            anchors.margins: 2
            radius: width*0.5
            border.color: borderColor
            color: insideColor
        }
    }

}
