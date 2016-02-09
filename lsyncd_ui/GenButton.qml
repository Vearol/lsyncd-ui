import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "Colors.js" as Colors

Button {
    style: ButtonStyle {

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 45
            border.width: 0
            radius: 0
            color: {
                var result;

                if (control.enabled) {
                    if (control.hovered) {
                        if (control.pressed) {
                            result = Colors.darkGrayColor;
                        } else {
                            result = Colors.normalTextColor;
                        }
                    } else {
                        result = Colors.blueActiveColor;
                    }
                } else {
                    result = Colors.generateButtonDisabledColor;
                }

                return result;
            }
        }

        label: Text {
            text: control.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pixelSize: 18
            color: {
                var result;

                if (control.enabled) {
                    if (control.hovered) {
                        if (control.pressed) {
                            result = Colors.normalTextColor;
                        } else {
                            result = Colors.blueActiveColor;
                        }
                    } else {
                        result = Colors.normalTextColor
                    }
                }
                    else {
                        result = Colors.disabledTextColor;
                    }

                return result;
            }
        }
    }
}


