import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2

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
            //var path = filedialog.fileUrl.toString();
        }
        //nameFilters:  []
    }

    Rectangle{
        width: 1020
        height: 65
        color: "#f0f0f5"
        anchors.right: parent.right
        anchors.left: parent.left

        RowLayout {
            id: row1
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            height: parent.height
            spacing: 10

            Button {
                id: removeButton
                width: 150
                height: 30
                text: "Remove all"

                onClicked: {
                    backupModel.removeAll()
                }
            }

            Button {
                id: addButton
                width: 150
                height: 30
                text: "Add"
                onClicked: {
                    fileDialog.open()
                }

            }
        }
    }


        Rectangle{
            width: 1020
            height: 750
            color: "white"
            anchors.top: parent.top
            anchors.topMargin: 65

            ColumnLayout {
                anchors.margins: 10
                anchors.fill: parent

                ListView {
                    id: view
                    width: parent.width
                    height: parent.height
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

