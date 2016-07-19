import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "Colors.js" as Colors;

TreeView {
    style: TreeViewStyle {
        alternateBackgroundColor: Colors.buttonsPanelColor
        backgroundColor: Colors.applicationListColor
        rowDelegate: Rectangle {
            color: ( styleData.row % 2 == 0 ) ? Colors.buttonsPanelColor : Colors.applicationListColor
            height: 25

        }
    }
}

