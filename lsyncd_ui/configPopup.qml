import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2
import QtQuick.Controls.Styles 1.1

Item {
    Rectangle {
        anchors.fill: parent
        color: Colors.applicationBackgroundColor

        Rectangle {
            anchors.fill: parent
            anchors.margins: 20
            anchors.bottomMargin: 60

            color: "#ffffff"
            TextEdit {
                anchors.fill: parent
                anchors.margins: 35

                text: backupModel.createConfig();
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

            PopoutButton {
                id: backButton
                text: "Back"
                anchors.verticalCenter: parent.verticalCenter
                onClicked: generateDialog.close()
            }

            PopoutButton {
                id: saveToFileButton
                text: "Save to file"
                anchors.verticalCenter: parent.verticalCenter

            }
        }
    }
}

