import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.0

Window {
    visible: true
    width: 1020
    height: 810

    Rectangle{
        width:  1020
        height: 60
        color: "#c2c2d6"

        Text{
            anchors.left: parent.left
            anchors.leftMargin: 100
            text: "Backup disk:"
            font.pointSize: 18
        }
    }

    Rectangle{
        width: 100
        height: 810
        color: "#7f7f8c"

        Rectangle{
            y: 60
            width: 100
            height: 150
            border {
                color: "black"
                width: 1
            }
            color: "#7f7f8c"
            Text{
                anchors.bottom: parent.bottomК
                text: "     Tree"
                font.pointSize: 15
            }
        }

        Rectangle{
            y: 209
            width: 100
            height: 150
            border {
                color: "black"
                width: 1
            }
            color: "#7f7f8c"
            Text{
                anchors.bottom: parent.bottom
                text: "      List"
                font.pointSize: 15
            }
        }
    }


    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            myModel.addItems()
        }
    }


    Rectangle{
        x: 100; y: 60
        width: 920
        height: 695
        color: "#e1e1ea"

        Rectangle{
            width: 880
            height: 65
            color: "#f0f0f5"

            Row {
                id: row1
                anchors.right: parent.right
                height: parent.height
                spacing: 10
                anchors.margins: 10



                Button {
                    id: removeButton
                    width: 150
                    height: 30
                    text: "Remove all / Close"

                    onClicked: {
                        close()
                    }
                }

                Button {
                    id: addButton
                    width: 150
                    height: 30
                    text: "Add"
                    onClicked: {
                        myModel.addItems()
                        //fileDialog.open()
                    }

                }
            }
        }

        Rectangle{
            y: 65
            width: 880
            height: 630
            color: "white"

            Column {
                anchors.margins: 10
                anchors.fill: parent

                ListView {
                    id: view
                    width: parent.width
                    height: parent.height
                    spacing: 10
                    clip: true

                    model: myModel

                    delegate: Rectangle {
                        width: parent.width - 45
                        height: 25
                        color: "white"
                        border.width: 1
                        border.color: "black"

                        Text {
                            anchors.left: parent.left
                            text: ' ' + model.super_name + ' ' + model.surname + ' ' + model.index
                        }
                    }
                }
            }
        }

    }
}

