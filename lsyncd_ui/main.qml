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
            console.log(fileDialog.fileUrls)
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

    Rectangle {
        anchors.fill: parent
        color: Colors.applicationBackgroundColor

        Rectangle {
            id: header
            height: 60
            color: Colors.normalGrayColor
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
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
                                id: showI

                                anchors.centerIn: parent

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
                                    var showT;
                                        if (index == 0) {
                                            showT = "Tree";
                                        } else {
                                            showT = "List";
                                        }

                                    return showT;
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

            Tab {
                title: "Tree"
                property string activeBackground: Images.treeBlue
                property string notActiveBackground: Images.treeGray
                property string hoverBackground: Images.treeWhite

            }

            Tab {
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

                                onClicked: {
                                    backupModel.removeAll()
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

                                MouseArea {
                                    id: deleteOne

                                    width: 30
                                    anchors.top: addedFolder.top
                                    anchors.bottom: addedFolder.bottom
                                    anchors.right: addedFolder.right

                                    hoverEnabled: true

                                    onClicked: backupModel.removeSingle(index)
                                }

                                Image {

                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: deleteOne.right
                                        anchors.rightMargin: 10

                                        source: {
                                            var imageClose;

                                            if (deleteOne.containsMouse) {
                                                imageClose = Images.deleteBlack;
                                            }
                                            else {
                                                imageClose = Images.deleteGray;
                                            }
                                            if (deleteOne.pressed)
                                                    imageClose = Images.deleteBlue


                                            return imageClose;
                                        }
                                    }

                            }
                        }
                    }
                }
            }
        }
    }
}


