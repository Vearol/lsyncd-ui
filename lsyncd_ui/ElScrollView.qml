import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "Colors.js" as Colors;

ScrollView {
    style: ScrollViewStyle {
        handle: Item {
            implicitHeight: 20
            implicitWidth: 20

            Rectangle {
                anchors.fill: parent
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                radius: 10
                color: Colors.blueActiveColor
                opacity: styleData.pressed ? 1 : (styleData.hovered ? 0.9 : 0.8)
            }
        }

        scrollBarBackground: Item {
            property bool sticky: false
            property bool hovered: styleData.hovered
            implicitWidth: 20
            implicitHeight: 20
            clip: true

            onHoveredChanged: if (hovered) sticky = true
        }

        corner: Item {}
        decrementControl: Item { width: 1; height: 1 }
        incrementControl: Item { width: 1; height: 1 }
    }
}

