import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2
import "Colors.js" as Colors

Window {
    visible: true
    width: 1020
    height: 810

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: true
        onAccepted: {
            backupModel.addItems(fileDialog.fileUrls)
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: Colors.applicationBackgroundColor

        ColumnLayout {
            anchors.margins: 10
            anchors.fill: parent

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 65
                color: "white"

                RowLayout {
                    anchors.fill: parent
                    anchors.rightMargin: 10
                    id: row1
                    spacing: 10

                    Item {
                       Layout.fillWidth: true
                    }

                    ElButton {
                        id: removeButton
                        text: "Remove all"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            backupModel.removeAll()
                        }
                    }

                    ElButton {
                        id: addButton
                        text: "Add"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            fileDialog.open()
                        }
                    }
                }
            }

            ListView {
                id: view
                anchors.left: parent.left
                anchors.right: parent.right
                height: 690
                spacing: 10
                clip: true

                model: backupModel

                delegate: Rectangle {
                    width: parent.width
                    height: 25

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 45
                        text: path
                    }
                    Image{
                        source: "qrc:/assets/folder_blue.svg"
                    }
                }
            }
        }
    }

}

