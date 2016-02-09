import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TextInput {
    font.family: "Helvetica"
    font.pixelSize: 16
    verticalAlignment: TextInput.AlignVCenter
    //selectedTextColor: Colors.defaultLightColor
    //selectionColor: Colors.defaultControlColor
    renderType: Text.NativeRendering
    selectByMouse: true
    clip: true
    //color: enabled ? Colors.defaultLightColor : Colors.itemsSourceForeground
    KeyNavigation.priority: KeyNavigation.BeforeItem
    maximumLength: 300
}
