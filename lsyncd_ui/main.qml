import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2
import QtQuick.Controls.Styles 1.1
import "Colors.js" as Colors
import "Images.js" as Images

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

    FileDialog {
        id: folderDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            backupModel.addItems(folderDialog.fileUrls)
        }
    }

    Rectangle{
        anchors.fill: parent
        anchors.margins: 10
        color: Colors.applicationListColor

        ColumnLayout {
            anchors.margins: 10
            anchors.fill: parent

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 65
                color: Colors.buttonsPanelColor

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
                        id: addFilesButton
                        text: "Add files"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            fileDialog.open()
                        }
                    }
                    ElButton {
                        id: addFolderButton
                        text: "Add directory"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            folderDialog.open()
                        }
                    }
                }
            }

            ElScrollView {
                id: scrollView
                anchors.left: parent.left
                anchors.right: parent.right
                Layout.fillHeight: true
                property bool areScrollBarsVisible: flickableItem.contentHeight > flickableItem.height

                ListView {
                    id: view
                    anchors.fill: parent
                    clip: true

                    model: backupModel

                    delegate: Rectangle {
                        color: index % 2 ? Colors.buttonsPanelColor : Colors.applicationListColor
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.rightMargin: scrollView.areScrollBarsVisible ? 10 : 0
                        height: 25

                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 45
                            anchors.verticalCenter: parent.verticalCenter
                            text: path
                        }
                        Item {
                            anchors.top: parent.top
                            anchors.topMargin: 4
                            anchors.left: parent.left
                            anchors.leftMargin: 10

                            Image {
                                source: isfile ? Images.fileUrl : Images.folderUrl
                            }
                        }
                    }
                }
            }
        }
    }
}


