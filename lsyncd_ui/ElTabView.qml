import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "Colors.js" as Colors;

TabView {
    style: TabViewStyle {
        property color backgroundColor: Colors.applicationBackgroundColor
        property double tabHeight: 150

        frame: Rectangle {
            color: Colors.applicationBackgroundColor

            Rectangle {
                anchors.left: parent.left
                width: 1
                color: Colors.normalGrayColor
                anchors.top: parent.top
                anchors.bottom: parent.bottom

            }
        }

        tabBar: Rectangle {
            color: Colors.normalGrayColor

        }

        tab: Item { }
    }
}

