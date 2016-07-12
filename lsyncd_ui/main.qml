import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs  1.2
import QtQuick.Controls.Styles 1.1
import QtQml.Models 2.2
import "Colors.js" as Colors
import "Images.js" as Images

Window {
    id: mainWindow
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    minimumWidth: 1020
    minimumHeight: 810

    MessageDialog {
        id: confirmRemoveAll
        title: "Warning"
        text: "Remove all items?"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            backupModel.removeAll()
        }
        onNo: confirmRemoveAll.close()
    }



    /*FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: true
        onAccepted: {
            backupModel.addItems(fileDialog.fileUrls)
            console.log(fileDialog.fileUrls)
        }
    }
    */
    FileDialog {
        id: outputFolderDialog
        title: "Please choose a path"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            lsyncdConfigModel.useBackupPath(outputFolderDialog.fileUrl)
        }
    }

    FileDialog {
        id: folderDialog
        title: "Please choose a folder"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            backupModel.addItems(folderDialog.fileUrls)
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 65
        color: Colors.applicationBackgroundColor

        Rectangle {
            id: header
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            color: Colors.normalGrayColor

            RowLayout {
                spacing: 20
                anchors.fill: parent
                anchors.leftMargin: tabsColumn.width + 10

                Text {
                    font.pixelSize: 20
                    color: Colors.normalTextColor

                    text: "Backup disk:"
                }

                Rectangle {
                    color: Colors.inputBackgroundColor
                    width: 250
                    height: 30

                    ElTextInput {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: lsyncdConfigModel.backupPath
                        onTextChanged: lsyncdConfigModel.backupPath = text
                    }
                }

                ActiveButton {
                    id: chooseBackupDiskButton

                    height: 30
                    width: 120
                    text: "Choose"
                    onClicked: outputFolderDialog.open();
                }

                Item {
                    Layout.fillWidth: true
                }
            }
        }

        Rectangle {
            id: tabsColumn
            anchors.left: parent.left
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            width: 100
            color: Colors.darkGrayColor

            Column {
                anchors.fill: parent

                Repeater {
                    id: tabsRepeater
                    model: tabView.count
                    delegate: Rectangle {
                        id: showType
                        width: 100
                        height: 150
                        color: (tabView.currentIndex == index) ? Colors.applicationBackgroundColor : Colors.notActiveTabColor
                        Item {
                            anchors.fill: parent

                            Image {
                                anchors.centerIn: parent

                                fillMode: Image.Pad
                                anchors.verticalCenterOffset: index == 0 ? -parent.width*0.1 : 0
                                property double scale: index == 0 ? 1.857142 : 1.175
                                property double basicScale: index == 0 ? 0.35 : 0.4
                                sourceSize.width: parent.width * basicScale
                                sourceSize.height: parent.width * basicScale * scale

                                source: {
                                    var tab = tabView.getTab(index);
                                    var isActiveTab = tabView.currentIndex == index;
                                    var imageSrc;

                                    if (itemsMA.containsMouse) {
                                        imageSrc = tab.hoverBackground;
                                    } else {
                                        if (isActiveTab) {
                                            imageSrc = tab.activeBackground;
                                        } else {
                                            imageSrc = tab.notActiveBackground;
                                        }
                                    }

                                    return imageSrc;
                                }
                            }

                            Text {
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 10
                                anchors.horizontalCenter: parent.horizontalCenter

                                text: {
                                    var showText;
                                    if (index == 0) {
                                        showText = "Tree";
                                    } else {
                                        showText = "List";
                                    }

                                    return showText;
                                }

                                font.pixelSize: 18

                                color: {
                                    var tab = tabView.getTab(index);
                                    var isActiveTab = tabView.currentIndex == index;
                                    var txtColor;

                                    if (itemsMA.containsMouse) {
                                        txtColor = Colors.normalTextColor;
                                    } else {
                                        if (isActiveTab) {
                                            txtColor = Colors.hoveredTextColor;
                                        } else {
                                            txtColor = Colors.normalGrayColor;
                                        }
                                    }

                                    return txtColor;
                                }
                            }
                        }

                        MouseArea {
                            id: itemsMA
                            hoverEnabled: true
                            anchors.fill: parent

                            onClicked: {
                                tabView.currentIndex = index
                            }
                        }
                    }
                }
            }
        }

        ElTabView {
            id: tabView
            anchors.left: tabsColumn.right
            anchors.top: header.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 65

            Tab {
                id: treeMode

                title: "Tree"
                property string activeBackground: Images.treeBlue
                property string notActiveBackground: Images.treeGray
                property string hoverBackground: Images.treeWhite

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 10

                    ElTreeView {
                        anchors.fill: parent
                        model: fileSystemModel
                        itemDelegate: Rectangle {
                            id: delegateRectangle
                            color: ( styleData.row % 2 == 0 ) ? Colors.buttonsPanelColor : Colors.applicationListColor
                            height: 25

                            ElCircle {
                                property string fullPath: fileSystemModel.getFilePath(styleData.index)
                                property bool isFullBackup: backupModel.isFullBackup(fullPath)
                                property bool isPartialBackup: backupModel.isPartialBackup(fullPath)
                                id: chooseIcon
                                anchors.left: parent.left
                                anchors.leftMargin: 25
                                iconColor: isFullBackup ? Colors.blueActiveColor: Colors.disabledTextColor
                                isFilled: isPartialBackup || isFullBackup
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            /*MouseArea {
                                id: selectCircle
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                anchors.left: parent.left
                                anchors.leftMargin: 25
                                width: 15
                                hoverEnabled: true
                                onClicked: backupModel.addSingle(index);
                            }*/

                            Image {
                                id: fileImage
                                anchors.left: chooseIcon.right
                                anchors.leftMargin: 15
                                fillMode: Image.PreserveAspectFit
                                sourceSize.height: parent.height * 0.6
                                sourceSize.width: parent.height * 0.6
                                anchors.verticalCenter: parent.verticalCenter
                                //source: isfile ? Images.fileUrl : Images.folderUrl
                                cache: true
                            }

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: fileImage.right
                                anchors.leftMargin: 5
                                color: {
                                    var treeTextColor = Colors.pathTextColor;
                                    if (selectCircle.containsMouse){
                                        treeTextColor = Colors.blueActiveColor;
                                    }
                                    return treeTextColor
                                }

                                text: styleData.value
                            }
                        }

                        TableViewColumn {
                            role: "fileName"
                        }

                    }
                }
            }

            Tab {
                id: tabList
                active: true
                property string activeBackground: Images.listBlue
                property string notActiveBackground: Images.listGray
                property string hoverBackground: Images.listWhite

                title: "List"

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
                                enabled: backupModel.itemsCount > 0
                                onClicked: {
                                    if (!backupModel.isEmpty())
                                        confirmRemoveAll.open()
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
                            id: backupListView
                            anchors.fill: parent
                            clip: true

                            model: backupModel

                            delegate: Rectangle {
                                id: addedFolder

                                color: index % 2 ? Colors.buttonsPanelColor : Colors.applicationListColor
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.rightMargin: scrollView.areScrollBarsVisible ? 10 : 0
                                height: 25

                                Image {
                                    id: iconImage
                                    anchors.left: parent.left
                                    anchors.leftMargin: 25
                                    fillMode: Image.PreserveAspectFit
                                    sourceSize.height: parent.height * 0.6
                                    sourceSize.width: parent.height * 0.6
                                    anchors.verticalCenter: parent.verticalCenter
                                    source: isfile ? Images.fileUrl : Images.folderUrl
                                    cache: true
                                }

                                Text {
                                    id: pathText
                                    anchors.left: iconImage.right
                                    anchors.leftMargin: 20
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: Colors.pathTextColor
                                    text: path
                                }

                                Image {
                                    anchors.right: parent.right
                                    anchors.rightMargin: 10
                                    sourceSize.height: parent.height / 2
                                    sourceSize.width: parent.height / 2
                                    fillMode: Image.PreserveAspectFit
                                    anchors.verticalCenter: parent.verticalCenter

                                    source: {
                                        var imageClose;

                                        if (deleteOne.containsMouse) {
                                            imageClose = Images.deleteBlack;
                                        }
                                        else {
                                            imageClose = Images.deleteGray;
                                        }
                                        if (deleteOne.pressed) {
                                            imageClose = Images.deleteBlue
                                        }

                                        return imageClose;
                                    }

                                    MouseArea {
                                        id: deleteOne
                                        anchors.fill: parent
                                        hoverEnabled: true

                                        onClicked: backupModel.removeSingle(index)
                                    }
                                }

                            }
                        }
                    }
                }
            }

        }

        ActiveButton {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.rightMargin: 40
            anchors.right: parent.right

            height: 45
            width: 230

            enabled: backupModel.itemsCount > 0

            text: "Generate"

            function launchDialog(componentName, directParent, options) {
                var component = Qt.createComponent(componentName);
                if (component.status !== Component.Ready) {
                    console.debug("Component Error: " + component.errorString());
                } else {
                    var instance = component.createObject(directParent, options);
                }
            }

            onClicked: {
                launchDialog("ConfigPopup.qml", mainWindow, {})
            }
        }

    }
}


