import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2
import QtQuick.Controls.Styles 1.1
import "Colors.js" as Colors

Item {
    id: myPopupComponent
    anchors.fill: parent

    function closePopup() {
        myPopupComponent.destroy()
    }

    PropertyAnimation { target: myPopupComponent; property: "opacity";
        duration: 400; from: 0; to: 1;
        easing.type: Easing.InOutQuad ; running: true }

    Rectangle {
        anchors.fill: parent
        id: overlay
        color: Colors.darkGrayColor
        opacity: 0.6
        MouseArea {
            anchors.fill: parent
        }
    }

    FocusScope {
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onWheel: wheel.accepted = true
            onClicked: mouse.accepted = true
            onDoubleClicked: mouse.accepted = true

            property real old_x : 0
            property real old_y : 0

            onPressed:{
                var tmp = mapToItem(myPopupComponent, mouse.x, mouse.y);
                old_x = tmp.x;
                old_y = tmp.y;

                var dialogPoint = mapToItem(dialogWindow, mouse.x, mouse.y);
                if (!Common.isInComponent(dialogPoint, dialogWindow)) {
                    closePopup()
                }
            }

            onPositionChanged: {
                var old_xy = Common.movePopupInsideComponent(myPopupComponent, dialogWindow, mouse, old_x, old_y);
                old_x = old_xy[0]; old_y = old_xy[1];
            }
        }

        Rectangle {
            id: dialogWindow
            width: 845
            height: 615
            color: Colors.applicationBackgroundColor
            anchors.centerIn: parent
            Component.onCompleted: anchors.centerIn = undefined

            Rectangle {
                anchors.fill: parent
                color: Colors.applicationBackgroundColor

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 20
                    anchors.bottomMargin: 60

                    color: Colors.normalTextColor

                    TextEdit {
                        anchors.fill: parent
                        anchors.margins: 35

                        text: lsyncdConfigModel.createConfig();
                    }
                }

                RowLayout {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    height: 60;
                    id: row1
                    spacing: 30

                    Item {
                        Layout.fillWidth: true
                    }

                    ConfigButton {
                        id: backButton
                        text: "Back"
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: closePopup()
                    }

                    ConfigButton {
                        id: saveToFileButton
                        text: "Save to file"
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            saveToFileDialog.open()
                            lsyncdConfigModel.saveToFile()
                        }

                    }
                }
            }
        }
    }
}


