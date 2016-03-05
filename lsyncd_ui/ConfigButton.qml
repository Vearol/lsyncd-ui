import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "Colors.js" as Colors

Button {
    style: ButtonStyle {
        background: Rectangle {
            implicitWidth: 150
            implicitHeight: 30
            border.width: 0
            radius: 0
            color: {
                var result;

                if (control.enabled) {
                    if (control.hovered) {
                        if (control.pressed) {
                            result = Colors.darkGrayColor;
                        } else {
                            result = Colors.blueActiveColor;
                        }
                    }
                    else {
                        result = Colors.normalTextColor;
                    }
                }
                else {
                    result = Colors.disabledButtonColor;
                }

                return result;
            }
        }

        label: Text {
            text: control.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pixelSize: 16
            color: {
                var result;

                if (control.enabled) {
                    if (control.hovered) {
                        if (control.pressed) {
                            result = Colors.normalTextColor;
                        } else {
                            result = Colors.normalTextColor;
                        }
                    }
                    else {
                        result = Colors.blueActiveColor;
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

