/*******************************************************************************
*                                                                              *
*  Button item implementation.                                                 *
*                                                                              *
*  Copyright (C) 2011-2012 Kirill Chuvilin.                                    *
*  All rights reserved.                                                        *
*  Contact: Kirill Chuvilin (kirill.chuvilin@gmail.com, kirik-ch.ru)           *
*                                                                              *
*  This file is part of the QKit project.                                      *
*                                                                              *
*  $QT_BEGIN_LICENSE:GPL$                                                      *
*  You may use this file under the terms of the GNU General Public License     *
*  as published by the Free Software Foundation; version 3 of the License.     *
*                                                                              *
*  This file is distributed in the hope that it will be useful,                *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this package; if not, write to the Free Software                 *
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.   *
*  $QT_END_LICENSE$                                                            *
*                                                                              *
*******************************************************************************/

import Qt 4.7

QKitRectangle {
    id: button
    objectName: "QKitButton"

    property string text: "" // button text
    // UI properties
    property int borderWidth // width of border
    property color backgroundColor // background color
    property color backgroundColorDimmed: backgroundColor // background color when button is pressed
    property color backgroundColorSelected: backgroundColor // background color when button is selected
    property color borderColor // border color
    property color borderColorDimmed: borderColor // border color when button is pressed
    property color borderColorSelected: borderColor // border color when button is selected
    property color textColor // text color
    property color textColorDimmed: textColor // text color when button is pressed
    property color textColorSelected: textColor // text color when button is selected
    property url imageSource: "" // url to image
    property url imageSourceDimmed: imageSource // url to image when button is pressed
    property url imageSourceSelected: imageSource // url to image when button is selected
    property bool mouseHoverEnabled: uiController.mouseHoverEnabled // handle mouse hover or not
    // key properties
    property int pressKey: keyController.buttonPressKey // key for press
    // other properties
    property Item textItem: buttonTextItem // item with text
    property Item imageItem: buttonImageItem // item with image
    property Item __local: Item { // local variables
        property bool pressed: false // pressed or not
        property int key // button was pressed by the key

        states: [
            State { // on pressed or disabled
                name: "dimmed"
                when: __local.pressed || buttonMouseArea.pressed || !button.active
                PropertyChanges {
                    target: button
                    color: button.backgroundColorDimmed
                    border.color: button.borderColorDimmed
                }
                PropertyChanges {
                    target: buttonTextItem
                    color: button.textColorDimmed
                }
                PropertyChanges {
                    target: buttonImageItem
                    source: button.imageSourceDimmed
                }
            },
            State { // on selected or focused
                name: "selected"
                when: button.active && !__local.pressed && (buttonMouseArea.containsMouse || button.selected)
                PropertyChanges {
                    target: button
                    color: button.backgroundColorSelected
                    borderColor: button.borderColorSelected
                }
                PropertyChanges {
                    target: buttonTextItem
                    color: button.textColorSelected
                }
                PropertyChanges {
                    target: buttonImageItem
                    source: button.imageSourceSelected
                }
            }
        ]
    }

    signal clicked() // emits when button is clicked
    signal doubleClicked() // emits when button is double clicked
    signal entered() // emits when mouse pointer enters button area
    signal exited() // emits when mouse pointer exits button area
    signal pressAndHold() // emits when button is pressed for a long time
    signal pressed() // emits when button is pressed
    signal pressedChanged() // emits when button pressed state is changes
    signal released() // emits when button is released

    function pressByKey(event) { // press button by particular key
        if (!active) return // must be active to press
        __local.key = event.key // remember key
        __local.pressed = true // press button
        focus = true // focus on button to handle key release
        button.pressed() // press signal
    }

    color: button.backgroundColor
    border.color: button.borderColor
    border.width: button.borderWidth

    Row { // button content
        anchors.centerIn: parent
        height: parent.height
        width: childrenRect.width
        Image { // item with image
            id: buttonImageItem

            anchors.verticalCenter: parent.verticalCenter
            source: button.imageSource
//            width: source == "" ? 0 : button.width
//            height: source == "" ? 0 : button.height
//            fillMode: Image.PreserveAspectFit
            scale: Math.min(button.height / sourceSize.height, button.width / sourceSize.width)
            smooth: button.smooth
        }
        Text { // item with text
            id: buttonTextItem

            anchors.verticalCenter: parent.verticalCenter
            text: button.text
            color: button.textColor
            font.pixelSize: 0.5 * parent.height
        }
    }

    MouseArea {
        id: buttonMouseArea

        anchors.fill: button
        hoverEnabled: button.mouseHoverEnabled // handle mouse hover or not
        onClicked: if (active) button.clicked()
        onDoubleClicked: if (active) button.doubleClicked()
        onEntered: if (active) button.entered()
        onExited: if (active) button.exited()
        onPressAndHold: if (active) button.pressAndHold()
        onPressed: if (active) button.pressed()
        onPressedChanged: if (active) button.pressedChanged()
        onReleased: if (active) button.released()
    }

    Keys.onPressed: {
        if (!active) return // must be active to handle
        switch (event.key) {
        case button.pressKey:
            button.pressByKey(event)
            break
        default:
            return
        }
        event.accepted = true
    }
    Keys.onReleased: {
        if (!active) return // must be active to handle
        switch (event.key) {
        case __local.key: // was pressed by that key
            __local.key = 0 // forget press key
            __local.pressed = false // now not pressed
            button.released() // release signal
            button.clicked() // click signal
            break
        default:
            return
        }
        event.accepted = true
    }
}
